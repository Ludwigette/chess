/* engine.c --- 
 * 
 * Filename: engine.c
 * Author: Louise <louise>
 * Created: Sun Sep  8 18:05:46 2019 (+0200)
 * Last-Updated: Sun Sep  8 19:53:04 2019 (+0200)
 *           By: Louise <louise>
 */
#include<stdlib.h>
#include"general.h"
#define GET_SQUARE(x, y) game.board[n_from_pos(x, y)]
#define GET_PIECE(x, y)  GET_SQUARE(x, y).piece
#define GET_COLOR(x, y)  GET_SQUARE(x, y).color

#define IN_BOARD(x, y) ((x >= 0) && (x <= 7) && (y >= 0) && (y <= 7))
#define GENERAL_MOVE(j, k)						\
    if (IN_BOARD(x + j, y + k)						\
	&& (GET_PIECE(x + j, y + k) == NOTHING || GET_COLOR(x + j, y + k) != current_c)) \
	result = set_bit(result, n_from_pos(x + j, y + k))

#define BISHOP_MOVE_PART(h, v)						\
    for (int j = x + h, k = y + v; IN_BOARD(j, k) && (GET_PIECE(j, k) == NOTHING || GET_COLOR(j, k) != current_c); j += h, k += v) { \
	result = set_bit(result, n_from_pos(j, k));			\
	if (GET_PIECE(j, k) != NOTHING) break;				\
    }

#define BISHOP_MOVE()	     \
    BISHOP_MOVE_PART(1, 1)   \
    BISHOP_MOVE_PART(-1, 1)  \
    BISHOP_MOVE_PART(1, -1)  \
    BISHOP_MOVE_PART(-1, -1)
    
#define ROOK_MOVE_PART1(a) \
    for (int j = x + a; IN_BOARD(j, y) && (GET_PIECE(j, y) == NOTHING || GET_COLOR(j, y) != current_c); j += a) { \
	result = set_bit(result, n_from_pos(j, y));			\
	if (GET_PIECE(j, y) != NOTHING) break;				\
    }

#define ROOK_MOVE_PART2(a) \
    for (int j = y + a; IN_BOARD(x, j) && (GET_PIECE(x, j) == NOTHING || GET_COLOR(x, j) != current_c); j += a) { \
	result = set_bit(result, n_from_pos(x, j));			\
	if (GET_PIECE(x, j) != NOTHING) break;				\
    }

#define ROOK_MOVE()	\
    ROOK_MOVE_PART1(1)	\
    ROOK_MOVE_PART1(-1) \
    ROOK_MOVE_PART2(1)	\
    ROOK_MOVE_PART2(-1)

static inline uint64_t set_bit(uint64_t bitfield, int n) {
    return bitfield | (uint64_t)1 << n;
}

static inline int n_from_pos(int x, int y) {
    return y * 8 + x;
}

uint64_t get_possible_moves(int i) {
    uint64_t result = 0;
    int x = i % 8, y = i / 8;
    enum Ch_Color current_c = GET_COLOR(x, y);
    
    switch (game.board[i].piece) {
    case PAWN:
	switch (game.board[i].color) {
	case CH_WHITE:
	    if (y != 0) result = set_bit(result, n_from_pos(x, y - 1));
	    if (y == 6) result = set_bit(result, n_from_pos(x, y - 2));
	    break;
	case CH_BLACK:
	    if (y != 7) result = set_bit(result, n_from_pos(x, y + 1));
	    if (y == 1) result = set_bit(result, n_from_pos(x, y + 2));
	    break;
	}
	break;
    case ROOK:
        ROOK_MOVE();
	break;
    case BISHOP:
	BISHOP_MOVE();
	break;
    case KNIGHT:
	GENERAL_MOVE(-2, -1);
	GENERAL_MOVE(-2, 1);
	GENERAL_MOVE(-1, 2);
	GENERAL_MOVE(1, 2);
	GENERAL_MOVE(2, 1);
	GENERAL_MOVE(2, -1);
	GENERAL_MOVE(-1, -2);
	GENERAL_MOVE(1, -2);
	break;
    case QUEEN:
	ROOK_MOVE();
	BISHOP_MOVE();
	break;
    case KING:
	GENERAL_MOVE(-1, -1);
	GENERAL_MOVE(-1, 0);
	GENERAL_MOVE(-1, 1);
	GENERAL_MOVE(0, -1);
	GENERAL_MOVE(0, 1);
	GENERAL_MOVE(1, -1);
	GENERAL_MOVE(1, 0);
	GENERAL_MOVE(1, 1);
	break;
    }
    
    return result;
}
