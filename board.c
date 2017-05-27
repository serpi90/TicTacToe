#include <stdio.h>

#include "position.h"
#include "cell_status.h"
#include "board_short.h"
#include "board_print.h"

int main() {
	board_t board = EMPTY_BOARD;

	printBoard( board );
	board = setCell(board, TOP_LEFT, CIRCLE);
	board = setCell(board, TOP_CENTER, CIRCLE);
	board = setCell(board, TOP_RIGHT, CIRCLE);
	board = setCell(board, CENTER_LEFT, CIRCLE);
	board = setCell(board, CENTER_CENTER, CIRCLE);
	board = setCell(board, CENTER_RIGHT, CIRCLE);
	board = setCell(board, BOTTOM_LEFT, CIRCLE);
	board = setCell(board, BOTTOM_CENTER, CIRCLE);
	board = setCell(board, BOTTOM_RIGHT, CIRCLE);
	printBoard( board );

	board = setCell(board, TOP_RIGHT, CROSS);
	board = setCell(board, TOP_CENTER, CROSS);
	board = setCell(board, CENTER_CENTER, EMPTY);
	printBoard( board );
	return 0;
}
