/**
 * Store a tic-tac-toe board using an unsigned in (32 bits)
 * First 18 bits are used to encode cell state in base 2
 * Last 14 bits can be used to store whatever you wish
 * EMPTY = 00
 * CROSS = 01
 * CIRCLE= 10
 * OTHER = 11
 * */

#ifndef BOARD_INT_H
#define BOARD_INT_H

/* Type Definitions */
typedef unsigned int board_t;
#define EMPTY_BOARD 0
#define BOARD_MASK 0x3FFFF

/* Cell manipulation functions */

enum cell_status_t getCell( board_t board, enum position_t position ) {
	return ( board >> (position*2) ) & 0x3;
}

board_t setCell ( board_t board, enum position_t position, enum cell_status_t newStatus ) {
	unsigned char offset = position * 2;
	return ( board & ~(0x3 << offset) ) | (newStatus << offset);
}

#endif /* BOARD_INT_H */
