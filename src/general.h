/* general.h --- 
 * 
 * Filename: general.h
 * Author: Louise <louise>
 * Created: Sun Sep  8 16:21:54 2019 (+0200)
 * Last-Updated: Sun Sep  8 20:07:41 2019 (+0200)
 *           By: Louise <louise>
 */
#ifndef GENERAL_H
#define GENERAL_H
#include<raylib.h>
#include<stdint.h>

enum Ch_Piece { PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING, NOTHING };
enum Ch_Color { CH_WHITE = 0, CH_BLACK = 1};
typedef struct Ch_Square { enum Ch_Piece piece; enum Ch_Color color; int x, y; } Ch_Square;

struct TexturePack {
    Texture2D pawn[2];
    Texture2D bishop[2];
    Texture2D knight[2];
    Texture2D rook[2];
    Texture2D queen[2];
    Texture2D king[2];
};

struct Game {
    Ch_Square board[64];

    enum Ch_Color to_play;
    int highlighted;
    uint64_t possible;
    int mode;
};

#ifdef MAIN_FILE

struct TexturePack tp;
struct Game game;

#else

extern struct TexturePack tp;
extern struct Game game;

#endif 
#endif
