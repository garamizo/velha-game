#include <stdio.h>
#include <stdlib.h>
#include "velha.h"

int main(int argc, char* argv[]) {
	
	int start_player = 1;
	if (argc == 2)
		start_player = atof(argv[1]);

	Velha game(start_player);

	game.Print();
	while (game.State() == 0) {
		int move;

		if (game.Turn() == 1)
			move = game.Query();
		else {
			game.PrintStrategy();
			move = game.PlanSmart();
		}

		game.Play(move);
		game.Print();
	}
	if (game.State() == -1)
		printf("\nGame over. Tie!\n");		
	else
		printf("\nGame over. Player %d wins!\n", game.State());

	return 0;
}