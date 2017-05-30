#ifndef TEST_SUITE_C
#define TEST_SUITE_C

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "board_test.h"
#include "board_rotation_test.h"

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
	CU_add_test( pSuite, "Reflection Query", test_isReflection );
	CU_add_test( pSuite, "Isometry", test_isIsometry );

	CU_basic_set_mode( CU_BRM_VERBOSE );
	CU_basic_run_tests( );
	CU_cleanup_registry( );
	return CU_get_error( );
}

#endif /* TEST_SUITE_C */
