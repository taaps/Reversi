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

// Function determines how many tiles can be flipped over
int changeTilesOnBoardForMyAlgorithm(int n, char board[26][26], int numRow, int numCol, char colourOfPlayer, int deltaRow, int deltaCol)
{
	int initialRow = numRow;
	int initialCol = numCol;
	numRow -= deltaRow;
	numCol += deltaCol;
	bool checkIfDirectionIsValid = false;
	int countHowManyTilesFlipped = 0;
	
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
			countHowManyTilesFlipped++;
			initialRow -= deltaRow;
			initialCol += deltaCol;
			
		} while (board[initialRow][initialCol] != colourOfPlayer);
	}
	
	return countHowManyTilesFlipped;
}

// Function determines how many moves my own algorithm can make at a given turn
double maximizeNumberOfMovesICanMake(int n, char board2[26][26], int row, int col, char colourOfComputer)
{
	board2[row][col] = colourOfComputer;
	int deltaRow = -1;
	int deltaCol = -1;
	int howManyTilesFlipped = 0;	//how many tiles flipped when I placed my tile
	int howManyMovesOpponentHas = 0;
	
	int i;
	int j;
	for (i=-1; i<=1; i++)
	{
		for (j=-1; j<=1; j++)
		{
			howManyTilesFlipped += changeTilesOnBoardForMyAlgorithm(n, board2, row, col, colourOfComputer, deltaRow, deltaCol);
			deltaCol++;
		}
		deltaCol = -1;
		deltaRow++;
	}
	
	//only call if opponent has a possible move for the next turn
	//howManyMovesOpponentHas = opponentAlgorithm(n, board2, colourOfComputer);	//opponent places an educated move and returns how many possible moves it had
	
	if (howManyMovesOpponentHas == 0)
	{
		return 1000.0;
	}
	
	//need to find out how many moves you have
	deltaRow = -1;
	deltaCol = -1;
	int numberOfMovesAfterOpponentPlaces = 0;
	int a;
	int b;
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			for (a=-1; a<=1; a++)
			{
				for (b=-1; b<=1; b++)
				{
					if (checkLegalInDirection(n, board2, changeNumberToChar(i), changeNumberToChar(j), colourOfComputer, deltaRow, deltaCol) == true)
					{
						numberOfMovesAfterOpponentPlaces++;
					}
					deltaCol++;
				}
				deltaCol = -1;
				deltaRow++;
			}
			deltaCol = -1;
			deltaRow = -1;
		}
	}
	
	
	/*
	 * in opponent algorithm, find out how many moves opponent has, if they have 0, return 0 right away
	 * how many tiles I was able to flip over after I made my move: howManyTilesFlipped
	 * number of moves opponent has after I made my move: howManyMovesOpponentHas
	 * number of moves I have after opponent places their move: numberOfMovesAfterOpponentPlaces
	 * //last thing i need is corner shit
	 */
	 
	 double calculatedValue = 0.0;
	 
	calculatedValue = (howManyTilesFlipped*0.1) - (howManyMovesOpponentHas*0.2) + (numberOfMovesAfterOpponentPlaces*0.5) + (cornerSideMiddle(n, row, col)*0.3);
	
	return calculatedValue; 
}

// Return a heuristic computed value for where the best position would be to place a marker
double finalValue(int n, char board[26][26], int row, int col, char colourOfComputer)
{
	char board2[26][26];
	double calculatedValueToReturn = 0.0;
	
	//initialize the second board
	int i;
	int j;
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			board2[i][j] = board[i][j];
		}
	}
	
	calculatedValueToReturn = maximizeNumberOfMovesICanMake(n, board2, row, col, colourOfComputer);
	
	return calculatedValueToReturn;	//returns calculated value to computerAlgorithm Function
}

// Initial version of my own implemented algorithm
void computerAlgorithm(int n, char board[26][26], char colourOfComputer)
{
	char possibleMoves[26][26];
	double valuesWhereToMakeAMove[26][26];
	
	//initialize possibleMoves board
	int i;
	int j;
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			possibleMoves[i][j] = 'U';
			valuesWhereToMakeAMove[i][j] = -10.0;
		}
	}
	
	int deltaRow = -1;
	int deltaCol = -1;
	int a;
	int b;
	//finds possible moves and saves them in 'possibleMoves'
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			for (a=-1; a<=1; a++)
			{
				for (b=-1; b<=1; b++)
				{
					if (checkLegalInDirection(n, board, changeNumberToChar(i), changeNumberToChar(j), colourOfComputer, deltaRow, deltaCol) == true)
					{
						possibleMoves[i][j] = colourOfComputer;
					}
					deltaCol++;
				}
				deltaCol = -1;
				deltaRow++;
			}
			deltaCol = -1;
			deltaRow = -1;
		}
	}
	
	double value=0.0;
	
	//sends possible moves to a function called finalValue and returns all the calculated values on where opponent should move
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			if (possibleMoves[i][j] == colourOfComputer)
			{
				value = finalValue(n, board, i, j, colourOfComputer);
				valuesWhereToMakeAMove[i][j] = value;
			}
		}
	}
	
	//run through valuesWhereToMakeAMove and finds highest value, my alogrithm will place a piece of it's own colour there
	
	double maxValue = 0.0;
	int finalRow;
	int finalCol;
	
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			if (valuesWhereToMakeAMove[i][j] > maxValue)
			{
				maxValue = valuesWhereToMakeAMove[i][j];
				finalRow = i;
				finalCol = j;
			}
		}
	}
	
	board[finalRow][finalCol] = colourOfComputer;
	findTilePositionAndChange(n, board, colourOfComputer, finalRow, finalCol); 
	
	printf("Computer places %c at %c%c.\n", colourOfComputer, changeNumberToChar(finalRow), changeNumberToChar(finalCol));

}