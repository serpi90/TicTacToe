#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "position.h"
#include "cell_status.h"
#include "board_short.h"
#include "board_rotation.h"
#include "board_print.h"

void test_getCell(void) {
	board_t board = EMPTY_BOARD;
	CU_ASSERT_TRUE( getCell( 0, TOP_LEFT ) == EMPTY );
	CU_ASSERT_TRUE( getCell( 1, TOP_LEFT ) == CROSS );
	CU_ASSERT_TRUE( getCell( 2, TOP_LEFT ) == CIRCLE );

	CU_ASSERT_TRUE( getCell( 3, TOP_LEFT ) == EMPTY );
	CU_ASSERT_TRUE( getCell( 3, TOP_CENTER ) == CROSS );

	CU_ASSERT_TRUE( getCell( 4, TOP_LEFT ) == CROSS );
	CU_ASSERT_TRUE( getCell( 4, TOP_CENTER ) == CROSS );

	CU_ASSERT_TRUE( getCell( 5, TOP_LEFT ) == CIRCLE );
	CU_ASSERT_TRUE( getCell( 4, TOP_CENTER ) == CROSS );

	CU_ASSERT_TRUE( getCell( 13122, BOTTOM_RIGHT ) == CIRCLE );
	CU_ASSERT_TRUE( getCell( 6561, BOTTOM_RIGHT ) == CROSS );

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
	CU_ASSERT_TRUE( board == 4069 );

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

#ifdef BOARD_SHORT_H
void test_lastBit(void) {
	CU_ASSERT_EQUAL( getLastBit ( EMPTY_BOARD ), 0 );
	CU_ASSERT_EQUAL( getLastBit ( setLastBit( EMPTY_BOARD, 0 ) ), 0 );
	CU_ASSERT_EQUAL( getLastBit ( setLastBit( EMPTY_BOARD, 1 ) ), 1 );
}
#endif /* BOARD_SHORT_H */

void test_isRotation(void) {
	board_t top_right_circle;
	CU_ASSERT_TRUE( isRotation( EMPTY_BOARD, EMPTY_BOARD ) );
	top_right_circle = setCell( EMPTY_BOARD, TOP_RIGHT, CIRCLE );
	CU_ASSERT_TRUE( isRotation( top_right_circle, setCell( EMPTY_BOARD, TOP_RIGHT, CIRCLE ) ) );
	CU_ASSERT_EQUAL( rotationsLeft( top_right_circle, setCell( EMPTY_BOARD, TOP_RIGHT, CIRCLE ) ), 0 );

	CU_ASSERT_TRUE( isRotation( top_right_circle, setCell( EMPTY_BOARD, BOTTOM_RIGHT, CIRCLE ) ) );
	CU_ASSERT_EQUAL( rotationsLeft( top_right_circle, setCell( EMPTY_BOARD, BOTTOM_RIGHT, CIRCLE ) ), 1 );

	CU_ASSERT_TRUE( isRotation( top_right_circle, setCell( EMPTY_BOARD, BOTTOM_LEFT, CIRCLE ) ) );
	CU_ASSERT_EQUAL( rotationsLeft( top_right_circle, setCell( EMPTY_BOARD, BOTTOM_LEFT, CIRCLE ) ), 2 );

	CU_ASSERT_TRUE( isRotation( top_right_circle, setCell( EMPTY_BOARD, TOP_LEFT, CIRCLE ) ) );
	CU_ASSERT_EQUAL( rotationsLeft( top_right_circle, setCell( EMPTY_BOARD, TOP_LEFT, CIRCLE ) ), 3 );
}

void test_rotateLeft(void) {
	board_t board;
	CU_ASSERT_EQUAL( rotateLeft( EMPTY_BOARD ), EMPTY_BOARD );
	board = setCell( EMPTY_BOARD, TOP_RIGHT, CIRCLE );
	CU_ASSERT_EQUAL( rotateLeft( board ), setCell( EMPTY_BOARD, TOP_LEFT, CIRCLE ) );
	board = 4069;
	CU_ASSERT_EQUAL( rotateLeft( rotateLeft( rotateLeft( rotateLeft( board ) ) ) ), board );
}

void test_rotateRight(void) {
	board_t board = 4069;
	CU_ASSERT_NOT_EQUAL( 4069, rotateRight( board ) );
	CU_ASSERT_EQUAL( board, rotateLeft( rotateRight( board ) ) );
	CU_ASSERT_EQUAL( rotateLeft( rotateLeft( board ) ), rotateRight( rotateRight( board ) ) );
}

void test_reflection(void) {
	board_t top_right_circle;
	CU_ASSERT_EQUAL( horizontalReflection( EMPTY_BOARD ), verticalReflection( EMPTY_BOARD ) );
	top_right_circle = setCell( EMPTY_BOARD, TOP_RIGHT, CIRCLE );
	CU_ASSERT_NOT_EQUAL( top_right_circle, horizontalReflection(top_right_circle) );
	CU_ASSERT_EQUAL( horizontalReflection(top_right_circle), setCell( EMPTY_BOARD, TOP_LEFT, CIRCLE ) );
	CU_ASSERT_EQUAL( verticalReflection(top_right_circle), setCell( EMPTY_BOARD, BOTTOM_RIGHT, CIRCLE ) );
}

void test_isIsometry(void) {
	board_t board = 4069;
	CU_ASSERT_TRUE(
		isIsometry(
			board,
			rotateLeft( rotateLeft ( horizontalReflection(board) ) )
		)
	);
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
#ifdef BOARD_SHORT_H
	CU_add_test( pSuite, "lastBit", test_lastBit );
#endif /* BOARD_SHORT_H */

	pSuite = CU_add_suite( "Board Rotation Tests", NULL, NULL );
	if ( NULL == pSuite ) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_add_test( pSuite, "isRotation", test_isRotation );
	CU_add_test( pSuite, "rotateLeft", test_rotateLeft );
	CU_add_test( pSuite, "rotateRight", test_rotateRight );
	CU_add_test( pSuite, "reflection", test_reflection );
	CU_add_test( pSuite, "isIsometry", test_isIsometry );

	CU_basic_set_mode( CU_BRM_VERBOSE );
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
