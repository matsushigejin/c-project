#pragma once

#include "DXlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "Othello.h"

// 盤面初期状態
void boardInit() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			data.stone[i][j] = 0;
		}
	}
	data.endFlag = 0;
	data.stone[3][3] = 1;
	data.stone[4][4] = 1;
	data.stone[3][4] = -1;
	data.stone[4][3] = -1;
}

void boardInitCPU() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			data.stone[i][j] = 0;
		}
	}
	data.endFlag = 0;
	data.stone[3][3] = 1;
	data.stone[4][4] = 1;
	data.stone[3][4] = -1;
	data.stone[4][3] = -1;
}

// ゲーム終了処理
// ゲームが終了していれば1、まだ途中であれば0を返す
int gameEnd() {
	int greenField = 0, whiteStone = 0, brackStone = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (data.stone[i][j] == 0) {
				greenField++;
			}
			else if (data.stone[i][j] == 1) {
				whiteStone++;
			}
			else if (data.stone[i][j] == -1) {
				brackStone++;
			}
		}
	}
	if (data.endFlag == 1) {
		return 1;
	}

	if (greenField == 0) {	// 盤面に0が存在しない→空き盤がない→1を返す
		return 1;
	}
	else {	// 0が存在する(空き盤がある)場合
		if (whiteStone == 0) {	// 白の石が存在しない→1を返す
			return 1;
		}
		if (brackStone == 0) {	// 黒の石が存在しない→1を返す
			return 1;
		}
		return 0;
	}
	return 1;
}

void FileInput() {
	FILE* fp;
	char s[BUFFSIZE];

	char delim[] = ", ";
	char* ctx;
	char* p1;

	int i = 0, j = 0;

	errno_t error;
	error = fopen_s(&fp, "stoneleveldata.txt", "r");
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		while (fgets(s, BUFFSIZE, fp) != NULL) {
			p1 = strtok_s(s, delim, &ctx);
			data.stonelevel[i][j] = atoi(p1);
			j++;
			while (*ctx != NULL) {
				p1 = strtok_s(NULL, delim, &ctx);
				data.stonelevel[i][j] = atoi(p1);
				j++;
			}
			i++;
			j = 0;

		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				printf_s("%d", data.stonelevel[i][j]);
			}
		}
		fclose(fp);
	}
}

void FileOutput() {

	FILE* fp;

	errno_t error;
	error = fopen_s(&fp, "result.txt", "w");
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {

		//txtファイルに表示
		fprintf(fp, "黒石 : %d\n", data.tmpblack);
		fprintf(fp, "白石 : %d\n", data.tmpwhite);
		if (data.tmpblack > data.tmpwhite) {
			fputs("黒の勝ち!!!", fp);
		}
		else if (data.tmpblack < data.tmpwhite) {
			fputs("白の勝ち!!!", fp);
		}

		fclose(fp);
	}
}