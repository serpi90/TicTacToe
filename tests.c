#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"

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

void test_getCell(void) {
	board_t board = EMPTY_BOARD;
	CU_ASSERT( getCell( 0, TOP_LEFT ) == EMPTY );
	CU_ASSERT( getCell( 1, TOP_LEFT ) == CROSS );
	CU_ASSERT( getCell( 2, TOP_LEFT ) == CIRCLE );

	CU_ASSERT( getCell( 3, TOP_LEFT ) == EMPTY );
	CU_ASSERT( getCell( 3, TOP_CENTER ) == CROSS );

	CU_ASSERT( getCell( 4, TOP_LEFT ) == CROSS );
	CU_ASSERT( getCell( 4, TOP_CENTER ) == CROSS );

	CU_ASSERT( getCell( 5, TOP_LEFT ) == CIRCLE );
	CU_ASSERT( getCell( 4, TOP_CENTER ) == CROSS );

	CU_ASSERT( getCell( 13122, BOTTOM_RIGHT ) == CIRCLE );
	CU_ASSERT( getCell( 6561, BOTTOM_RIGHT ) == CROSS );

	/*
	 * Stored in base 3,
	 * TOP_LEFT being the least significant
	 * TOP_CENTER the next
	 * ...
	 * BOTTOM_RIGHT the most significant
	 *
	 * base 10 -> base 3 -> meaning
	 * 4069 -> 012 120 201 -> .XO XO. O.X
	 * Should match this board:
	 * X.O
	 * .OX
	 * OX.
	 */
 	board = 4069;
	CU_ASSERT( getCell( board, TOP_LEFT ) == CROSS );
	CU_ASSERT( getCell( board, TOP_CENTER ) == EMPTY );
	CU_ASSERT( getCell( board, TOP_RIGHT ) == CIRCLE );

	CU_ASSERT( getCell( board, CENTER_LEFT ) == EMPTY );
	CU_ASSERT( getCell( board, CENTER_CENTER ) == CIRCLE );
	CU_ASSERT( getCell( board, CENTER_RIGHT ) == CROSS );

	CU_ASSERT( getCell( board, BOTTOM_LEFT ) == CIRCLE );
	CU_ASSERT( getCell( board, BOTTOM_CENTER ) == CROSS );
	CU_ASSERT( getCell( board, BOTTOM_RIGHT ) == EMPTY );
}

void test_setCell(void) {
	board_t board = EMPTY_BOARD;
	CU_ASSERT( getCell( setCell( board, TOP_LEFT, EMPTY ), TOP_LEFT ) == EMPTY );
	CU_ASSERT( getCell( setCell( board, TOP_LEFT, CROSS ), TOP_LEFT ) == CROSS );
	CU_ASSERT( getCell( setCell( board, TOP_LEFT, CIRCLE ), TOP_LEFT ) == CIRCLE );

	CU_ASSERT( getCell( setCell( board, BOTTOM_RIGHT, EMPTY ), BOTTOM_RIGHT ) == EMPTY );
	CU_ASSERT( getCell( setCell( board, BOTTOM_RIGHT, CROSS ), BOTTOM_RIGHT ) == CROSS );
	CU_ASSERT( getCell( setCell( board, BOTTOM_RIGHT, CIRCLE ), BOTTOM_RIGHT ) == CIRCLE );

	board = setCell( board, TOP_LEFT, CROSS );
	board = setCell( board, TOP_CENTER, EMPTY );
	board = setCell( board, TOP_RIGHT, CIRCLE );

	board = setCell( board, CENTER_LEFT, EMPTY );
	board = setCell( board, CENTER_CENTER, CIRCLE );
	board = setCell( board, CENTER_RIGHT, CROSS );

	board = setCell( board, BOTTOM_LEFT, CIRCLE );
	board = setCell( board, BOTTOM_CENTER, CROSS );
	board = setCell( board, BOTTOM_RIGHT, EMPTY );

	/* See comment in test_getCell */
	CU_ASSERT( board == 4069 );

	CU_ASSERT( getCell( board, TOP_LEFT ) == CROSS );
	CU_ASSERT( getCell( board, TOP_CENTER ) == EMPTY );
	CU_ASSERT( getCell( board, TOP_RIGHT ) == CIRCLE );

	CU_ASSERT( getCell( board, CENTER_LEFT ) == EMPTY );
	CU_ASSERT( getCell( board, CENTER_CENTER ) == CIRCLE );
	CU_ASSERT( getCell( board, CENTER_RIGHT ) == CROSS );

	CU_ASSERT( getCell( board, BOTTOM_LEFT ) == CIRCLE );
	CU_ASSERT( getCell( board, BOTTOM_CENTER ) == CROSS );
	CU_ASSERT( getCell( board, BOTTOM_RIGHT ) == EMPTY );

}

int main() {
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if ( CUE_SUCCESS != CU_initialize_registry() ) {
		return CU_get_error();
	}

	/* add a suite to the registry */
	pSuite = CU_add_suite( "Board Tests", NULL, NULL );
	if ( NULL == pSuite ) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	CU_add_test( pSuite, "getCell", test_getCell );
	CU_add_test( pSuite, "setCell", test_setCell );

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode( CU_BRM_VERBOSE );
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
