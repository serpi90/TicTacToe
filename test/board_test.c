#ifndef BOARD_TESTS_C
#define BOARD_TESTS_C

#include <CUnit/CUnit.h>

#include "board_test.h"

board_t exampleBoard( void ) {
	board_t board = ~BOARD_MASK;
	board = setCell( board, TOP_LEFT, CROSS );
	board = setCell( board, TOP_CENTER, EMPTY );
	board = setCell( board, TOP_RIGHT, CIRCLE );
	board = setCell( board, CENTER_LEFT, EMPTY );
	board = setCell( board, CENTER_CENTER, CIRCLE );
	board = setCell( board, CENTER_RIGHT, CROSS );
	board = setCell( board, BOTTOM_LEFT, CIRCLE );
	board = setCell( board, BOTTOM_CENTER, CROSS );
	board = setCell( board, BOTTOM_RIGHT, EMPTY );
	return board;
}

void test_setAndGetCellOnEmptyBoard ( ) {
	enum position_t position = 0;
	enum cell_status_t status = 0;
	for( position = 0; position < 9; position++ ) {
		for( status = 0; status < 4; status++ ) {
			CU_ASSERT_TRUE( getCell( EMPTY_BOARD, position ) == EMPTY );
			CU_ASSERT_TRUE( getCell( setCell( EMPTY_BOARD, position, EMPTY ), position ) == EMPTY );
			CU_ASSERT_TRUE( getCell( setCell( EMPTY_BOARD, position, CROSS ), position ) == CROSS );
			CU_ASSERT_TRUE( getCell( setCell( EMPTY_BOARD, position, CIRCLE ), position ) == CIRCLE );
		}
	}
}

void test_fullBoard( void ) {
	board_t board = exampleBoard( );
	CU_ASSERT_EQUAL( board & ~BOARD_MASK, ( board_t ) ~BOARD_MASK );
	CU_ASSERT_EQUAL( getCell( board, TOP_LEFT ), CROSS );
	CU_ASSERT_EQUAL( getCell( board, TOP_CENTER ), EMPTY );
	CU_ASSERT_EQUAL( getCell( board, TOP_RIGHT ), CIRCLE );
	CU_ASSERT_EQUAL( getCell( board, CENTER_LEFT ), EMPTY );
	CU_ASSERT_EQUAL( getCell( board, CENTER_CENTER ), CIRCLE );
	CU_ASSERT_EQUAL( getCell( board, CENTER_RIGHT ), CROSS );
	CU_ASSERT_EQUAL( getCell( board, BOTTOM_LEFT ), CIRCLE );
	CU_ASSERT_EQUAL( getCell( board, BOTTOM_CENTER ), CROSS );
	CU_ASSERT_EQUAL( getCell( board, BOTTOM_RIGHT ), EMPTY );
}

#endif /* BOARD_TESTS_C */
