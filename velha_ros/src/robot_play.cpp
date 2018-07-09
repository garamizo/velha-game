#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <actionlib/server/simple_action_server.h>
#include <velha_ros/MoveAction.h>
#include <iostream>
#include "velha.h"

typedef actionlib::SimpleActionServer<velha_ros::MoveAction> Server;

class GameServer : public Velha {
public:
	ros::NodeHandle nh;
	Server server1, server2;

	velha_ros::MoveResult result;
	velha_ros::MoveFeedback feedback;

	GameServer() :
		server1(nh, "player1", boost::bind(&GameServer::execute1, this, _1, &server1), false),
		server2(nh, "player2", boost::bind(&GameServer::execute2, this, _1, &server2), false)
	{
	  	server1.start();
	  	server2.start();
	  	ROS_INFO("Game started");
	}

	void execute(const velha_ros::MoveGoalConstPtr& goal, Server* as, int from)
	{
		result.valid = (Turn() == from) ? Play(goal->index) : false;
		as->setSucceeded(result);

		Copy(feedback.state);
		as->publishFeedback(feedback);

		Print();

		if (State() == -1) {
			printf("\nGame over. Tie!\n");
			exit(0);
		}
		else if (State() != 0) {
			printf("\nGame over. Player %d wins!\n", State());
			exit(0);
		}
	}

	void execute1(const velha_ros::MoveGoalConstPtr& goal, Server* as) {
		execute(goal, as, 1);
	}

	void execute2(const velha_ros::MoveGoalConstPtr& goal, Server* as) {
		execute(goal, as, 2);
	}
};

int main(int argc, char* argv[]) {
	ros::init(argc, argv, "robot_play");

	GameServer gs;

	// game.Print();
	// while (game.State() == 0) {
	// 	int move;

	// 	if (game.Turn() == 1)
	// 		move = game.Query();
	// 	else {
	// 		// game.PrintStrategy();
	// 		move = game.PlanSmart();
	// 	}

	// 	game.Play(move);
	// 	game.Print();
		
	// 	ros::spinOnce();
	// }
	// if (game.State() == -1)
	// 	printf("\nGame over. Tie!\n");		
	// else
	// 	printf("\nGame over. Player %d wins!\n", game.State());

	ros::spin();
	return 0;
}