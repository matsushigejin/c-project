// othello.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "stdio.h"

#define B 10       /* 盤を表す配列 board のサイズ */
#define aite(player) (3-(player))	/* 1と2をplayerとする */

int board[B][B];   /* 盤の状態を表す配列 */

void init_board(int board[B][B]);
void print_board(int board[B][B]);
int check(int a[10], int p, int d);
int count_turn_over(int board[B][B], int player, int p, int q, int d, int e);
int is_legal_move(int board[B][B], int player, int p, int q);
int exist_legal_move(int board[B][B], int player);
void get_move(int board[B][B], int player, int *p, int *q);
void set_and_turn_over(int board[B][B], int player, int p, int q);
void count_stone(int board[B][B], int *c1, int *c2);
int game();

int main()
{
	char buf[100];
	printf("Let's play Othello!\n");
	do {
		game();
		printf("again? (y/n) > ");
		scanf_s("%s", buf);
	} while (buf[0] == 'y');
	return 0;
}

void init_board(int board[B][B]){	/*ゲーム盤の設定*/
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

void print_board(int board[B][B])	/*ゲーム盤の表示*/
{
	int i, j;

	for (i = 1; i <= 8; i++) {
		for (j = 1; j <= 8; j++) {
			printf("%2d", board[i][j]);
		}
		printf("\n");
	}
}

int check(int a[10], int p, int d)
{
	int i;

	for (i = 1; a[p + i*d] == 2; i++);

	if (a[p + i*d] == 1) {
		return i - 1;
	}
	else {
		return 0;
	}
}

int count_turn_over(int board[B][B], int player, int p, int q, int d, int e)	/* player (1または2）が，p行q列のマス目に石を置いたとき，
																				そのマス目から(d, e) 方向（d, e は -1, 0, 1 のどれか。
																				ただし，両方とも0 でなはい）にある，裏返る相手の石の個数を返す。*/
{
	int i;

	for (i = 1; board[p + i*d][q + i*e] == aite(player); i++) {};

	if (board[p + i*d][q + i*e] == player) {
		return i - 1;
	}
	else {
		return 0;
	}
}

int is_legal_move(int board[B][B], int player, int p, int q)	/* player が (p,q) のマス目に石を置くことができるかどうか */
{
	if (p < 1 || p > 8 || q < 1 || q > 8) return 0;
	if (board[p][q] != 0) return 0;
	if (count_turn_over(board, player, p, q, -1, 0)) return 1;  /* 上 */
	if (count_turn_over(board, player, p, q, 1, 0)) return 1;  /* 下 */
	if (count_turn_over(board, player, p, q, 0, -1)) return 1;  /* 左 */
	if (count_turn_over(board, player, p, q, 0, 1)) return 1;  /* 右 */
	if (count_turn_over(board, player, p, q, -1, -1)) return 1;  /* 左上 */
	if (count_turn_over(board, player, p, q, -1, 1)) return 1;  /* 右上 */
	if (count_turn_over(board, player, p, q, 1, -1)) return 1;  /* 左下 */
	if (count_turn_over(board, player, p, q, 1, 1)) return 1;  /* 右下 */
	return 0;
}

int exist_legal_move(int board[B][B], int player)	/* player が (p,q) のマス目に石を置くことができるかどうか */
{
	int i, j;

	for (i = 1; i <= 8; i++) {
		for (j = 1; j <= 8; j++) {
			if (is_legal_move(board, player, i, j)) return 1;
		}
	}
	return 0;
}

void get_move(int board[B][B], int player, int *p, int *q)	/* 指し手の入力 */
{
	char str[100];   /* 入力した文字列が入るバッファ */

	printf("Player %d ", player);
	while (1) {
		printf("> ");
		fgets(str, sizeof(str), stdin);
		if (str[0] > '8') {
			*q = str[0] - 'a' + 1;
			*p = str[1] - '1' + 1;
		}
		if(str[0] <= '8') {
			*q = str[1] - 'a' + 1;
			*p = str[0] - '1' + 1;
		}
		if (is_legal_move(board, player, *p, *q)) return;

		printf("次の中から選んでください：");

	}
}

void set_and_turn_over(int board[B][B], int player, int p, int q)	/* 石を置いて、挟んだ石を裏返す */
{
	int count, d, e, i;

	for (d = -1; d <= 1; d++) {      /* 上下方向 */
		for (e = -1; e <= 1; e++) {  /* 左右方向 */
			if (d == 0 && e == 0) continue;
			count = count_turn_over(board, player, p, q, d, e);
			for (i = 1; i <= count; i++) {
				board[p + i*d][q + i*e] = player; /* 裏返す */
			}
		}
	}
	board[p][q] = player; /* 石を置く */
}

void count_stone(int board[B][B], int *c1, int *c2)	/* 盤上の石の個数を数える */
{
	int i, j;

	*c1 = 0;
	*c2 = 0;
	for (i = 1; i <= 8; i++) {
		for (j = 1; j <= 8; j++) {
			switch (board[i][j]) {
			case 1:
				(*c1)++;
				break;
			case 2:
				(*c2)++;
				break;
			}
		}
	}
}

int game()
{
	int p, q, player, c1, c2;
	int board[B][B];

	init_board(board);
	player = 1;
	while (1) {
		print_board(board);
		if (!exist_legal_move(board, player)) {
			printf("Player %d has no legal moves > pass\n", player);
			player = aite(player);
			if (!exist_legal_move(board, player)) {
				printf("Player %d has no legal moves > pass\n", player);
				break;
			}
		}
		get_move(board, player, &p, &q);
		set_and_turn_over(board, player, p, q);
		player = aite(player);
	}
	count_stone(board, &c1, &c2);
	printf("Game Over\nPlayer 1 : %d\nPlayer 2 : %d\n", c1, c2);
	return c1 - c2;
}
