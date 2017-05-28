/**
 * Store a tic-tac-toe board using an unsigned short (16 bits)
 * First 15 bits are used to encode cell state in base 3
 * Last bit can be used to store whatever you wish
 * EMPTY = 0,
 * CROSS = 1,
 * CIRCLE= 2
 * Ceiling( ln_2( 3^9 - 1 ) ) = 15 (bytes used to store information)
 * Last bit can be used to store whatever you with
 *
 * Keep in mind that the board should be initialized with EMPTY_BOARD (0),
 * having something else in the first 15 bits will mess the encoding.
 */

#ifndef BOARD_SHORT_H
#define BOARD_SHORT_H

/* Type Definitions */
typedef unsigned short board_t;
#define EMPTY_BOARD 0
/* 15 bits */
#define BOARD_MASK 0x7FFF

/* Cell manipulation functions */

enum cell_status_t getCell( board_t board, enum position_t position ) {
	board &= BOARD_MASK;
	while( position-- ) board /= 3;
	return board % 3;
}

board_t setCell ( board_t board, enum position_t position, enum cell_status_t newStatus ) {
	unsigned short oldStatus = getCell(board, position);
	while( position-- ) {
		oldStatus *= 3;
		newStatus *= 3;
	}
	return board - oldStatus + newStatus;
}

#endif /* BOARD_SHORT_H */
