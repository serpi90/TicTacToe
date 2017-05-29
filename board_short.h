/**
 * Store a tic-tac-toe board using an unsigned short ( 16 bits )
 * First 15 bits are used to encode cell state in base 3
 * Last bit can be used to store whatever you wish
 * EMPTY = 0,
 * CROSS = 1,
 * CIRCLE= 2
 * Ceiling( ln_2( 3^9 - 1 ) ) = 15 ( bytes used to store information )
 * Last bit can be used to store whatever you with
 *
 * Keep in mind that the board should be initialized with EMPTY_BOARD ( 0 ),
 * having something else in the first 15 bits will mess the encoding.
 */

#ifndef BOARD_SHORT_H
#define BOARD_SHORT_H

enum cell_status_t {
	EMPTY=0,
	CROSS=1,
	CIRCLE=2
};

enum position_t {
	TOP_LEFT=0,
	TOP_CENTER=1,
	TOP_RIGHT=2,
	CENTER_LEFT=7,
	CENTER_CENTER=8,
	CENTER_RIGHT=3,
	BOTTOM_LEFT=6,
	BOTTOM_CENTER=5,
	BOTTOM_RIGHT=4
};

/* Type Definitions */
typedef unsigned short board_t;
#define EMPTY_BOARD 0
/* 15 bits */
#define BOARD_MASK 0x7FFF
#define BOARD_BASE 3

/* Cell manipulation functions */

enum cell_status_t getCell( board_t board, enum position_t position ) {
	board &= BOARD_MASK;
	while( position-- ) board /= 3;
	return board % 3;
}

board_t setCell ( board_t board, enum position_t position, enum cell_status_t newStatus ) {
	unsigned short oldStatus = getCell( board, position );
	while( position-- ) {
		oldStatus *= 3;
		newStatus *= 3;
	}
	return board - oldStatus + newStatus;
}

#endif /* BOARD_SHORT_H */
