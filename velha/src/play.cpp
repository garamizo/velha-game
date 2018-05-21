#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Velha {
private:
	union {
		int m[3][3];
		int v[9];
	};
	int turn;  // -1 (over), 1 (player 1), 2 (player 2)

public:
	Velha();
	Velha(int start_player);
	bool Play(int move);
	int PlanSilly();
	int PlanSmart();
	int State();
	void Print();
	int Query();
	int Turn() {return turn;};
	void Undo(int move);
	int TestMove(int move);
};

Velha::Velha() {
	Velha(1);
}

Velha::Velha(int start_player) {
	turn = start_player;
	for (int i = 0; i < 9; i++)
		v[i] = 0;
}

int Velha::Query() {
	int input, move;

	printf("Move: ");
	scanf("%d", &input);
	move = 3*(2 - (input-1) / 3) + ((input-1) % 3);
	while (v[move] > 0) {
		printf("Invalid. Try again: ");
		scanf("%d", &input);
		move = 3*(2 - (input-1) / 3) + ((input-1) % 3);
	}
	return move;
}

void Velha::Print() {
	printf("\nState: %d\nNext turn: %d\n", State(), turn);
	for (int i = 0; i < 3; i++) {
		printf(" %d | %d | %d\n", m[i][0], m[i][1], m[i][2]);
		if (i < 2)
			printf("-----------\n");
	}
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
	if (v[move] != 0)
		return false;

	v[move] = turn;
	turn = (turn == 1 ? 2 : 1);

	return true;
}

int Velha::PlanSilly() {
	int move = rand() % 9;
	while (v[move] > 0)
		move = rand() % 9;

	return move;
}

int Velha::PlanSmart() {
	std::vector<int> good_moves, neutral_moves;

	for (int move = 0; move < 9; move++) {
		int quality = TestMove(move);
		if (quality > 0)
			good_moves.push_back(move);
		else if (quality == 0)
			neutral_moves.push_back(move);
	}

	if (good_moves.size() > 0)
		return good_moves[0];
	else if (neutral_moves.size() > 0)
		return neutral_moves[0];
	else
		return PlanSilly();
}

int Velha::TestMove(int move) {
	int me = Turn();
	int test = 0;

	bool valid = Play(move);
	if (!valid)
		return -1;

	if (State() == me)
		test = 1;
	else
		for (int newmove = 0; newmove < 9; newmove++)
			if (TestMove(newmove) > 0) {
				test = -1;
				break;
			}
	Undo(move);
	return test;
}

void Velha::Undo(int move) {

	v[move] = 0;
	turn = (turn == 1 ? 2 : 1);
}



int main(int argc, char* argv[]) {
	
	Velha game(2);

	game.Print();
	while (game.State() == 0) {
		int move;

		if (game.Turn() == 1)
			move = game.Query();
		else
			move = game.PlanSmart();

		game.Play(move);
		game.Print();
	}
	if (game.State() < 0)
		printf("\nGame over. Tie!\n");		
	else
		printf("\nGame over. Player %d wins!\n", game.State());

	return 0;
}