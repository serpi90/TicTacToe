#ifndef BOARD_ROTATION_H
#define BOARD_ROTATION_H

unsigned char isRotation( board_t board, board_t otherBoard );
unsigned char isIsometry( board_t board, board_t otherBoard );

board_t rotateLeft( board_t board );
board_t rotateRight( board_t board );
board_t horizontalReflection( board_t board );

char rotationsLeft( board_t board, board_t otherBoard );

unsigned char isRotation( board_t board, board_t otherBoard ) {
  return rotationsLeft( board, otherBoard ) >= 0;
}

/* Number of rotations to the left needed for otherBoard == board, -1 if not possible */
char rotationsLeft( board_t board, board_t otherBoard ) {
  unsigned char times = 4;
  while ( times-- ) {
    if( board == otherBoard ) return 3 - times;
    otherBoard = rotateLeft(otherBoard);
  }
  return -1;
}

unsigned char isIsometry( board_t board, board_t otherBoard ) {
  return isRotation( board, otherBoard ) || isRotation( board, horizontalReflection(otherBoard) );
}

board_t horizontalReflection( board_t board ) {
  board_t horizontalReflection = board;
  horizontalReflection = setCell( horizontalReflection, TOP_LEFT, getCell( board, TOP_RIGHT ) );
  horizontalReflection = setCell( horizontalReflection, CENTER_LEFT, getCell( board, CENTER_RIGHT ) );
  horizontalReflection = setCell( horizontalReflection, BOTTOM_LEFT, getCell( board, BOTTOM_RIGHT ) );
  horizontalReflection = setCell( horizontalReflection, TOP_RIGHT, getCell( board, TOP_LEFT ) );
  horizontalReflection = setCell( horizontalReflection, CENTER_RIGHT, getCell( board, CENTER_LEFT ) );
  horizontalReflection = setCell( horizontalReflection, BOTTOM_RIGHT, getCell( board, BOTTOM_LEFT ) );
  return horizontalReflection;
}
/*
To check if matches only 1 reflection is needed
may not be the one with less combinations, but fewer checks are needed
V = verticalReflection, H = horizontalReflection, LN = rotateLeft N times
  Orig    |   L1      |   L2      |   L3
  X . .   |   . . .   |   . X X   |   X X X
  X . .   |   . . x   |   . . X   |   X . .
  X X .   |   X X X   |   . . X   |   . . .

  H       |   H+L1    |   H+L2    |   H+L3
  . . X   |   X X X   |   X X .   |   . . .
  . . X   |   . . X   |   X . .   |   X . .
  . X X   |   . . .   |   X . .   |   X X X

  V       |   V+L1    |   V+L2    |   V+L3
  H+L2    |   H+L3    |   H       |   H+L1
  X X .   |   . . .   |   . . X   |   X X X
  X . .   |   X . .   |   . . X   |   . . X
  X . .   |   X X X   |   . X X   |   . . .
*/
board_t verticalReflection( board_t board ) {
  board_t verticalReflection = board;
  verticalReflection = setCell( verticalReflection, TOP_LEFT, getCell( board, BOTTOM_LEFT ) );
  verticalReflection = setCell( verticalReflection, TOP_CENTER, getCell( board, BOTTOM_CENTER ) );
  verticalReflection = setCell( verticalReflection, TOP_RIGHT, getCell( board, BOTTOM_RIGHT ) );
  verticalReflection = setCell( verticalReflection, BOTTOM_LEFT, getCell( board, TOP_LEFT ) );
  verticalReflection = setCell( verticalReflection, BOTTOM_CENTER, getCell( board, TOP_CENTER ) );
  verticalReflection = setCell( verticalReflection, BOTTOM_RIGHT, getCell( board, TOP_RIGHT ) );
  return verticalReflection;
}

board_t rotateLeft( board_t board ) {
  board_t rotated = board;
  rotated = setCell( rotated, TOP_LEFT, getCell( board, TOP_RIGHT ) );
  rotated = setCell( rotated, TOP_CENTER, getCell( board, CENTER_RIGHT ) );
  rotated = setCell( rotated, TOP_RIGHT, getCell( board, BOTTOM_RIGHT ) );
  rotated = setCell( rotated, CENTER_RIGHT, getCell( board, BOTTOM_CENTER ) );
  rotated = setCell( rotated, BOTTOM_RIGHT, getCell( board, BOTTOM_LEFT ) );
  rotated = setCell( rotated, BOTTOM_CENTER, getCell( board, CENTER_LEFT ) );
  rotated = setCell( rotated, BOTTOM_LEFT, getCell( board, TOP_LEFT ) );
  rotated = setCell( rotated, CENTER_LEFT, getCell( board, TOP_CENTER ) );
  return rotated;
}

board_t rotateRight( board_t board ) {
  board_t rotated = board;
  rotated = setCell( rotated, TOP_RIGHT, getCell( board, TOP_LEFT ) );
  rotated = setCell( rotated, CENTER_RIGHT, getCell( board, TOP_CENTER ) );
  rotated = setCell( rotated, BOTTOM_RIGHT, getCell( board, TOP_RIGHT ) );
  rotated = setCell( rotated, BOTTOM_CENTER, getCell( board, CENTER_RIGHT ) );
  rotated = setCell( rotated, BOTTOM_LEFT, getCell( board, BOTTOM_RIGHT ) );
  rotated = setCell( rotated, CENTER_LEFT, getCell( board, BOTTOM_CENTER ) );
  rotated = setCell( rotated, TOP_LEFT, getCell( board, BOTTOM_LEFT ) );
  rotated = setCell( rotated, TOP_CENTER, getCell( board, CENTER_LEFT ) );
  return rotated;
}

#endif /* BOARD_ROTATION_H */
