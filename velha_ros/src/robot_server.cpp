#include <ros/ros.h>
#include <velha_ros/MakeMove.h>
#include <iostream>
#include "velha.h"


int main(int argc, char* argv[]) {
	ros::init(argc, argv, "robot_server");
	ros::NodeHandle nh;

	int start_player = 1;
	if (argc == 2)
		start_player = atof(argv[1]);

	Velha game(start_player);
	game.Print();

	ros::ServiceClient client1 = nh.serviceClient<velha_ros::MakeMove>("move1"),
					   client2 = nh.serviceClient<velha_ros::MakeMove>("move2");
	ros::Rate loop_rate(1);

	while (game.State() == 0 && ros::ok()) {
		bool success;

		velha_ros::MakeMove srv;
		game.Copy(srv.request.fields);
		srv.request.player = game.Turn();

		if (game.Turn() == 1)
			success = client1.call(srv);
		else
			success = client2.call(srv);
		
		if (success) {
			game.Play(srv.response.index);
			game.Print();
		}
		
		ros::spinOnce();
		loop_rate.sleep();
	}
	if (game.State() == -1)
		ROS_INFO("\nGame over. Tie!\n");		
	else
		ROS_INFO("\nGame over. Player %d wins!\n", game.State());

	ros::spin();
	return 0;
}