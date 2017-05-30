#ifndef BOARD_C
#define BOARD_C

#include "board.h"

enum cell_status_t getCell( board_t board, enum position_t position ) {
	return ( board >> ( position * 2 ) ) & 0x3;
}

board_t setCell ( board_t board, enum position_t position, enum cell_status_t newStatus ) {
	unsigned char offset = position * 2;
	/* Remove the old status bits, and set the new status bits */
	return ( board & ~( 0x3 << offset ) ) | ( newStatus << offset );
}

#endif /* BOARD_C */
