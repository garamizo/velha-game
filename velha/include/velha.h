#ifndef _H_VELHA_
#define _H_VELHA_

enum Outcome {INVALID, LOSE, UNKNOWN, WIN};

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
	Outcome TestMove(int move);
	void PrintStrategy();
};

#endif