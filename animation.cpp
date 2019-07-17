// projectA.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include < stdio.h >
#include <curses.h>
#include <string.h>

int key;

void anime1(int score) {
	while (1) {
		bkgd(COLOR_PAIR(10));			// 背景は色10
		attrset(COLOR_PAIR(1));			// 色1 を使う
		mvaddstr(8, 25, "*********  *********   *******   *       * *          *********");
		mvaddstr(9, 25, "*        * *          *          *       * *              *    ");
		mvaddstr(10, 25, "*********  *********   *******   *       * *              *    ");
		mvaddstr(11, 25, "*       *  *                  *  *       * *              *    ");
		mvaddstr(12, 25, "*        * *********   *******   ********* **********     *    ");
		mvaddstr(14, 50, "SCORE : ");
		move(14, 58);
		printw("%d", score);

		key = getch();
		if (key == ' ')break;
	}
}

void anime2() {
	int x, y;
	int move = 0;

	erase();
	while (1) {
		bkgd(COLOR_PAIR(10));			// 背景は色10
		attrset(COLOR_PAIR(1));			// 色1 を使う

		x = 6;
		y = 20;
		if (move == 0) {
			for (int j = x; j < x + 100; j++) {

				mvaddstr(y - 1, j, " ** ");
				mvaddstr(y, j, "****");
				mvaddstr(y + 1, j, " ** ");

				napms(15);
				mvaddstr(y - 1, j - 1, " ");
				mvaddstr(y, j - 1, " ");
				mvaddstr(y + 1, j - 1, " ");
				refresh();
			}
			move = 1;
		}
		else if (move == 1) {
			for (int j = x + 100; j > x; j--) {

				mvaddstr(y - 1, j, " ** ");
				mvaddstr(y, j, "****");
				mvaddstr(y + 1, j, " ** ");

				napms(15);
				mvaddstr(y - 1, j + 3, " ");
				mvaddstr(y, j + 4, " ");
				mvaddstr(y + 1, j + 3, " ");
				refresh();
			}
			move = 0;
			//break;
			key = getch();
			if (key == ' ')break;
		}
	}
}

void anime3() {
	int x, y;
	int move = 0;

	erase();
	while (1) {
		bkgd(COLOR_PAIR(10));			// 背景は色10
		attrset(COLOR_PAIR(10));			// 色1 を使う

		x = 6;
		y = 20;
		if (move == 0) {

			for (int j = x + 100; j > x; j--) {

				mvaddstr(y - 1, j, " ** ");
				mvaddstr(y, j, "****");
				mvaddstr(y + 1, j, " ** ");

				napms(15);
				mvaddstr(y - 1, j + 3, " ");
				mvaddstr(y, j + 4, " ");
				mvaddstr(y + 1, j + 3, " ");
				refresh();
			}
			move = 1;
		}
		else if (move == 1) {
			for (int j = x; j < x + 100; j++) {

				mvaddstr(y - 1, j, " ** ");
				mvaddstr(y, j, "****");
				mvaddstr(y + 1, j, " ** ");

				napms(15);
				mvaddstr(y - 1, j - 1, " ");
				mvaddstr(y, j - 1, " ");
				mvaddstr(y + 1, j - 1, " ");
				refresh();
			}
			
			move = 0;
			//break;
			key = getch();
			if (key == ' ')break;
		}
	}
}

void anime4() {
	int x, y;
	int c = 0;

	erase();
	while (1) {
		bkgd(COLOR_PAIR(10));			// 背景は色10


		x = 6;
		y = 20;
		for (int j = x; j < x + 100; j += 5) {
			if (c % 2 == 0) {
				attrset(COLOR_PAIR(1));			// 色1 を使う
			}
			else {
				attrset(COLOR_PAIR(10));			// 色1 を使う
			}

			mvaddstr(y - 1, j, " ** ");
			mvaddstr(y, j, "****");
			mvaddstr(y + 1, j, " ** ");

			c++;
		}
		key = getch();
		if (key == ' ')break;
	}
	
}


int main(void) {

	// 端末の準備
	initscr();

	// *ゲームオーバー画面* //


	// 色の準備
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_GREEN);	// 色1 は緑地に黒文字
	init_pair(2, COLOR_WHITE, COLOR_BLACK);	// 色2 は黒地に白文字
	init_pair(3, COLOR_GREEN, COLOR_BLACK);	// 色3 は黒地に緑文字
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);	// 色4 は黒地にマゼンタ文字
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);	// 色5 は黒地に黄文字
	init_pair(10, COLOR_WHITE, COLOR_GREEN);	// 色10 は緑地に白文字

	int score = 0;
	//noecho();
	//cbreak();
	//timeout(0);
	keypad(stdscr, TRUE);
	
	anime1(score);
	anime2();
	anime3();
	anime4();

	endwin();
	return (0);
}