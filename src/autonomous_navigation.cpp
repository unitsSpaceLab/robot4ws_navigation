#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <cstdlib>
#include <string.h>
#include <tf/transform_listener.h>

#define N 10000

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  move_base_msgs::MoveBaseGoal goal_out;

  ros::Time t = ros::Time(0); // ask for last known transform

  //we'll send a random goal to the robot
  goal.target_pose.header.frame_id = "Archimede_base_link";
  goal.target_pose.header.stamp = t;

    goal.target_pose.pose.position.x = rand()%N/(N/10);
  goal.target_pose.pose.position.y = rand()%N/(N/10) - 10/2;
  goal.target_pose.pose.orientation.w = 1;
  //ROS_INFO("Goal x: ", goal.target_pose.pose.position.x);
  //ROS_INFO("Goal x: ", goal.target_pose.pose.position.y);
  
  tf::TransformListener tf_;
  goal_out.target_pose.header.frame_id = "map";
  goal_out.target_pose.header.stamp = ros::Time::now();
  
  //Transform goal pose from base_link frame to map frame
  try {
    tf_.waitForTransform(goal_out.target_pose.header.frame_id, goal.target_pose.header.frame_id, t, ros::Duration(4));
    tf_.transformPose(goal_out.target_pose.header.frame_id, goal.target_pose, goal_out.target_pose);
  }
    catch (const tf::TransformException ex)
  {
    ROS_ERROR("Failed to transform: %s", ex.what());
    return 1;
  }

  ROS_INFO("Sending goal");
  ac.sendGoal(goal_out);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Goal reached");
  else
    ROS_INFO("The base failed to move for some reason");

  return 0;
}