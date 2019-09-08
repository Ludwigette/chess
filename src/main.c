/* main.c --- 
 * 
 * Filename: main.c
 * Author: Louise <louise>
 * Created: Sun Sep  8 13:53:49 2019 (+0200)
 * Last-Updated: Sun Sep  8 20:10:12 2019 (+0200)
 *           By: Louise <louise>
 */
#define MAIN_FILE
#include<stdlib.h>
#include<stdio.h>
#include"general.h"
#include"engine.h"
#include"ui.h"

void init_board() {
    game.highlighted = -1;
    for (int i = 0; i < 64; i++) game.board[i] = (Ch_Square){.piece = NOTHING, .color = CH_WHITE};

    // Black
    game.board[0] = (Ch_Square){.piece = ROOK, .color = CH_BLACK};
    game.board[1] = (Ch_Square){.piece = KNIGHT, .color = CH_BLACK};
    game.board[2] = (Ch_Square){.piece = BISHOP, .color = CH_BLACK};
    game.board[3] = (Ch_Square){.piece = QUEEN, .color = CH_BLACK};
    game.board[4] = (Ch_Square){.piece = KING, .color = CH_BLACK};
    game.board[5] = (Ch_Square){.piece = BISHOP, .color = CH_BLACK};
    game.board[6] = (Ch_Square){.piece = KNIGHT, .color = CH_BLACK};
    game.board[7] = (Ch_Square){.piece = ROOK, .color = CH_BLACK};
    for (int i = 8; i < 16; i++) game.board[i] = (Ch_Square){.piece = PAWN, .color = CH_BLACK};
    
    // White
    for (int i = 48; i < 56; i++) game.board[i] = (Ch_Square){.piece = PAWN, .color = CH_WHITE};
    game.board[56] = (Ch_Square){.piece = ROOK, .color = CH_WHITE};
    game.board[57] = (Ch_Square){.piece = KNIGHT, .color = CH_WHITE};
    game.board[58] = (Ch_Square){.piece = BISHOP, .color = CH_WHITE};
    game.board[59] = (Ch_Square){.piece = KING, .color = CH_WHITE};
    game.board[60] = (Ch_Square){.piece = QUEEN, .color = CH_WHITE};
    game.board[61] = (Ch_Square){.piece = BISHOP, .color = CH_WHITE};
    game.board[62] = (Ch_Square){.piece = KNIGHT, .color = CH_WHITE};
    game.board[63] = (Ch_Square){.piece = ROOK, .color = CH_WHITE};
}

void press() {
    Vector2 pos = GetMousePosition();
    if (pos.x >= 88 && pos.x <= 392 && pos.y >= 8 && pos.y <= 312) {
	int x = ((int)pos.x - 88) / 38;
	int y = ((int)pos.y - 8) / 38;
	int n = y * 8 + x;
	
	if (game.board[n].color == game.to_play && game.board[n].piece != NOTHING) {
	    game.highlighted = y * 8 + x;
	    game.possible = get_possible_moves(game.highlighted);
	    game.mode = 1;
	} else if (game.mode) {
	    if (game.possible & ((uint64_t)1 << n)) {
		game.board[n] = game.board[game.highlighted];
		game.board[game.highlighted].piece = NOTHING;
		game.highlighted = -1;
		game.possible = 0;
		game.mode = 0;

		game.to_play = !game.to_play;
	    }
	}
    }
}

int main(int argc, char **argv) {
    InitWindow(480, 340, "Chess");
    load_texture();
    init_board();

    while(!WindowShouldClose()) {
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) press();
	
	BeginDrawing();
	draw_misc();
	draw_board();
	EndDrawing();
    }
    
    return 0;
}
