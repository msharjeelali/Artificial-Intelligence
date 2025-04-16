#include<iostream>

using namespace std;

const int boardSize = 8;
const int totalMoves = 8;
long long state = 0;

void printBoard(int board[boardSize][boardSize]) {
	for (int i = 0; i < ::boardSize; i++) {
		for (int j = 0; j < ::boardSize; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}


bool isGoalState(int board[boardSize][boardSize]) {
	bool flag = true;
	for (int i = 0; i < boardSize && flag; i++) {
		for (int j = 0; j < boardSize && flag; j++) {
			if (-1 == board[i][j]) {
				flag = false;
			}
		}
	}
	return flag;
}

void successorFunction(int position[], int(&nextMoves)[totalMoves][2]) {
	int x = position[0];
	int y = position[1];

	nextMoves[5][0] = x - 1;
	nextMoves[5][1] = y - 2;
	// Left down function
	nextMoves[6][0] = x + 1;
	nextMoves[6][1] = y - 2;
	// Right up function
	nextMoves[2][0] = x - 1;
	nextMoves[2][1] = y + 2;
	// Right down function
	nextMoves[1][0] = x + 1;
	nextMoves[1][1] = y + 2;
	// Up left function
	nextMoves[4][0] = x - 2;
	nextMoves[4][1] = y - 1;
	// Up right function
	nextMoves[3][0] = x - 2;
	nextMoves[3][1] = y + 1;
	// Down left function
	nextMoves[7][0] = x + 2;
	nextMoves[7][1] = y - 1;
	// Down right function
	nextMoves[0][0] = x + 2;
	nextMoves[0][1] = y + 1;

};

void canMove(int board[boardSize][boardSize], int(&moves)[totalMoves][2]) {
	for (int i = 0; i < totalMoves; i++) {
		if (moves[i][0] >= 0 && moves[i][0] < boardSize && moves[i][1] >= 0 && moves[i][1] < boardSize) {
			if (board[moves[i][0]][moves[i][1]] != -1) {
				moves[i][0] = INT_MAX;
				moves[i][1] = INT_MAX;
			}
		}
		else {
			moves[i][0] = INT_MAX;
			moves[i][1] = INT_MAX;
		}
	}
}

bool ids(int(&board)[boardSize][boardSize], int position[], int targetLevel, int currentLevel) {

	if (currentLevel == targetLevel) {
		board[position[0]][position[1]] = currentLevel;
		if (isGoalState(board)) {
			cout << "Goal Reached" << endl;
			cout << "Level: " << currentLevel << " , " << "State: " << state++ << endl;
			printBoard(board);
			return true;
		}
		cout << "Level: " << currentLevel << " , " << "State: " << state++ << endl;
		printBoard(board);
	}

	if (currentLevel < targetLevel) {
		board[position[0]][position[1]] = currentLevel;
		state++;
		int nextPositions[totalMoves][2];
		successorFunction(position, nextPositions);
		canMove(board, nextPositions);
		for (int i = 0; i < totalMoves; i++) {
			if (nextPositions[i][0] != INT_MAX && nextPositions[i][1] != INT_MAX) {
				if (ids(board, nextPositions[i], targetLevel, currentLevel + 1))
					return true;
			}
		}
	}

	board[position[0]][position[1]] = -1;
	return false;
}

bool iterativeDeepeningSearch(int(&board)[boardSize][boardSize], int start[]) {
	int level = 0;
	while (level < ::boardSize * ::boardSize) {
		if (ids(board, start, level, 0))
			return true;
		level++;
	}
	return false;
}

int main() {

	cout << "Execution Started" << endl;
	int board[boardSize][boardSize];
	for (int i = 0; i < ::boardSize; i++) {
		for (int j = 0; j < ::boardSize; j++) {
			board[i][j] = -1;
		}
	}
	int start[2]{ 0, 0 };

	if (iterativeDeepeningSearch(board, start))
		cout << "Solution found" << endl;
	else
		cout << "Solution not found" << endl;

	return 0;
}