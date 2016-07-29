#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h> //more info
#include <apriltags_ros/AprilTagDetectionArray.h>
#include <std_msgs/String.h>

ros::Publisher Tf_pose;
float x, y, z, Qx, Qy, Qz, Qw;
void apriltagHandle(const apriltags_ros::AprilTagDetectionArray::ConstPtr& msg){
    if(msg->detections.size() > 0) {

        x = msg->detections[0].pose.pose.position.x;
        y = msg->detections[0].pose.pose.position.y;
        z = msg->detections[0].pose.pose.position.z; 
        Qx = msg->detections[0].pose.pose.orientation.x;
        Qy = msg->detections[0].pose.pose.orientation.y;
        Qz = msg->detections[0].pose.pose.orientation.z;
        Qw = msg->detections[0].pose.pose.orientation.w;
    } else {
        ROS_ERROR_STREAM("tag_detections topic is passing empty array!");
    }

    //    ROS_INFO_STREAM(" In The ApriltagHandle X :"<< msg->detections[0].pose.pose.position.x <<" Y :"<< y <<" Z :"<<z);
}

void transformPose(const tf::TransformListener& listener){
    //obtaining the pose in the camera frame that will be transformed to 
    geometry_msgs::PoseStamped camera_pose;
    camera_pose.header.frame_id = "head_camera";

    camera_pose.pose.position.x =x;
    camera_pose.pose.position.y =y;
    camera_pose.pose.position.z =z;
    camera_pose.pose.orientation.x = Qx;
    camera_pose.pose.orientation.y = Qy;
    camera_pose.pose.orientation.z = Qz;
    camera_pose.pose.orientation.w = Qw;

    ROS_DEBUG_STREAM("In the TransformPose function X :"<< x <<" Y :"<< y <<" Z :"<<z);
    //using the most recent transform available
    camera_pose.header.stamp = ros::Time();

    //pose in the space camera frame

    try{
        geometry_msgs::PoseStamped odom_pose;
        listener.transformPose("gamma/odom", camera_pose, odom_pose);
        ROS_INFO("camera_pose:(%.2f,%.2f,%.2f)------->odom_pose:(%.2f,%.2f,%.2f) at time of %.2f",camera_pose.pose.position.x,camera_pose.pose.position.y,camera_pose.pose.position.z,odom_pose.pose.position.x,odom_pose.pose.position.y,odom_pose.pose.position.z, odom_pose.header.stamp.toSec());
    Tf_pose.publish(odom_pose);

    }catch(tf::TransformException& ex){
        ROS_ERROR("Received an exception trying to transform a pose from \"camera\" to \"base_link\": %s", ex.what()); } 


}


int main(int argc, char** argv){

    ROS_ERROR_STREAM("X :"<< x <<" Y :"<< y <<" Z :"<<z);
    ros::init(argc, argv, "rover_tf_listener");
    ros::NodeHandle node;

    //                ros::Publisher rover_val = node.advertise<????::???>("type/name", 10); //I need to publish the velocity

    tf::TransformListener listener(ros::Duration(10));
    ros::Subscriber aprilSubscriber = node.subscribe("gamma/tag_detections", 10, apriltagHandle);
    Tf_pose = node.advertise<geometry_msgs::PoseStamped>("tag_tf", 1 ,transformPose);

        //transform a pose 
        ros::Timer timer = node.createTimer(ros::Duration(0.5), boost::bind(&transformPose, boost::ref(listener)));
        ros::spin();

    };

    //figure out the frames that we want to transform between
