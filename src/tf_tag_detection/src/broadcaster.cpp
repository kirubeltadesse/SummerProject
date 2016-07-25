//this is broadcasting the rover in relation to the hold world
//
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

char host[128];
std::string rover_name;

/* void poseCallback(const nav_msgs::Odometry::ConstPtr& msg){
    
    static tf::TransformBroadcaster Br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->pose.pose.position.x, msg->pose.pose.position.y, 0.0));
    tf::Quaternion q(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
    double roll, pitch, yaw;
    tf::Matrix3x3 m(q);
    m.getRPY(roll,pitch, yaw);
    q.setRPY(0, 0, yaw);
    transform.setRotation(q);
    Br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", rover_name));
    ROS_INFO_STREAM("x: "<< msg->pose.pose.orientation.x<<" y: "<<msg->pose.pose.orientation.y<<" z: "<< msg->pose.pose.orientation.z<< " w: " << msg->pose.pose.orientation.w << yaw );


}*/ 

int main(int argc, char** argv){
    gethostname(host, sizeof(host));
    std::string hostname(host);
    
    ros::init(argc, argv, "rover_tf_transform");
   if (argc != 2){ROS_ERROR("need rover name as an argument"); return -1;};
  rover_name = argv[1];

  ros::NodeHandle node;
  ros::Rate r(100);
  tf::TransformBroadcaster broadcaster;
  while(node.ok()){
      broadcaster.sendTransform(
              tf::StampedTransform(
                  tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.13,0.03,0.195)), 
                  ros::Time::now(), "gamma/base_link" , "head_camera")); //gamma/base_like needs modification
      r.sleep();
  }
 // ros::Subscriber sub = node.subscribe(rover_name+"/odom", 10, &poseCallback);
  ros::spin();
  return 0;
};



            

