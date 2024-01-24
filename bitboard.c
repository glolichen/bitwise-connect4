#include <stdio.h>
#include <stdbool.h>

#include "bitboard.h"
#include "bitmask.h"

void new_board(Board *board) {
	board->color = 0ull;
	board->occupied = 0ull;
	board->turn = RED;
}

void add_piece(Board *board, int col) {
	// mask = one column is all 1, everything else is 0
	ull mask = vertical[6 - col];
	// and it to the not occupied squares
	// it will be 1 if it is in the column and not occupied
	ull colOccupied = mask & ~board->occupied;
	// if the occupied is 0 then nothing is available, return
	if (!colOccupied)
		return;
	// bitwise hack to find the least significant bit
	// the least significant bit is the lowest available square, that is where we add the piece
	ull lowest = colOccupied & -colOccupied;
	// set that square to occupied
	board->occupied |= lowest;
	// if the color is red, switch the color at that square to 1
	// ~0ull = all 1, xor lowest will switch that square to 0
	// then when you and it it will take out the lowest square and keep everything else as 1
	if (board->turn == RED)
		board->color &= (~0ull) ^ lowest;
	// if it's yellow just or the bit to 1
	else
		board->color |= lowest;
	// toggle turn
	board->turn = board->turn == RED ? YELLOW : RED;
}

Side check_winner(Board *board) {
	// color - 0 = red, 1 = yellow
	// occupied xor color = all red pieces
	// (technically if it's not occupied and yellow this will break but we ensure that doesn't happen)
	// occupied and color = all yellow pieces
	ull red = board->occupied ^ board->color;
	ull yellow = board->occupied & board->color;

	// loop through the bitmasks
	for (int i = 0; i < bitmasks_size; i++) {
		ull bitmask = bitmasks[i];
		// if anding them results in the same bitmask then all the required pieces are there
		// therefore that side wins
		if ((bitmask & red) == bitmask)
			return RED;
		if ((bitmask & yellow) == bitmask)
			return YELLOW;
	}

	// nothing found = no one wins
	return NOTHING;
}

bool is_full(Board *board) {
	// 4398046511103 = 0b11111...11 (42 1's)
	// check if occupied is full of 1s
	return board->occupied == 4398046511103;
}

void print_board(Board *board, bool print_turn) {
	// print the board
	// weird unicode box drawing characters
	printf("  1   2   3   4   5   6   7\n");
	printf("╭───┬───┬───┬───┬───┬───┬───╮\n");

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			int index = 41 - (i * 7 + j);
			printf("│");
			// QUERY is a macro that returns 1 if the ull is 1 at that bit
			// if occupied os 0 print nothing otherwise print O with right color
			if (!QUERY(board->occupied, index))
				printf("   ");
			else if (QUERY(board->color, index) == RED)
				// ansi control signal for red, then clear color
				printf("\033[30;91m O \033[0m");
			else if (QUERY(board->color, index) == YELLOW)
				// ansi control signal for yellow, then clear color
				printf("\033[30;93m O \033[0m");
		}

		printf("│");

		if (i < 5)
			printf("\n├───┼───┼───┼───┼───┼───┼───┤\n");
		else
			printf("\n╰───┴───┴───┴───┴───┴───┴───╯\n");
	}
	if (print_turn)
		printf("Turn: %s\n", board->turn == RED ? "red" : "yellow");
}