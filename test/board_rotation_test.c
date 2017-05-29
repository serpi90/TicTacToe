#ifndef BOARD_ROTATION_TESTS_C
#define BOARD_ROTATION_TESTS_C

#include <CUnit/CUnit.h>

#include "board_rotation_test.h"

board_t rotationExampleBoard( void ) {
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

void test_rotateLeft( void ) {
	board_t board, rotated;

	/* Base Case */
	CU_ASSERT_EQUAL( rotateLeft( EMPTY_BOARD ), EMPTY_BOARD );

	/* Simple Case */
	board = setCell( EMPTY_BOARD, TOP_RIGHT, CIRCLE );
	rotated =  setCell( EMPTY_BOARD, TOP_LEFT, CIRCLE );
	CU_ASSERT_EQUAL( rotateLeft( board ), rotated );

	/* Full Board */
	board = rotationExampleBoard( );
	rotated = rotateLeft( board );
	CU_ASSERT_EQUAL( getCell( rotated, TOP_LEFT ), getCell( board, TOP_RIGHT ) );
	CU_ASSERT_EQUAL( getCell( rotated, TOP_CENTER ), getCell( board, CENTER_RIGHT ) );
	CU_ASSERT_EQUAL( getCell( rotated, TOP_RIGHT ), getCell( board, BOTTOM_RIGHT ) );
	CU_ASSERT_EQUAL( getCell( rotated, CENTER_RIGHT ), getCell( board, BOTTOM_CENTER ) );
	CU_ASSERT_EQUAL( getCell( rotated, BOTTOM_RIGHT ), getCell( board, BOTTOM_LEFT ) );
	CU_ASSERT_EQUAL( getCell( rotated, BOTTOM_CENTER ), getCell( board, CENTER_LEFT ) );
	CU_ASSERT_EQUAL( getCell( rotated, BOTTOM_LEFT ), getCell( board, TOP_LEFT ) );
	CU_ASSERT_EQUAL( getCell( rotated, CENTER_LEFT ), getCell( board, TOP_CENTER ) );
	CU_ASSERT_EQUAL( getCell( rotated, CENTER_CENTER ), getCell( board, CENTER_CENTER ) );

	/* Rotation a square board 4 times preserves state */
	CU_ASSERT_EQUAL( rotateLeft( rotateLeft( rotateLeft( rotateLeft( board ) ) ) ), board );
}

void test_rotateRight( void ) {
	board_t board, rotated;

	/* Base Case */
	CU_ASSERT_EQUAL( rotateRight( EMPTY_BOARD ), EMPTY_BOARD );

	/* Simple Case */
	board = setCell( EMPTY_BOARD, TOP_LEFT, CIRCLE );
	rotated = setCell( EMPTY_BOARD, TOP_RIGHT, CIRCLE );
	CU_ASSERT_EQUAL( rotateRight( board ), rotated );

	/* Full Board */
	board = rotationExampleBoard( );
	rotated = rotateRight( board );
	CU_ASSERT_EQUAL( getCell( rotated, TOP_RIGHT ), getCell( board, TOP_LEFT ) );
	CU_ASSERT_EQUAL( getCell( rotated, CENTER_RIGHT ), getCell( board, TOP_CENTER ) );
	CU_ASSERT_EQUAL( getCell( rotated, BOTTOM_RIGHT ), getCell( board, TOP_RIGHT ) );
	CU_ASSERT_EQUAL( getCell( rotated, BOTTOM_CENTER ), getCell( board, CENTER_RIGHT ) );
	CU_ASSERT_EQUAL( getCell( rotated, BOTTOM_LEFT ), getCell( board, BOTTOM_RIGHT ) );
	CU_ASSERT_EQUAL( getCell( rotated, CENTER_LEFT ), getCell( board, BOTTOM_CENTER ) );
	CU_ASSERT_EQUAL( getCell( rotated, TOP_LEFT ), getCell( board, BOTTOM_LEFT ) );
	CU_ASSERT_EQUAL( getCell( rotated, TOP_CENTER ), getCell( board, CENTER_LEFT ) );
	CU_ASSERT_EQUAL( getCell( rotated, CENTER_CENTER ), getCell( board, CENTER_CENTER ) );

	/* Rotation a square board 4 times preserves state */
	CU_ASSERT_EQUAL( rotateRight( rotateRight( rotateRight( rotateRight( board ) ) ) ), board );
}

void test_rotationQueries( void ) {
	board_t board = rotationExampleBoard( );
	board_t rotated = board;
	short rotations = 0;
	CU_ASSERT_TRUE( isRotation( EMPTY_BOARD, EMPTY_BOARD ) );
	CU_ASSERT_EQUAL( rotationsLeft( EMPTY_BOARD, EMPTY_BOARD ), 0 );
	CU_ASSERT_EQUAL( rotationsRight( EMPTY_BOARD, EMPTY_BOARD ), 0 );

	CU_ASSERT_TRUE( isRotation( board, board ) );
	CU_ASSERT_EQUAL( rotationsLeft( board, board ), 0 );
	CU_ASSERT_EQUAL( rotationsRight( board, board ), 0 );

	CU_ASSERT_FALSE( isRotation( EMPTY_BOARD, board ) );
	CU_ASSERT_EQUAL( rotationsLeft( EMPTY_BOARD, board ), -1 );
	CU_ASSERT_EQUAL( rotationsRight( EMPTY_BOARD, board ), -1 );

	for( rotations = 0, rotated = board;  rotations < 4 ; rotations ++ ) {
		CU_ASSERT_TRUE( isRotation( board, rotated ) );
		CU_ASSERT_EQUAL( rotationsLeft( rotated, board ), rotations );
		CU_ASSERT_EQUAL( rotationsRight( rotated, board ), ( 4 - rotations ) % 4 );
		rotated = rotateLeft( rotated );
	}
}

void test_verticalReflection( void ) {
	board_t board = rotationExampleBoard( );
	board_t reflection = verticalReflection( board );

	CU_ASSERT_EQUAL( verticalReflection( EMPTY_BOARD ), EMPTY_BOARD );

	CU_ASSERT_EQUAL( getCell( reflection, TOP_LEFT ), getCell( board, BOTTOM_LEFT ) );
	CU_ASSERT_EQUAL( getCell( reflection, BOTTOM_LEFT ), getCell( board, TOP_LEFT ) );
	CU_ASSERT_EQUAL( getCell( reflection, TOP_CENTER ), getCell( board, BOTTOM_CENTER ) );
	CU_ASSERT_EQUAL( getCell( reflection, BOTTOM_CENTER ), getCell( board, TOP_CENTER ) );
	CU_ASSERT_EQUAL( getCell( reflection, TOP_RIGHT ), getCell( board, BOTTOM_RIGHT ) );
	CU_ASSERT_EQUAL( getCell( reflection, BOTTOM_RIGHT ), getCell( board, TOP_RIGHT ) );

	CU_ASSERT_EQUAL( getCell( reflection, CENTER_LEFT ), getCell( board, CENTER_LEFT ) );
	CU_ASSERT_EQUAL( getCell( reflection, CENTER_CENTER ), getCell( board, CENTER_CENTER ) );
	CU_ASSERT_EQUAL( getCell( reflection, CENTER_RIGHT ), getCell( board, CENTER_RIGHT ) );
}

void test_horizontalReflection( void ) {
	board_t board = rotationExampleBoard( );
	board_t reflection = horizontalReflection( board );

	CU_ASSERT_EQUAL( horizontalReflection( EMPTY_BOARD ), EMPTY_BOARD );

	CU_ASSERT_EQUAL( getCell( reflection, TOP_LEFT ), getCell( board, TOP_RIGHT ) );
	CU_ASSERT_EQUAL( getCell( reflection, TOP_RIGHT ), getCell( board, TOP_LEFT ) );
	CU_ASSERT_EQUAL( getCell( reflection, CENTER_LEFT ), getCell( board, CENTER_RIGHT ) );
	CU_ASSERT_EQUAL( getCell( reflection, CENTER_RIGHT ), getCell( board, CENTER_LEFT ) );
	CU_ASSERT_EQUAL( getCell( reflection, BOTTOM_LEFT ), getCell( board, BOTTOM_RIGHT ) );
	CU_ASSERT_EQUAL( getCell( reflection, BOTTOM_RIGHT ), getCell( board, BOTTOM_LEFT ) );

	CU_ASSERT_EQUAL( getCell( reflection, TOP_CENTER ), getCell( board, TOP_CENTER ) );
	CU_ASSERT_EQUAL( getCell( reflection, CENTER_CENTER ), getCell( board, CENTER_CENTER ) );
	CU_ASSERT_EQUAL( getCell( reflection, BOTTOM_CENTER ), getCell( board, BOTTOM_CENTER ) );
}

void test_isIsometry( void ) {
	board_t board = rotationExampleBoard( );
	board_t isomtery = board;

	CU_ASSERT_TRUE( isIsometry( board, isomtery ) );
	isomtery = rotateLeft( isomtery );
	CU_ASSERT_TRUE( isIsometry( board, isomtery ) );
	isomtery = rotateLeft( isomtery );
	CU_ASSERT_TRUE( isIsometry( board, isomtery ) );
	isomtery = rotateLeft( isomtery );
	CU_ASSERT_TRUE( isIsometry( board, isomtery ) );

	isomtery = horizontalReflection( board );
	CU_ASSERT_TRUE( isIsometry( board, isomtery ) );
	isomtery = rotateLeft( isomtery );
	CU_ASSERT_TRUE( isIsometry( board, isomtery ) );
	isomtery = rotateLeft( isomtery );
	CU_ASSERT_TRUE( isIsometry( board, isomtery ) );
	isomtery = rotateLeft( isomtery );
	CU_ASSERT_TRUE( isIsometry( board, isomtery ) );
}

#endif /* BOARD_ROTATION_TESTS_C */
