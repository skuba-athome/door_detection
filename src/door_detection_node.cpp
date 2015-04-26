#include "ros/ros.h"

#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"

ros::Publisher pub_door;

void scanCallback(const sensor_msgs::LaserScanConstPtr &scan){
  unsigned int center_index = scan->ranges.size()/2;
  float sum = 0.0;
  unsigned int k = 0;
  for(unsigned int n = center_index-10; n <= center_index+10;n++)
  {
  	float laser_range = scan->ranges[n];
  	if(laser_range == 0.0f) laser_range = scan->range_max;
  	sum += laser_range*cos((n-center_index)*scan->angle_increment);
  	k++;
  }
  float distance = sum/k;
  std_msgs::String door_isopen;
  static int count = 0;
  
  if(distance>0.6f) count++;
  else count = 0;
  
  if(count>60) door_isopen.data = "open";
  else door_isopen.data = "close";
  
  ROS_INFO("distance %f,%s",distance,door_isopen.data.c_str());
  
  pub_door.publish(door_isopen);  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "door_detection");

  ros::NodeHandle n;
  ros::Subscriber scan_sub = n.subscribe("/scan", 1, scanCallback);
  pub_door = n.advertise<std_msgs::String> ("status", 1);
  ros::spin();
  
  return 0;
}
