#ifndef _H_VELHA_
#define _H_VELHA_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <ctime>

enum Outcome {INVALID, UNKNOWN, LOSE, WIN};

class Velha {
private:
	union {
		int m[3][3];
		int v[9];
	};
	int turn;  // -1 (over), 1 (player 1), 2 (player 2)

	void Undo(int move);
	Outcome TestMove(int move);

public:
	Velha() { Velha(1); };
	Velha(int start_player);
	bool Play(int move);
	int PlanSilly();
	int PlanSmart();
	int State(); // ongoing (0), tie (-1), p1 wins (1), p2 wins (2)
	void Print();
	int Query();
	int Turn() {return turn;};
	void PrintStrategy();
	void Copy(std::vector<int>& cp);
};

#endif