package Gobang

/*
#include "Gobang.h"
*/
import "C"

func AI(chessMap [][]byte) (row, col int) {
	s := make([]byte, 15*15)

	for i := 0; i < 15; i++ {
		for j := 0; j < 15; j++ {
			s[15*i+j] = chessMap[i][j]
		}
	}

	cs := C.CString(string(s))
	r := C.int(0)
	c := C.int(0)

	C.AI(cs, &r, &c)

	// C.free(unsafe.Pointer(cs))

	return int(r), int(c)
}
