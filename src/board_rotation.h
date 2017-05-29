#ifndef BOARD_ROTATION_H
#define BOARD_ROTATION_H

board_t rotateLeft( board_t board );
board_t rotateRight( board_t board );
board_t horizontalReflection( board_t board );
board_t verticalReflection( board_t board );

/* True if @botherBoard is a rotation of @board*/
int isRotation( board_t board, board_t otherBoard );
/* True if @botherBoard is a reflection of @board*/
int isReflection( board_t board, board_t otherBoard );
/* True if @botherBoard is a combination of rotations + reflections of @board*/
int isIsometry( board_t board, board_t otherBoard );
/* Number of rotations to the left needed for @otherBoard == @board
 * -1 if not possible */
int rotationsLeft( board_t board, board_t otherBoard );
/* Number of rotations to the right needed for @otherBoard == @board
 * -1 if not possible */
int rotationsRight( board_t board, board_t otherBoard );

#endif /* BOARD_ROTATION_H */
