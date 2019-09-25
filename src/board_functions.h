#ifndef _BOARD_FUNCTIONS_
#define _BOARD_FUNCTIONS_

// Change char to a number
int changeCharToNumber(char a);

// Change number to a char 
char changeNumberToChar(int n);

// Function prints the board contents
void printBoard(int n, char board[26][26]);

// Switches the player that is playing
void switchPlayerPlaying(int *playerPlaying, int *playerSitting);

// Checks whether the given row and column lies within the board 
bool positionInBounds(int n, int row, int col);

// Checks if move entered by human is legal (returns true if legal, false if illegal)
bool checkLegalInDirection(int n, char board[26][26], char humanRowInput, char humanColInput, char colourOfHuman, int deltaRow, int deltaCol);

// If a specific direction from a colourOfPlayer piece is valid for tiles to change, this function will change the tiles to colourOfPlayer
void changeTilesOnBoard(int n, char board[26][26], int numRow, int numCol, char colourOfPlayer, int deltaRow, int deltaCol);

// Finds where the colourOfPlayer is located on the board and calls the changeTilesOnBoard function
void findTilePositionAndChange(int n, char board[26][26], char colourOfPlayer, int row, int col);

// Checks whether the board is full or not
bool isBoardFull(int n, char board[26][26]);

#endif