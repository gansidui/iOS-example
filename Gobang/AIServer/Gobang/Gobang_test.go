package Gobang

import (
	"testing"
)

func TestAI(t *testing.T) {
	var chessMap [][]byte
	for i := 0; i < 15; i++ {
		slice := make([]byte, 15)
		chessMap = append(chessMap, slice)
	}

	for i := 0; i < 15; i++ {
		for j := 0; j < 15; j++ {
			chessMap[i][j] = ' '
		}
	}
	chessMap[7][7] = 'B'

	row, col := AI(chessMap)
	println(row, col)
}
