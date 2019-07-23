#pragma once

#include "DXlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "Othello.h"

// オセロ盤描画
void boardPrint() {
	int linecount = 0;
	DrawBox(0, 0, 640, 480, BLACK, TRUE);
	DrawBox(80, 0, 560, 480, GREEN, TRUE);
	DrawBox(88, 8, 552, 472, BLACK, FALSE);
	for (int i = 0; i < 7; i++) {
		linecount += 58;
		DrawLine(88, 8 + linecount, 552, 8 + linecount, BLACK);
		DrawLine(88 + linecount, 8, 88 + linecount, 472, BLACK);
	}

	// エンドボタン
	DrawBox(5, 220, 75, 340, TEAL, TRUE);
	DrawString(28, 280, "End", BLACK);

	// パスボタン
	DrawBox(5, 350, 75, 470, OLIVE, TRUE);
	DrawString(25, 410, "PASS", BLACK);

}

void boardPrintCPUlv1() {
	int linecount = 0;
	DrawBox(0, 0, 640, 480, BLACK, TRUE);
	DrawBox(80, 0, 560, 480, BLUE, TRUE);
	DrawBox(88, 8, 552, 472, WHITE, FALSE);
	for (int i = 0; i < 7; i++) {
		linecount += 58;
		DrawLine(88, 8 + linecount, 552, 8 + linecount, WHITE);
		DrawLine(88 + linecount, 8, 88 + linecount, 472, WHITE);
	}

	// エンドボタン
	DrawBox(5, 220, 75, 340, TEAL, TRUE);
	DrawString(28, 280, "End", BLACK);

	// パスボタン
	DrawBox(5, 350, 75, 470, OLIVE, TRUE);
	DrawString(25, 410, "PASS", BLACK);

}

void boardPrintCPUlv2() {
	int linecount = 0;
	DrawBox(0, 0, 640, 480, BLACK, TRUE);
	DrawBox(80, 0, 560, 480, YELLOW, TRUE);
	DrawBox(88, 8, 552, 472, BLACK, FALSE);
	for (int i = 0; i < 7; i++) {
		linecount += 58;
		DrawLine(88, 8 + linecount, 552, 8 + linecount, BLACK);
		DrawLine(88 + linecount, 8, 88 + linecount, 472, BLACK);
	}

	// エンドボタン
	DrawBox(5, 220, 75, 340, TEAL, TRUE);
	DrawString(28, 280, "End", BLACK);

	// パスボタン
	DrawBox(5, 350, 75, 470, OLIVE, TRUE);
	DrawString(25, 410, "PASS", BLACK);

}

void boardPrintCPUlv3() {
	int linecount = 0;
	DrawBox(0, 0, 640, 480, BLACK, TRUE);
	DrawBox(80, 0, 560, 480, RED, TRUE);
	DrawBox(88, 8, 552, 472, WHITE, FALSE);
	for (int i = 0; i < 7; i++) {
		linecount += 58;
		DrawLine(88, 8 + linecount, 552, 8 + linecount, WHITE);
		DrawLine(88 + linecount, 8, 88 + linecount, 472, WHITE);
	}

	// エンドボタン
	DrawBox(5, 220, 75, 340, TEAL, TRUE);
	DrawString(28, 280, "End", BLACK);

	// パスボタン
	DrawBox(5, 350, 75, 470, OLIVE, TRUE);
	DrawString(25, 410, "PASS", BLACK);

}

// 石描画
void drawStone() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (data.stone[i][j] == 1) {
				DrawCircle(117 + (i * 58), 37 + (j * 58), 26, WHITE, TRUE);
			}
			else if (data.stone[i][j] == -1) {
				DrawCircle(117 + (i * 58), 37 + (j * 58), 26, BLACK, TRUE);
			}
		}
	}
}

// 表示設定
void Display() {
	int blackcount = 0, whitecount = 0;
	//char BLACKBUFF[128] , WHITEBUFF[128];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (data.stone[i][j] == -1) {
				blackcount++;
			}
			else if (data.stone[i][j] == 1) {
				whitecount++;
			}
		}
	}

	DrawString(580, 25, "手番", WHITE);
	if (data.turn == 1) {
		DrawString(580, 45, "WHITE", WHITE);
	}
	else {
		DrawString(580, 45, "BLACK", WHITE);
	}

	sprintf_s(BLACKBUFF, 128, "黒石 :%d", blackcount);
	sprintf_s(WHITEBUFF, 128, "白石 :%d", whitecount);
	data.tmpblack = blackcount;
	data.tmpwhite = whitecount;

	DrawString(570, 320, BLACKBUFF, WHITE);
	DrawString(570, 340, WHITEBUFF, WHITE);
}