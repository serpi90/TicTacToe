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

#ifndef BOARD_SHORT_H
#define BOARD_SHORT_H

/* Type Definitions */
typedef unsigned short board_t;
#define EMPTY_BOARD 0
#define BOARD_MASK 0x7FFF

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
		return board | ~BOARD_MASK;
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

#endif /* BOARD_SHORT_H */
