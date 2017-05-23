#include <stdio.h>
#include "board.h"

/* Printing functions */
char cellValue( enum position_t value ) {
	switch (value) {
		case EMPTY: return ' ';
		case CROSS: return 'X';
		case CIRCLE: return 'O';
		default: return '?';
	}
}

void printBoard( unsigned short board ) {
	printf("+-+-+-+\n|%c|%c|%c|\n|%c|%c|%c|\n|%c|%c|%c|\n+-+-+-+\nLastBit: %hu\n\n",
			cellValue(getCell(board, TOP_LEFT)),
			cellValue(getCell(board, TOP_CENTER)),
			cellValue(getCell(board, TOP_RIGHT)),
			cellValue(getCell(board, CENTER_LEFT)),
			cellValue(getCell(board, CENTER_CENTER)),
			cellValue(getCell(board, CENTER_RIGHT)),
			cellValue(getCell(board, BOTTOM_LEFT)),
			cellValue(getCell(board, BOTTOM_CENTER)),
			cellValue(getCell(board, BOTTOM_RIGHT)),
			getLastBit( board ) );
}

int main() {
	board_t board = EMPTY_BOARD;
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

	printBoard( board );
	board = setCell(board, CENTER_CENTER, EMPTY);
	printBoard( board );
	printBoard( setLastBit(board,0) );
	printBoard( setLastBit(board,1) );
	return 0;
}

