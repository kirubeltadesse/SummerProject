#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

char host[128];
std::string rover_name;
std::string hostname;


int main(int argc, char** argv){
    gethostname(host, sizeof(host));
    std::string gamma; // reamend this line

    ros::init(argc, argv, "rover_tf_transform");
    if (argc != 2){
        ROS_ERROR("need rover name as an argument"); 

        rover_name = argv[1];
      /*  return -1*/;}else{
            rover_name = gamma;}

    ros::NodeHandle node;
    ros::Rate r(100);
    tf::TransformBroadcaster broadcaster;
    while(node.ok()){
        broadcaster.sendTransform(
                tf::StampedTransform(
                    tf::Transform(tf::createQuaternionFromRPY(0, 0, M_PI/2), tf::Vector3(0.13,0.03,0.195)),                     ros::Time::now(), "gamma/base_link" , "head_camera")); //gamma/base_like needs modification
        r.sleep();
    }
    // ros::Subscriber sub = node.subscribe(rover_name+"/odom", 10, &poseCallback);
 //   ros::spin();
    return 0;
};




