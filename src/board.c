#ifndef BOARD_C
#define BOARD_C

#include "board.h"

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

#endif /* BOARD_C */
