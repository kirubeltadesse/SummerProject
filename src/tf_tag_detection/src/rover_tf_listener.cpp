#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h> //more info
#include <geometry_msgs/PointStamped.h> //more info
#include <apriltags_ros/AprilTagDetectionArray.h>


void transformPoint(const tf::TransformListener& Listener){
    //obtaining the point in the camera frame that will be transformed to 
    apriltags_ros::AprilTagDetectionArray value;
    geometry_msgs::PointStamped camera_point;
    camera_point.header.frame_id = "head_camera";

    //using the most recent transform available
    camera_point.header.stamp = ros::Time();

    //point in the space camera frame
    camera_point.point.x = value.detections[0].pose.pose.position.x;
    camera_point.point.y = value.detections[0].pose.pose.position.y;
    camera_point.point.z = value.detections[0].pose.pose.position.z; 

    try{
        geometry_msgs::PointStamped base_point;
        Listener.transformPoint("gamma/base_link", camera_point, base_point);
                ROS_INFO("camera_point.point:(%.2f,%.2f,%.2f)------->base_link:(%.2f,%.2f,%.2f) at time of %.2f",camera_point.point.x,camera_point.point.y,camera_point.point.z,base_point.point.x,base_point.point.y,base_point.point.z, base_point.header.stamp.toSec());
                }catch(tf::TransformException& ex){
                ROS_ERROR("Received an exception trying to transform a point from \"camera\" to \"base_link\": %s", ex.what()); } 
                }




                int main(int argc, char** argv){

                ros::init(argc, argv, "rover_tf_listener");
                ros::NodeHandle node;

                //                ros::Publisher rover_val = node.advertise<????::???>("type/name", 10); //I need to publish the velocity

                tf::TransformListener listener(ros::Duration(10));

                //transform a point 
                ros::Timer timer = node.createTimer(ros::Duration(1.0), boost::bind(&transformPoint, boost::ref(listener)));
                ros::spin();

                };

//figure out the frames that we want to transform between
