#include <stdio.h>

#include "board.h"
#include "board_rotation.h"

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

	board = setCell( board, TOP_LEFT, CIRCLE );
	board = setCell( board, CENTER_CENTER, CIRCLE );
	board = setCell( board, BOTTOM_RIGHT, CIRCLE );

	board = setCell( board, TOP_CENTER, CROSS );
	board = setCell( board, CENTER_LEFT, CROSS );
	board = setCell( board, BOTTOM_CENTER, CROSS );
	printBoard( board );
	printBoard( rotateLeft( board ) );

	return 0;
}
