#include <stdio.h>
#include <stdbool.h>


int main()
{
	int n=0;
	char board[26][26];
	
	printf("Enter the board dimension: ");
	scanf("%d", &n);
	
	// Makes everything in the board have a value of 'U'
	int z;
	int g;
	for (z=0; z<n; z++)
	{
		for (g=0; g<n; g++)
		{
			board[z][g] = 'U';
		}
	}

	// Puts initial board configuration
	board[n/2 - 1][n/2 - 1] = 'W';
	board[n/2][n/2] = 'W';
	board[n/2 - 1][n/2] = 'B';
	board[n/2][n/2 -1] = 'B';
	
	char colourOfComputer;
	char colourOfHuman;
	int playerPlaying;
	int playerSitting;
	char humanRowInput;
	char humanColInput;
	
	bool isHumanInputValid;
	bool doesPlayerHaveAnyMoves;
	int deltaRow = -1;
	int deltaCol = -1;
	
	printf("Computer plays (B/W) : ");
	scanf(" %c", &colourOfComputer);
	
	//'0' is the computer, '1' is the human
	if (colourOfComputer == 'B')
	{
		playerPlaying = 0; 
		playerSitting = 1;
		colourOfHuman = 'W';
	}
	else if (colourOfComputer == 'W')
	{
		playerPlaying = 1; 
		playerSitting = 0;
		colourOfHuman = 'B';
	}
	
	printBoard(n, board);
	
	// Main loop function
	do
	{
		humanRowInput = ' ';
		humanColInput = ' ';
		
		if (playerPlaying == 0)
		{
			computerAlgorithm(n, board, colourOfComputer);
		}
		else if (playerPlaying == 1)
		{
			printf("Enter move for colour %c (RowCol): ", colourOfHuman);
			scanf(" %c%c", &humanRowInput, &humanColInput);

			deltaRow = -1;
			deltaCol = -1;
			isHumanInputValid = false;
			
			//check if move is valid
			int i;
			int b;
			for (i=-1; i<=1; i++)
			{
				for (b=-1; b<=1; b++)
				{
					if (checkLegalInDirection(n, board, humanRowInput, humanColInput, colourOfHuman, deltaRow, deltaCol))
						isHumanInputValid = true;
					deltaCol++;
				}
				deltaCol = -1;
				deltaRow++;
			}
			
			if (isHumanInputValid)
			{
				board[changeCharToNumber(humanRowInput)][changeCharToNumber(humanColInput)] = colourOfHuman;
				findTilePositionAndChange(n, board, colourOfHuman, changeCharToNumber(humanRowInput), changeCharToNumber(humanColInput));//
			}
			else if (isHumanInputValid == false)
			{
				printf("Invalid move.\n");
				break;
			}
		}
		
		printBoard(n, board);
		
		//if the game board is full, end the game
		if (isBoardFull(n, board))
		{
			break;
		}
		
		switchPlayerPlaying(&playerPlaying, &playerSitting);
		
		if (playerPlaying == 0)
		{
			doesPlayerHaveAnyMoves = doesPlayerHaveAvailableMove(n, board, colourOfComputer);
			
			if (doesPlayerHaveAnyMoves == false)
			{
				printf("%c player has no valid move.\n",  colourOfComputer);
				switchPlayerPlaying(&playerPlaying, &playerSitting);
				
				doesPlayerHaveAnyMoves = doesPlayerHaveAvailableMove(n, board, colourOfHuman);
				
				if (doesPlayerHaveAnyMoves == false)
				{
					printf("%c player has no valid move.\n",  colourOfHuman);
					break;
				}
			}
		}
		else if (playerPlaying == 1)
		{
			doesPlayerHaveAnyMoves = doesPlayerHaveAvailableMove(n, board, colourOfHuman);

			if (doesPlayerHaveAnyMoves == false)
			{
				printf("%c player has no valid move.\n",  colourOfHuman);
				switchPlayerPlaying(&playerPlaying, &playerSitting);
				
				doesPlayerHaveAnyMoves = doesPlayerHaveAvailableMove(n, board, colourOfComputer);
				
				if(doesPlayerHaveAnyMoves == false)
				{
					printf("%c player has no valid move.\n",  colourOfComputer);
					break;
				}
			}
		}
		
	} while(1);
	
	int countWhite = 0;
	int countBlack = 0;

	//finds how many white and black pieces there are on the board
	int i;
	int j;
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			if (board[i][j] == 'W')
				countWhite++;
			else if (board[i][j] == 'B')
				countBlack++;
		}
	}
	
	//finds out who won
	if (countWhite > countBlack)
		printf("W player wins.");
	else if (countBlack > countWhite)
		printf("B player wins.");
	else if (countWhite == countBlack)
		printf("Draw!");
	
	puts("");
	return 0;
}
