#include <stdio.h>
#include <stdbool.h>
#include "board_functions.h"

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