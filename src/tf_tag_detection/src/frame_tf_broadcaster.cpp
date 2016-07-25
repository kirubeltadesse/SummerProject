#include <ros/ros.h>
#include <tf/transform_broadcaster.h> // in case this doesn't work try using tf2_ros instand of tf


int main(int argc, char** argv){
    ros::init(argc, argv, "rover_tf_transform");
    ros::NodeHandle node;

    tf::TransformBroadcaster br;
    tf::Transform transform;

    ros::Rate rate(10.0);
    while (node.ok()){
        transform.setOrigin(tf::Vector3(0.13,0.03,0.195));
        transform.setRotation(tf::Quaternion(0,0,0,1));
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"head_camera", "gamma/base_link" ));
        rate.sleep();
    }
    return 0;
};
