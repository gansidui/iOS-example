#include "GobangInterface.h"
#include "FiveChessAI.hpp"
#include <iostream>

void AI_interface(char *arr, int *row, int *col, int *flag) {
	char chessMap[15][15];
	int count = 0;
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			chessMap[i][j] = arr[count++];
		}
	}

	FiveChessAI chessAI;

	char player = chessAI.getCurrentPlayer(chessMap);
	if (player == 'B') {
		*flag = 1;
	} else {
		*flag = 2;
	}

	std::pair<int, int> position = chessAI.goAI(chessMap);
	*row = position.first;
	*col = position.second;
}