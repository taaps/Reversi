#include <stdio.h>
#include <stdbool.h>

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