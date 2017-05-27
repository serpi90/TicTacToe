#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "position.h"
#include "cell_status.h"
#include "board_int.h"
#include "board_print.h"

void test_getCell(void) {
	board_t board = EMPTY_BOARD;
	CU_ASSERT_TRUE( getCell( 0, TOP_LEFT ) == EMPTY );
	CU_ASSERT_TRUE( getCell( 1, TOP_LEFT ) == CROSS );
	CU_ASSERT_TRUE( getCell( 2, TOP_LEFT ) == CIRCLE );
	CU_ASSERT_TRUE( getCell( 3, TOP_LEFT ) == OTHER );

	CU_ASSERT_TRUE( getCell( 4, TOP_CENTER ) == CROSS );
	CU_ASSERT_TRUE( getCell( 4, TOP_LEFT ) == EMPTY );

	CU_ASSERT_TRUE( getCell( 6, TOP_CENTER ) == CROSS );
	CU_ASSERT_TRUE( getCell( 6, TOP_LEFT ) == CIRCLE );

	CU_ASSERT_TRUE( getCell( 0x10000, BOTTOM_RIGHT ) == CROSS );
	CU_ASSERT_TRUE( getCell( 0x20000, BOTTOM_RIGHT ) == CIRCLE );

	/*
	 * Stored in base 2,
	 * TOP_LEFT being the least significant
	 * TOP_CENTER the next
	 * ...
	 * BOTTOM_RIGHT the most significant
	 * EMPTY = 00
	 * CROSS = 01
	 * CIRCLE= 10
	 * OTHER = 11
	 *
	 * base 16 -> base 2 -> meaning
	 * 0x6621 -> 00 01 10 01 10 00 10 00 01 -> . XO XO .O .X
	 * Should match this board:
	 * X.O
	 * .OX
	 * OX.
	 */
 	board = 0x6621;
	CU_ASSERT_TRUE( getCell( board, TOP_LEFT ) == CROSS );
	CU_ASSERT_TRUE( getCell( board, TOP_CENTER ) == EMPTY );
	CU_ASSERT_TRUE( getCell( board, TOP_RIGHT ) == CIRCLE );

	CU_ASSERT_TRUE( getCell( board, CENTER_LEFT ) == EMPTY );
	CU_ASSERT_TRUE( getCell( board, CENTER_CENTER ) == CIRCLE );
	CU_ASSERT_TRUE( getCell( board, CENTER_RIGHT ) == CROSS );

	CU_ASSERT_TRUE( getCell( board, BOTTOM_LEFT ) == CIRCLE );
	CU_ASSERT_TRUE( getCell( board, BOTTOM_CENTER ) == CROSS );
	CU_ASSERT_TRUE( getCell( board, BOTTOM_RIGHT ) == EMPTY );
}

void test_setCell(void) {
	board_t board = EMPTY_BOARD;
	CU_ASSERT_TRUE( getCell( setCell( board, TOP_LEFT, EMPTY ), TOP_LEFT ) == EMPTY );
	CU_ASSERT_TRUE( getCell( setCell( board, TOP_LEFT, CROSS ), TOP_LEFT ) == CROSS );
	CU_ASSERT_TRUE( getCell( setCell( board, TOP_LEFT, CIRCLE ), TOP_LEFT ) == CIRCLE );

	CU_ASSERT_TRUE( getCell( setCell( board, BOTTOM_RIGHT, EMPTY ), BOTTOM_RIGHT ) == EMPTY );
	CU_ASSERT_TRUE( getCell( setCell( board, BOTTOM_RIGHT, CROSS ), BOTTOM_RIGHT ) == CROSS );
	CU_ASSERT_TRUE( getCell( setCell( board, BOTTOM_RIGHT, CIRCLE ), BOTTOM_RIGHT ) == CIRCLE );

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
	CU_ASSERT_EQUAL( board, 0x6621 );

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

int main() {
	CU_pSuite pSuite = NULL;

	if ( CUE_SUCCESS != CU_initialize_registry() ) {
		return CU_get_error();
	}

	pSuite = CU_add_suite( "Board Tests", NULL, NULL );
	if ( NULL == pSuite ) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	CU_add_test( pSuite, "getCell", test_getCell );
	CU_add_test( pSuite, "setCell", test_setCell );

	CU_basic_set_mode( CU_BRM_VERBOSE );
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
