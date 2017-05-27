#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "position.h"
#include "cell_status.h"
#include "board_short.h"
#include "board_rotation.h"

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

	pSuite = CU_add_suite( "Board Isometry Tests", NULL, NULL );
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
