#ifndef _ALGORITHM_
#define _ALGORITHM_

// Function returns how many tiles that can be flipped over for a given direction
int howManyTilesCanBeFlipped(int n, char board[26][26], int numRow, int numCol, char colourOfComputer, int deltaRow, int deltaCol);

// Returns true if direction is valid, returns false if direction is not valid
bool isDirectionAValidMove(int n, char board[26][26], int numRow, int numCol, char colour, int deltaRow, int deltaCol);

// Finds value of position at corner, side or in the middle
int cornerSideMiddle(int n, int numRow, int numCol);

// Function determines how many tiles can be flipped over
int changeTilesOnBoardForMyAlgorithm(int n, char board[26][26], int numRow, int numCol, char colourOfPlayer, int deltaRow, int deltaCol);

// Function determines how many moves my own algorithm can make at a given turn
double maximizeNumberOfMovesICanMake(int n, char board2[26][26], int row, int col, char colourOfComputer);

// Return a heuristic computed value for where the best position would be to place a marker
double finalValue(int n, char board[26][26], int row, int col, char colourOfComputer);

// Initial version of my own implemented algorithm
void computerAlgorithm(int n, char board[26][26], char colourOfComputer);

#endif