#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>

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

void test_rotateLeft( void ) {
	board_t board, rotated;

	/* Base Case */
	CU_ASSERT_EQUAL( rotateLeft( EMPTY_BOARD ), EMPTY_BOARD );

	/* Simple Case */
	board = setCell( EMPTY_BOARD, TOP_RIGHT, CIRCLE );
	rotated =  setCell( EMPTY_BOARD, TOP_LEFT, CIRCLE );
	CU_ASSERT_EQUAL( rotateLeft( board ), rotated );

	/* Full Board */
	board = exampleBoard( );
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
	board = exampleBoard( );
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
	board_t board = exampleBoard( );
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
	board_t board = exampleBoard( );
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
	board_t board = exampleBoard( );
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
	board_t board = exampleBoard( );
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

int main( ) {
	CU_pSuite pSuite = NULL;

	if ( CUE_SUCCESS != CU_initialize_registry( ) ) {
		return CU_get_error( );
	}

	pSuite = CU_add_suite( "Board Tests", NULL, NULL );
	if ( NULL == pSuite ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	CU_add_test( pSuite, "Set & Get single Cells on an Empty Board", test_setAndGetCellOnEmptyBoard );
	CU_add_test( pSuite, "Set & Get a full board", test_fullBoard );

	pSuite = CU_add_suite( "Board Isometry Tests", NULL, NULL );
	if ( NULL == pSuite ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	CU_add_test( pSuite, "Rotate Board Left", test_rotateLeft );
	CU_add_test( pSuite, "Rotate Board Right", test_rotateRight );
	CU_add_test( pSuite, "Queries for: Is Rotation, Rotations to Left and Rotations to Right", test_rotationQueries );
	CU_add_test( pSuite, "Vertical Reflection", test_verticalReflection );
	CU_add_test( pSuite, "Horizontal Reflection", test_horizontalReflection );
	CU_add_test( pSuite, "Isometry", test_isIsometry );

	CU_set_output_filename( BOARD_BASE == 3 ? "short" : "int");
	CU_automated_run_tests( );
	CU_cleanup_registry( );
	return CU_get_error( );
}
