#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdbool.h>

#define SET1(bitboard, pos) (bitboard |= 1ull << (pos))
#define SET0(bitboard, pos) (bitboard &= ((~0ull) ^ (1ull << (pos))))
#define QUERY(bitboard, pos) (bitboard >> (pos) & 1)

typedef unsigned long long ull;

typedef enum {
	NOTHING = -1,
	RED = 0,
	YELLOW = 1
} Side;
typedef struct {
	Side turn;
	// 0 = not occupied, 1 = occupied
	ull occupied;
	// 0 = red, 1 = yellow
	ull color;	
} Board;

void new_board(Board *board);
void add_piece(Board *board, int col);
Side check_winner(Board *board);
bool is_full(Board *board);
void print_board(Board *board, bool print_turn);

#endif