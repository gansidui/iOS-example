#include "GobangInterface.h"
#include "FiveChessAI.hpp"
#include <iostream>

void AI_interface(char *arr, int *row, int *col) {
	char chessMap[15][15];
	int count = 0;
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			chessMap[i][j] = arr[count++];
		}
	}

	FiveChessAI chessAI;
	std::pair<int, int> position = chessAI.goAI(chessMap);
	*row = position.first;
	*col = position.second;
}