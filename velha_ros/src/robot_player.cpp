#include <ros/ros.h>
#include <velha_ros/MakeMove.h>
#include <iostream>
#include "velha.h"

bool expert_mode = false;

bool play(velha_ros::MakeMove::Request  &req,
         velha_ros::MakeMove::Response &res)
{
	Velha game(req.fields, req.player);
	res.index = expert_mode ? game.PlanSmart() : game.PlanSilly();
	return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "robot_player", ros::init_options::AnonymousName);
  ros::NodeHandle nh;

  if (argc == 2 && atoi(argv[1]) == 1234)
  	expert_mode = true;

  ros::ServiceServer service = nh.advertiseService("move", play);
  ROS_INFO("Ready to play velha");
  ros::spin();

  return 0;
}
