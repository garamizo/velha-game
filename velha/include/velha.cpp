#include "velha.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <ctime>


Velha::Velha(int start_player) {
	srand(std::time(0));
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
		if (m[i][0] == m[i][1] && m[i][1] == m[i][2] && m[i][0] != 0)
			return m[i][0];
		if (m[0][i] == m[1][i] && m[1][i] == m[2][i] && m[0][i] != 0)
			return m[0][i];
	}
	if (m[0][0] == m[1][1] && m[1][1] == m[2][2] && m[0][0] != 0)
		return m[0][0];
	if (m[2][0] == m[1][1] && m[1][1] == m[0][2] && m[2][0] != 0)
		return m[2][0];

	if (m[0][0] != 0 && m[0][1] != 0 && m[0][2] != 0 &&
		m[1][0] != 0 && m[1][1] != 0 && m[1][2] != 0 &&
		m[2][0] != 0 && m[2][1] != 0 && m[2][2] != 0)
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
		if (quality == WIN)
			good_moves.push_back(move);
		else if (quality == UNKNOWN)
			neutral_moves.push_back(move);
	}

	if (good_moves.size() > 0)
		return good_moves[rand() % good_moves.size()];
	else if (neutral_moves.size() > 0)
		return neutral_moves[rand() % neutral_moves.size()];
	else
		return PlanSilly();
}

Outcome Velha::TestMove(int move) {
	int me = Turn();

	if (!Play(move))  // invalid
		return INVALID;

	Outcome quality = UNKNOWN;
	if (State() == me)  // immediate win
		quality = WIN;
	else {
		bool safe = false;
		bool any_valid = false;
		for (int newmove = 0; newmove < 9; newmove++) {
			int new_quality = TestMove(newmove);

			if (new_quality == WIN) {  // can lose next
				quality = LOSE;
				break;
			}
			if (new_quality == UNKNOWN)
				safe = true;
			if (new_quality != INVALID)
				any_valid = true;
		}
		if (quality == UNKNOWN && safe == false && any_valid)  // will win later
			quality = WIN;
	}

	Undo(move);
	return quality;
}

void Velha::PrintStrategy() {
	printf("\n\t(Strategy for player %d)\n", turn);
	for (int i = 0; i < 3; i++) {
		printf("\t %2d | %2d | %2d\n", TestMove(3*i)-1,
			TestMove(3*i+1)-1, TestMove(3*i+2)-1);
		if (i < 2)
			printf("\t--------------\n");
	}
}

void Velha::Undo(int move) {

	v[move] = 0;
	turn = (turn == 1 ? 2 : 1);
}