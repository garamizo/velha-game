#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Velha {
private:
	union {
		int m[3][3];
		int v[9];
	};
	int turn;  // -1 (over), 1 (player 1), 2 (player 2)

public:
	Velha();
	bool Play(int move);
	int Plan();
	int State();
	void Print();
	int Query();
	int Turn() {return turn;};
};

Velha::Velha() {
	turn = 1;
	for (int i = 0; i < 9; i++)
		v[i] = 0;
}

int Velha::Query() {
	int move;
	printf("Move: ");
	scanf("%d", &move);
	while (v[move] > 0) {
		printf("Invalid. Try again: ");
		scanf("%d", &move);
	}
	return move;
}

void Velha::Print() {
	for (int i = 0; i < 3; i++)
		printf("%d | %d | %d\n__________\n", m[i][0], m[i][1], m[i][2]);
}

int Velha::State() {
	for (int i = 0; i < 3; i++) {
		if (m[i][0] == m[i][1] && m[i][1] == m[i][2] && m[i][0] > 0)
			return m[i][0];
		if (m[0][i] == m[1][i] && m[1][i] == m[2][i] && m[0][i] > 0)
			return m[0][i];
	}
	if (m[0][0] == m[1][1] && m[1][1] == m[2][2] && m[0][0] > 0)
		return m[0][0];
	if (m[2][0] == m[1][1] && m[1][1] == m[0][2] && m[2][0] > 0)
		return m[2][0];

	if (m[0][0] > 0 && m[0][1] > 0 && m[0][2] > 0 &&
		m[1][0] > 0 && m[1][1] > 0 && m[1][2] > 0 &&
		m[2][0] > 0 && m[2][1] > 0 && m[2][2] > 0)
		return -1;

	return 0;
}

bool Velha::Play(int move) {
	printf("Marking %d as %d\n", move, turn);

	if (v[move] != 0)
		return false;

	v[move] = turn;

	if (State() == 0)
		turn = (turn == 1 ? 2 : 1);
	else
		turn = -1;
	return true;
}

int Velha::Plan() {
	int move = rand() % 9;
	while (v[move] > 0)
		move = rand() % 9;

	return move;
}



int main(int argc, char* argv[]) {
	
	Velha game;

	while (game.State() == 0) {
		printf("Turn: %d\n", game.Turn());
		int move;
		if (game.Turn() == 1)
			move = game.Query();
		else
			move = game.Plan();

		game.Play(move);
		game.Print();
		printf("State: %d\n", game.State());
	}
	if (game.State() < 0)
		printf("Game over. Tie!\n");		
	else
		printf("Game over. Player %d wins!\n", game.State());

	return 0;
}