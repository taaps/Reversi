#ifndef _BOARD_FUNCTIONS_
#define _BOARD_FUNCTIONS_

// Function prints the board contents
void printBoard(int n, char board[26][26]);

// Switches the player that is playing
void switchPlayerPlaying(int *playerPlaying, int *playerSitting);

// Checks whether the given row and column lies within the board 
bool positionInBounds(int n, int row, int col);

#endif