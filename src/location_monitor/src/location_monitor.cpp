#include <ros/ros.h>
#include <math.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include "shared_messages/TagsImage.h"
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Point32.h>

using namespace std;

ros::Publisher infoLogPublisher;
ros::Publisher value_pub;
char host[128];
string publishedName;

void TargetsCallback(const shared_messages::TagsImage::ConstPtr& msg){

    float x = msg->corners[0].points[0].x;
    float y = msg->corners[0].points[0].y;
    float _x = msg->corners[0].points[1].x;
    float _y = msg->corners[0].points[1].y;


    float x1 = msg->corners[0].points[2].x;
    float y1 = msg->corners[0].points[2].y;
    float _x1 = msg->corners[0].points[3].x;
    float _y1 = msg->corners[0].points[3].y;


    //caluculating perceived with 
    float perWidth = abs(x - _x);



    //distace found by actual measurment
    float knowDistance = 40.0;

    //actual width of the cube in centimeter 
    float know_width = 3.75;

    //initializing the Focus obtain through expermient
    float Focus = 371.2407147;

    //calculating the actual distance
    float Distance = hypot(((know_width * Focus)/perWidth), 0.195);

    std_msgs::Float32 value;
    value.data = Distance;



    value_pub.publish(value);

    ROS_INFO("kirubel Distance: %f", Distance); 
    /*ROS_INFO("X1: %f", x); 
    ROS_INFO("X2: %f", _x); 
    ROS_INFO("Y1: %f", y); 
    ROS_INFO("Y2: %f", _y); 
    ROS_INFO("X3: %f", x1); 
    ROS_INFO("Y3: %f", y1); 
    ROS_INFO("X4: %f", _x1); 
   ROS_INFO("Y4: %f", _y1);*/ 
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
    value_pub = n.advertise<std_msgs::Float32>((publishedName + "/value2"), 10);
    ros::Subscriber sub = n.subscribe((publishedName+ "/targets"),2, TargetsCallback); 
    std_msgs::String msg;
    msg.data = "Log Started";
    infoLogPublisher.publish(msg);
    ROS_INFO("kirubel X: %s", "Im here");
    //ROS_INFO("kirubel Y: %f", y);
    ros::spin();

    return 0;
}
