#include <stdio.h>
#include <stdbool.h>
#include "board_functions.h"


// Change char to a number
int changeCharToNumber(char a)
{
	int num;
	num = a - 97;
	return num;
}

// Change number to a char 
char changeNumberToChar(int n)
{
	char letter;
	letter = n + 97;
	return letter;
}

// Function prints the board contents
void printBoard(int n, char board[26][26])
{
	int boardRow = 0;
	char row[26];
	char col[26];
	char initialLetter = 'a';
	
	// Sets column and row of outer egdes of the board
	int i;
	for (i=0; i<n; i++)
	{
		row[i] = initialLetter;
		col[i] = initialLetter;
		initialLetter++;
	}
	
	printf("  ");
	for (i=0; i<n; i++)
		printf("%c", row[i]);
	
	printf("\n");
	int a;
	for (i=0; i<n; i++)
	{
		printf("%c ", col[i]);
		
		for(a=0; a<n; a++)
			printf("%c", board[boardRow][a]);
		
		printf("\n");
		boardRow++;
	}
}

// Switches the player that is playing
void switchPlayerPlaying(int *playerPlaying, int *playerSitting)
{
	int numberToSwitch = 0;
	numberToSwitch = *playerPlaying;
	*playerPlaying = *playerSitting;
	*playerSitting = numberToSwitch;
}

// Checks whether the given row and column lies within the board 
bool positionInBounds(int n, int row, int col)
{
	bool isPositionValid = false;
	if ((row < n) && (col < n) && (row >=0) && (col >=0))
	{
		isPositionValid = true;
	}

	return isPositionValid;
}

// Checks if move entered by human is legal (returns true if legal, false if illegal)
bool checkLegalInDirection(int n, char board[26][26], char humanRowInput, char humanColInput, char colourOfHuman, int deltaRow, int deltaCol)
{
	int numRow = changeCharToNumber(humanRowInput);
	int numCol = changeCharToNumber(humanColInput);
	bool isPositionLegal = false;
	
	if(board[numRow][numCol] == 'U' && positionInBounds(n, numRow, numCol))
	{
		numRow = numRow - deltaRow;
		numCol = numCol + deltaCol;
			
		if ((board[numRow][numCol] != 'U') && (board[numRow][numCol] != colourOfHuman) && (positionInBounds(n, numRow, numCol)))
		{
			numRow = numRow - deltaRow;
			numCol = numCol + deltaCol;
				
			while ((board[numRow][numCol] != 'U') && (positionInBounds(n, numRow, numCol)))
			{
				if (board[numRow][numCol] == colourOfHuman)
				{
					isPositionLegal = true;
					break;
				}
				
				numRow = numRow - deltaRow;
				numCol = numCol + deltaCol;
			}
		}
	}
	
	return isPositionLegal;
}

// If a specific direction from a colourOfPlayer piece is valid for tiles to change, this function will change the tiles to colourOfPlayer
void changeTilesOnBoard(int n, char board[26][26], int numRow, int numCol, char colourOfPlayer, int deltaRow, int deltaCol)
{
	int initialRow = numRow;
	int initialCol = numCol;
	numRow -= deltaRow;
	numCol += deltaCol;
	bool checkIfDirectionIsValid = false;
	
	while((board[numRow][numCol] != colourOfPlayer) && (positionInBounds(n, numRow, numCol)) && (board[numRow][numCol] != 'U'))
	{
		numRow -= deltaRow;
		numCol += deltaCol;
		
		if((board[numRow][numCol] == colourOfPlayer) && (positionInBounds(n, numRow, numCol)))
		{
			checkIfDirectionIsValid = true;
			break;
		}
	}
	
	if (checkIfDirectionIsValid == true)
	{
		initialRow -= deltaRow;
		initialCol += deltaCol;
			
		do
		{
			board[initialRow][initialCol] = colourOfPlayer;
			initialRow -= deltaRow;
			initialCol += deltaCol;
			
		} while (board[initialRow][initialCol] != colourOfPlayer);
	}
}

// Finds where the colourOfPlayer is located on the board and calls the changeTilesOnBoard function
void findTilePositionAndChange(int n, char board[26][26], char colourOfPlayer, int row, int col)
{
	int deltaRow = -1;
	int deltaCol = -1;
	
	int i;
	int j;
	for (i=-1; i<=1; i++)
	{
		for (j=-1; j<=1; j++)
		{
			changeTilesOnBoard(n, board, row, col, colourOfPlayer, deltaRow, deltaCol);
			deltaCol++;
		}
		deltaCol = -1;
		deltaRow++;
	}
}

// Checks whether the board is full or not
bool isBoardFull(int n, char board[26][26])
{
	int i;
	int j;
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			if (board[i][j] == 'U')
				return false;
	return true;
}

// True if has moves, false if doesn't have any moves
bool doesPlayerHaveAvailableMove(int n, char board[26][26], char colour)
{
	int deltaRow = -1;
	int deltaCol = -1;
	bool returnValue = false;
	
	int i;
	int j;
	int a;
	int b;
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			if (board[i][j] == colour)
			{
				for (a=-1; a<=1; a++)
				{
					for (b=-1; b<=1; b++)
					{
						if (isDirectionAValidMove(n, board, i, j, colour, deltaRow, deltaCol) == true)
							returnValue = true;
						deltaCol++;
					}
					deltaCol = -1;
					deltaRow++;
				}
			}
			deltaCol = -1;
			deltaRow = -1;
		}
	}
	
	return returnValue;
}
