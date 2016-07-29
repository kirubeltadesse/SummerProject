#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <apriltags_ros/AprilTagDetectionArray.h>


char host[128];
std::string rover_name;
std::string hostname;

void apriltags_Handler(const apriltags_ros::AprilTagDetectionArray::ConstPtr& msg){
    static tf::TransformBroadcaster Br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(0.13, 0.03, 0.195));
    tf::Quaternion q;
    q.setRPY(-2.36, 0, -M_PI_2);
    transform.setRotation(q);
    Br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "gamma/base_link", "head_camera"));
}

int main(int argc, char** argv){
    gethostname(host, sizeof(host));
    std::string gamma; // reamend this line

    ros::init(argc, argv, "rover_tf_transform");
    if (argc != 2){
        ROS_ERROR("need rover name as an argument"); 

        rover_name = argv[1];
      /*  return -1*/;}else{
            rover_name = gamma;}

    ROS_INFO_STREAM("Inside the main function");
    ros::NodeHandle node;
    ros::Subscriber apriltagsSubscriber = node.subscribe("/gamma/tag_detections", 10, apriltags_Handler);
    ros::spin();
   return 0;
};




