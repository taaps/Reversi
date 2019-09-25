#include <stdio.h>
#include <stdbool.h>
#include "algorithm.h"

// Function returns how many tiles that can be flipped over for a given direction
int howManyTilesCanBeFlipped(int n, char board[26][26], int numRow, int numCol, char colourOfComputer, int deltaRow, int deltaCol)
{
	numRow -= deltaRow;
	numCol += deltaCol;
	int count = 0;
	int totalCountIfDirectionPossible = 0;
	
	while ((positionInBounds(n, numRow, numCol)) && (board[numRow][numCol] != colourOfComputer) && (board[numRow][numCol] != 'U'))
	{
		count++;
		numRow -= deltaRow;
		numCol += deltaCol;
		
		if((board[numRow][numCol] == colourOfComputer) && (positionInBounds(n, numRow, numCol)))
		{
			totalCountIfDirectionPossible = count;
			break;
		}
	}
	
	return totalCountIfDirectionPossible;
}

// Returns true if direction is valid, returns false if direction is not valid
bool isDirectionAValidMove(int n, char board[26][26], int numRow, int numCol, char colour, int deltaRow, int deltaCol)
{
	numRow -= deltaRow;
	numCol += deltaCol;
	bool returnValue = false;
	
	while((positionInBounds(n, numRow, numCol)) && (board[numRow][numCol] != colour) && (board[numRow][numCol] != 'U'))
	{
		numRow -= deltaRow;
		numCol += deltaCol;
		
		if ((board[numRow][numCol] == 'U') && (positionInBounds(n, numRow, numCol)))
		{
			returnValue = true;
		}
	}
	return returnValue;
}

// Finds value of position at corner, side or in the middle
int cornerSideMiddle(int n, int numRow, int numCol)
{
	int valueOfPosition=1;
	
	if (((numRow == 0) && (numCol == 0))||((numRow == 0) && (numCol == (n-1))) ||((numRow == (n-1) && (numCol == 0))) ||(numRow == (n-1) && (numCol == (n-1))))
	{
		valueOfPosition = 3;
	}
	else if ((numRow == 0) || (numCol == 0) || (numRow == (n-1)) || (numCol == (n-1)))
	{
		valueOfPosition = 2;
	}
	
	return valueOfPosition;
}
