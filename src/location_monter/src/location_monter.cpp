#include <ros/ros.h>
#include <math.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <shared_messages/TagsImage.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Point32.h>

using namespace std;

ros::Publisher infoLogPublisher;
ros::Publisher value_pub;
char host[128];
string publishedName;

void TargetsCallback(const shared_messages::TagsImage::ConstPtr& msg){
    //caluculating perceived with 
    float perWidth = 0.0; //abs(x - _x);

    for(int i=0; i<2; i++){
        float x = msg->corners[0].points[i].x;
        float y = msg->corners[0].points[i].y;
        float _x = msg->corners[0].points[i+1].x;
        float _y = msg->corners[0].points[i+1].y;

        if(abs(x -_x) > abs(y - _y)){
            perWidth = abs(x - _x); 
        }
        else{
            perWidth = abs(y - _y);
        }


    }

    //initializing the Focus obtain through expermient
    float Focus = 337.5;

    //distace found by actual measurment
    float knowDistace = 40.0;

    //actual width of the cube in centimeter 
    float know_width = 4.0;

    //calculating the actual distance
    float Distance = (4.0 * Focus)/perWidth;
    std_msgs::Float32 value;
    value.data = Distance;



    value_pub.publish(value);

    ROS_INFO("kirubel Distance: %f", Distance); 
}


int main(int argc, char** argv){

    gethostname(host, sizeof(host));
    string hostname(host);

    if(argc >= 2){
        publishedName = argv[1];
        cout << "Position of " << publishedName << "!" << endl;
    }else {
        publishedName = hostname;
        cout << "No Name selected. Default is: " << publishedName << endl;
    }

    ros::init(argc, argv, (publishedName + "_LOCATION_MONTER"));
    ros::NodeHandle n;
    infoLogPublisher = n.advertise<std_msgs::String>("/infoLog", 1, true);
    value_pub = n.advertise<std_msgs::Float32>("/value2", 10);
    ros::Subscriber sub = n.subscribe((publishedName+ "/targets"),2, TargetsCallback); 
    std_msgs::String msg;
    msg.data = "Log Started";
    infoLogPublisher.publish(msg);
    //ROS_INFO("kirubel X: %f", x);
    //ROS_INFO("kirubel Y: %f", y);
    ros::spin();

    return 0;
}
