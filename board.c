#include <stdio.h>

/**
 * Store a tic-tac-toe board using an unsigned short (16 bits)
 * First 15 bits are used to encode cell state in base 3
 * Last bit can be used to store whatever you wish
 *
 * Keep in mind that the board should be initialized with EMPTY_BOARD (0)
 * */

/* 
 * ceiling( ln_2( 3^9 -1 ) ) = 15 (bytes used to store information)
 * 2^15 -1 = 32767 (the mask to use)
 *
 * As sizeof(unsigned short) * 8 = 16 we have an extra bit to spare.
 */

/* Type Definitions */
typedef unsigned short board_t;
#define EMPTY_BOARD 0
#define BOARD_MASK 32767
enum position_t { TOP_LEFT=0, TOP_CENTER=1, TOP_RIGHT=2, CENTER_LEFT=3, CENTER_CENTER=4, CENTER_RIGHT=5, BOTTOM_LEFT=6, BOTTOM_CENTER=7, BOTTOM_RIGHT=8 };
enum cell_status_t { EMPTY=0, CROSS=1, CIRCLE=2 };

/* Cell manipulation functions */
enum cell_status_t getCell( board_t board, enum position_t position );
board_t setCell ( board_t board, enum position_t position, enum cell_status_t newStatus );
/* Spare bit manipulation functions */
unsigned char getLastBit ( board_t board );
board_t setLastBit ( board_t board, unsigned char extra );

/* Implementation */
unsigned char getLastBit ( board_t board ) {
	return board & ~BOARD_MASK ? 1 : 0;
}

board_t setLastBit ( board_t board, unsigned char extra ) {
	if( extra ) {
		return ( board & BOARD_MASK ) | ~BOARD_MASK;
	} else {
		return board & BOARD_MASK;
	}
}

enum cell_status_t getCell( board_t board, enum position_t position ) {
	board &= BOARD_MASK;
	while( position-- ) board /= 3;
	return board % 3;
}

board_t setCell ( board_t board, enum position_t position, enum cell_status_t newStatus ) {
	board_t extra = board & ~BOARD_MASK;
	unsigned short oldStatus = getCell(board, position);
	while( position-- ) {
		oldStatus *= 3;
		newStatus *= 3;
	}
	return ( ( board & BOARD_MASK ) - oldStatus + newStatus ) | extra;
}

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
			cellValue(getCell(board, TOP_LEFT)), cellValue(getCell(board, TOP_CENTER)), cellValue(getCell(board, TOP_RIGHT)),
			cellValue(getCell(board, CENTER_LEFT)), cellValue(getCell(board, CENTER_CENTER)), cellValue(getCell(board, CENTER_RIGHT)),
			cellValue(getCell(board, BOTTOM_LEFT)), cellValue(getCell(board, BOTTOM_CENTER)), cellValue(getCell(board, BOTTOM_RIGHT)),
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

