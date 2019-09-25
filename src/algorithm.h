#ifndef _ALGORITHM_
#define _ALGORITHM_

// Function returns how many tiles that can be flipped over for a given direction
int howManyTilesCanBeFlipped(int n, char board[26][26], int numRow, int numCol, char colourOfComputer, int deltaRow, int deltaCol);

// Returns true if direction is valid, returns false if direction is not valid
bool isDirectionAValidMove(int n, char board[26][26], int numRow, int numCol, char colour, int deltaRow, int deltaCol);

#endif