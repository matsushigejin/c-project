// c-project.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#define B 10       /* 盤を表す配列 board のサイズ */
int board[B][B];   /* 盤の状態を表す配列 */

void init_board(int board[B][B]);
void print_board(int board[B][B]);

int main()
{
	init_board(board);
	print_board(board);
}

void init_board(int board[B][B]){
	int i, j;
	static int initdata[B][B] =
	{ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  2,  1,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  1,  2,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } };

	for (i = 0; i < B; i++) {
		for (j = 0; j < B; j++) {
			board[i][j] = initdata[i][j];
		}
	}
}

void print_board(int board[B][B])
{
	int i, j;

	for (i = 1; i <= 8; i++) {
		for (j = 1; j <= 8; j++) {
			printf("%2d", board[i][j]);
		}
		printf("\n");
	}
}

