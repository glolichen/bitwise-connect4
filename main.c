#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "bitboard.h"
#include "bitmask.h"

void clear() {
	// credit: https://stackoverflow.com/a/33992073
    system("cls || clear");
}

int main() {
	init_bitmasks();
	
	Board board;
	Side winner;
	int col;

	while (1) {
		// clear console
		clear();
		// if the winner is not nothing break
		// also set the winner to whatever the winner is
		if ((winner = check_winner(&board)) != NOTHING)
			break;
		// if the board is full break
		if (is_full(&board))
			break;
		// print board
		print_board(&board, true);
		int length = -1;
		do {
			// do not do this on the first time running
			if (length != -1) {
				// go back a line
				printf("\033[F");
				// print spaces to clear out past input
				for (int i = 0; i < length; i++)
					printf(" ");
				// then use \b to go back to start
				for (int i = 0; i < length; i++)
					printf("\b");
			}
			// ask for move
			printf("Move: ");
			scanf("%d", &col);
			// get length of line (the length of "Move: " plus the length of the input)
			// add 1 for negative sign if they enter that
			// if they enter a non-integer this will crash and die but if they enter that they deserve it
			length = 6 + floor(log10(abs(col))) + 1 + (col < 0 ? 1 : 0);
		} while (col < 1 | col > 7); // keep doing this until the col input is valid
		// add the piece (but subtract 1 to make it 0 indexed)
		add_piece(&board, col - 1);
	}

	print_board(&board, false);
	if (winner != NOTHING)
		printf("%s wins!\n", winner == RED ? "Red" : "Yellow");
	else
		printf("Tie\n");

	return 0;
}
