/* ui.c --- 
 * 
 * Filename: ui.c
 * Author: Louise <louise>
 * Created: Sun Sep  8 16:26:28 2019 (+0200)
 * Last-Updated: Sun Sep  8 21:48:37 2019 (+0200)
 *           By: Louise <louise>
 */
#include<stdio.h>
#include"general.h"
#include"ui.h"

void load_texture() {
    tp.pawn[0] = LoadTexture("images/pl.png");
    tp.bishop[0] = LoadTexture("images/bl.png");
    tp.knight[0] = LoadTexture("images/nl.png");
    tp.rook[0] = LoadTexture("images/rl.png");
    tp.queen[0] = LoadTexture("images/ql.png");
    tp.king[0] = LoadTexture("images/kl.png");
    
    tp.pawn[1] = LoadTexture("images/pd.png");
    tp.bishop[1] = LoadTexture("images/bd.png");
    tp.knight[1] = LoadTexture("images/nd.png");
    tp.rook[1] = LoadTexture("images/rd.png");
    tp.queen[1] = LoadTexture("images/qd.png");
    tp.king[1] = LoadTexture("images/kd.png");
}

void draw_board() {
    ClearBackground(BEIGE);

    for (int i = 1; i < 64; i += (i % 8 == 7) ? 1 : (i % 8 == 6) ? 3 : 2)
	DrawRectangle((i % 8) * 38 + 88, (i / 8) * 38 + 8, 38, 38, BROWN);
    
    DrawRectangleLines(88, 8, 304, 304, BLACK);
    for (int i = 126; i < 394; i += 38) {
	DrawLine(i, 8, i, 312, BLACK);
    }
    
    for (int i = 46; i < 312; i += 38) {
	DrawLine(88, i, 392, i, BLACK);
    }
    
    DrawText("a", 107 - MeasureText("a", FONT_SIZE) / 2, 314, FONT_SIZE, BLACK);
    DrawText("b", 145 - MeasureText("b", FONT_SIZE) / 2, 314, FONT_SIZE, BLACK);
    DrawText("c", 183 - MeasureText("c", FONT_SIZE) / 2, 314, FONT_SIZE, BLACK);
    DrawText("d", 221 - MeasureText("d", FONT_SIZE) / 2, 314, FONT_SIZE, BLACK);
    DrawText("e", 259 - MeasureText("e", FONT_SIZE) / 2, 314, FONT_SIZE, BLACK);
    DrawText("f", 297 - MeasureText("f", FONT_SIZE) / 2, 314, FONT_SIZE, BLACK);
    DrawText("g", 335 - MeasureText("g", FONT_SIZE) / 2, 314, FONT_SIZE, BLACK);
    DrawText("h", 373 - MeasureText("h", FONT_SIZE) / 2, 314, FONT_SIZE, BLACK);

    DrawText("8", 395, 27 - FONT_SIZE / 2, FONT_SIZE, BLACK);
    DrawText("7", 395, 65 - FONT_SIZE / 2, FONT_SIZE, BLACK);
    DrawText("6", 395, 103 - FONT_SIZE / 2, FONT_SIZE, BLACK);
    DrawText("5", 395, 141 - FONT_SIZE / 2, FONT_SIZE, BLACK);
    DrawText("4", 395, 179 - FONT_SIZE / 2, FONT_SIZE, BLACK);
    DrawText("3", 395, 217 - FONT_SIZE / 2, FONT_SIZE, BLACK);
    DrawText("2", 395, 255 - FONT_SIZE / 2, FONT_SIZE, BLACK);
    DrawText("1", 397, 293 - FONT_SIZE / 2, FONT_SIZE, BLACK);
}

void draw_pieces() {
    for (int i = 0; i < 64; i++) {
	int x = (i % 8) * 38 + 89, y = (i / 8) * 38 + 9;
	switch (game.board[i].piece) {
	case NOTHING: break;
	case PAWN: DrawTexture(tp.pawn[game.board[i].color], x, y, RAYWHITE); break;
	case BISHOP: DrawTexture(tp.bishop[game.board[i].color], x, y, RAYWHITE); break;
	case KNIGHT: DrawTexture(tp.knight[game.board[i].color], x, y, RAYWHITE); break;
	case ROOK: DrawTexture(tp.rook[game.board[i].color], x, y, RAYWHITE); break;
	case QUEEN: DrawTexture(tp.queen[game.board[i].color], x, y, RAYWHITE); break;
	case KING: DrawTexture(tp.king[game.board[i].color], x, y, RAYWHITE); break;
	}
    }
}

void draw_misc() {
    // Highlight
    if (game.highlighted != -1)
	DrawRectangle((game.highlighted % 8) * 38 + 88, (game.highlighted / 8) * 38 + 8, 37, 37, GREEN);

    // Possible
    for (int i = 0; i < 64; i++) {
	if (game.possible & ((uint64_t)1 << i)) {
	    DrawRectangle((i % 8) * 38 + 88, (i / 8) * 38 + 8, 37, 37, BLUE);
	}
    }
}
