#include <stdio.h>

#include "board_short.h"

char cellValue( enum position_t value ) {
	switch ( value ) {
		case EMPTY: return ' ';
		case CROSS: return 'X';
		case CIRCLE: return 'O';
		default: return '?';
	}
}

void printBoard( unsigned short board ) {
	printf( " %c | %c | %c \n---+---+---\n %c | %c | %c \n---+---+---\n %c | %c | %c \n\n",
			cellValue( getCell( board, TOP_LEFT ) ),
			cellValue( getCell( board, TOP_CENTER ) ),
			cellValue( getCell( board, TOP_RIGHT ) ),
			cellValue( getCell( board, CENTER_LEFT ) ),
			cellValue( getCell( board, CENTER_CENTER ) ),
			cellValue( getCell( board, CENTER_RIGHT ) ),
			cellValue( getCell( board, BOTTOM_LEFT ) ),
			cellValue( getCell( board, BOTTOM_CENTER ) ),
			cellValue( getCell( board, BOTTOM_RIGHT ) )
		 );
}

int main( ) {
	board_t board = EMPTY_BOARD;

	printBoard( board );
	board = setCell( board, TOP_LEFT, CIRCLE );
	board = setCell( board, TOP_CENTER, CIRCLE );
	board = setCell( board, TOP_RIGHT, CIRCLE );
	board = setCell( board, CENTER_LEFT, CIRCLE );
	board = setCell( board, CENTER_CENTER, CIRCLE );
	board = setCell( board, CENTER_RIGHT, CIRCLE );
	board = setCell( board, BOTTOM_LEFT, CIRCLE );
	board = setCell( board, BOTTOM_CENTER, CIRCLE );
	board = setCell( board, BOTTOM_RIGHT, CIRCLE );
	printBoard( board );

	board = setCell( board, TOP_RIGHT, CROSS );
	board = setCell( board, TOP_CENTER, CROSS );
	board = setCell( board, CENTER_CENTER, EMPTY );
	printBoard( board );
	return 0;
}
