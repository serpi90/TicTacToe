#ifndef BOARD_PRINT_H
#define BOARD_PRINT_H

char cellValue( enum position_t value ) {
	switch (value) {
		case EMPTY: return ' ';
		case CROSS: return 'X';
		case CIRCLE: return 'O';
		default: return '?';
	}
}

void printBoard( unsigned short board ) {
	printf(" %c | %c | %c \n---+---+---\n %c | %c | %c \n---+---+---\n %c | %c | %c \n\nLastBit: %hu\n\n",
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

#endif /* BOARD_PRINT_H */
