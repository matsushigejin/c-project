#include "DXlib.h"
#include <stdlib.h>
#include <stdio.h>

#define WHITE	GetColor(255, 255, 255)
#define BLACK	GetColor(0, 0, 0)
#define GREEN	GetColor(0, 128, 0)
#define RED		GetColor(255, 0, 0)
#define BLUE	GetColor(0, 0, 255)
#define TEAL	GetColor(0, 128, 128)
#define OLIVE	GetColor(128, 128, 0)

// グローバル変数
int stone[8][8];
int endFlag = 0;
int turn = -1; // 手番・・・先手黒
int coolTimer = 0;
int tmpblack, tmpwhite;
int winjudge = 0;

// 関数
void boardInit();
void boardPrint();
void boardPrintAlpha();
void drawStone();
void setStone();
int gameEnd();
void passBottan();
void gameEndBottan();
void Display();
int checkPosStone(int myX, int myY);
void Reverse(int myX, int myY);


// 盤面初期状態
void boardInit() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			stone[i][j] = 0;
		}
	}
	endFlag = 0;
	stone[3][3] = 1;
	stone[4][4] = 1;
	stone[3][4] = -1;
	stone[4][3] = -1;
}

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

void boardPrintAlpha() {
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

// 石描画
void drawStone() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (stone[i][j] == 1) {
				DrawCircle(117 + (i * 58), 37 + (j * 58), 26, WHITE, TRUE);
			}
			else if (stone[i][j] == -1) {
				DrawCircle(117 + (i * 58), 37 + (j * 58), 26, BLACK, TRUE);
			}
		}
	}
}

// 石配置判別
// 1で置けて、0でそこには石を置くことができない
int checkPosStone(int myX, int myY) {
	int whichplayer = turn;
	int constantX = 0, constantY = 0;		//定数

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int k = 0;
			// 自分が石を置いたコマの処理を飛ばす
			if (i == 1 && j == 1) {
				continue;
			}

			if (whichplayer == 1) { //白
				switch (i * 10 + j) {
				case 0: // 左上
					constantX = -1, constantY = -1;
					if (myX < myY) {
						k = myX - 1;
					}
					else {
						k = myY - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX - 1][myY + constantY - 1] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX--, constantY--;
					}
					break;

				case 1: // 左
					constantX = -1, constantY = 0;
					k = myX - 1;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX - 1][myY + constantY] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX--;
					}
					break;

				case 2: // 左下
					constantX = -1, constantY = 1;
					if (myX > 7 - myY) {
						k = 6 - myY;
					}
					else {
						k = myX - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX - 1][myY + constantY + 1] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX--, constantY++;
					}
					break;

				case 10: // 上
					constantX = 0, constantY = -1;
					k = myY - 1;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX][myY + constantY - 1] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantY--;
					}
					break;

				case 12: // 下
					constantX = 0, constantY = 1;
					k = 6 - myY;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX][myY + constantY + 1] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantY++;
					}
					break;

				case 20: // 右上
					constantX = 1, constantY = -1;
					if (7 - myX < myY) k = 6 - myX;
					else k = myY - 1;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX + 1][myY + constantY - 1] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX++, constantY--;
					}
					break;

				case 21: // 右
					constantX = 1, constantY = 0;
					k = 6 - myX;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX + 1][myY + constantY] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX++;
					}
					break;

				case 22: // 右下
					constantX = 1, constantY = 1;
					if (7 - myX > 7 - myY) {
						k = 6 - myY;
					}
					else {
						k = 6 - myX;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX + 1][myY + constantY + 1] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX++, constantY++;
					}
					break;
				}
			}
			else if (whichplayer == -1) { // 置きたい石が黒だった場合
				switch (i * 10 + j) {
				case 0: // 左上
					constantX = -1, constantY = -1;
					if (myX < myY) {
						k = myX - 1;
					}
					else {
						k = myY - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX - 1][myY + constantY - 1] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX--, constantY--;
					}
					break;

				case 1: // 左
					constantX = -1, constantY = 0;
					k = myX - 1;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX - 1][myY + constantY] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX--;
					}
					break;

				case 2: // 左下
					constantX = -1, constantY = 1;
					if (myX > 7 - myY) {
						k = 6 - myY;
					}
					else {
						k = myX - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX - 1][myY + constantY + 1] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX--, constantY++;
					}
					break;

				case 10: // 上
					constantX = 0, constantY = -1;
					k = myY - 1;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX][myY + constantY - 1] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantY--;
					}
					break;

				case 12: // 下
					constantX = 0, constantY = 1;
					k = 6 - myY;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX][myY + constantY + 1] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantY++;
					}
					break;

				case 20: // 右上
					constantX = 1, constantY = -1;
					if (7 - myX < myY) {
						k = 6 - myX;
					}
					else {
						k = myY - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX + 1][myY + constantY - 1] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX++, constantY--;
					}
					break;

				case 21: // 右
					constantX = 1, constantY = 0;
					k = 6 - myX;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX + 1][myY + constantY] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX++;
					}
					break;

				case 22: // 右下
					constantX = 1, constantY = 1;
					if (7 - myX > 7 - myY) {
						k = 6 - myY;
					}
					else {
						k = 6 - myX;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX + 1][myY + constantY + 1] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX++, constantY++;
					}
					break;
				}
			}
			else {
				DrawString(0, 0, "エラーが発生しています", RED);
				return 0;
			}
		}
	}
	return 0;
}


// 反転処理
void Reverse(int myX, int myY) {
	int whichplayer = turn;
	int constantX = 0, constantY = 0;		//定数

	for (int i = 0; i < 3; i++) {		//3x3
		for (int j = 0; j < 3; j++) {
			int k = 0;
			// 自分が石を置いたコマの処理を無視
			if (i == 1 && j == 1) {
				continue;
			}

			if (whichplayer == 1) { //白
				switch (i * 10 + j) {
				case 0: // 左上
					constantX = -1, constantY = -1;
					if (myX < myY) {
						k = myX - 2;
					}
					else {
						k = myY - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX - 1][myY + constantY - 1] == 1) {
								constantX = -1, constantY = -1;
								while (stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = 1;
									constantX--, constantY--;
								}
							}
						}
						else {
							break;
						}
						constantX--, constantY--;
					}
					break;

				case 1: // 左
					constantX = -1, constantY = 0;
					k = myX - 1;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX - 1][myY + constantY] == 1) {
								constantX = -1, constantY = 0;
								while (stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = 1;
									constantX--;
								}
							}
						}
						else {
							break;
						}
						constantX--;
					}
					break;

				case 2: // 左下
					constantX = -1, constantY = 1;
					if (myX > 7 - myY) {
						k = 6 - myY;
					}
					else {
						k = myX - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX - 1][myY + constantY + 1] == 1) {
								constantX = -1, constantY = 1;
								while (stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = 1;
									constantX--, constantY++;
								}
							}
						}
						else {
							break;
						}
						constantX--, constantY++;
					}
					break;

				case 10: // 上
					constantX = 0, constantY = -1;
					k = myY - 1;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX][myY + constantY - 1] == 1) {
								constantX = 0, constantY = -1;
								while (stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = 1;
									constantY--;
								}
							}
						}
						else {
							break;
						}
						constantY--;
					}
					break;

				case 12: // 下
					constantX = 0, constantY = 1;
					k = 6 - myY;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX][myY + constantY + 1] == 1) {
								constantX = 0, constantY = 1;
								while (stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = 1;
									constantY++;
								}
							}
						}
						else {
							break;
						}
						constantY++;
					}
					break;

				case 20: // 右上
					constantX = 1, constantY = -1;
					if (7 - myX < myY) {
						k = 6 - myX;
					}
					else {
						k = myY - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX + 1][myY + constantY - 1] == 1) {
								constantX = 1, constantY = -1;
								while (stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = 1;
									constantX++, constantY--;
								}
							}
						}
						else break;
						constantX++, constantY--;
					}
					break;

				case 21: // 右
					constantX = 1, constantY = 0;
					k = 6 - myX;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX + 1][myY + constantY] == 1) {
								constantX = 1, constantY = 0;
								while (stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = 1;
									constantX++;
								}
							}
						}
						else break;
						constantX++;
					}
					break;

				case 22: // 右下
					constantX = 1, constantY = 1;
					if (7 - myX > 7 - myY) {
						k = 6 - myY;
					}
					else {
						k = 6 - myX;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == -1) {
							if (stone[myX + constantX + 1][myY + constantY + 1] == 1) {
								constantX = 1, constantY = 1;
								while (stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = 1;
									constantX++, constantY++;
								}
							}
						}
						else {
							break;
						}
						constantX++, constantY++;
					}
					break;
				}
			}
			else if (whichplayer == -1) { //黒
				switch (i * 10 + j) {
				case 0: // 左上
					constantX = -1, constantY = -1;
					if (myX < myY) {
						k = myX - 1;
					}
					else {
						k = myY - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX - 1][myY + constantY - 1] == -1) {
								constantX = -1, constantY = -1;
								while (stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = -1;
									constantX--, constantY--;
								}
							}
						}
						else {
							break;
						}
						constantX--, constantY--;
					}
					break;

				case 1: // 左
					constantX = -1, constantY = 0;
					k = myX - 1;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX - 1][myY + constantY] == -1) {
								constantX = -1, constantY = 0;
								while (stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = -1;
									constantX--;
								}
							}
						}
						else {
							break;
						}
						constantX--;
					}
					break;

				case 2: // 左下
					constantX = -1, constantY = 1;
					if (myX > 7 - myY) {
						k = 6 - myY;
					}
					else {
						k = myX - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX - 1][myY + constantY + 1] == -1) {
								constantX = -1, constantY = 1;
								while (stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = -1;
									constantX--, constantY++;
								}
							}
						}
						else {
							break;
						}
						constantX--, constantY++;
					}
					break;

				case 10: // 上
					constantX = 0, constantY = -1;
					k = myY - 1;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX][myY + constantY - 1] == -1) {
								constantX = 0, constantY = -1;
								while (stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = -1;
									constantY--;
								}
							}
						}
						else {
							break;
						}
						constantY--;
					}
					break;

				case 12: // 下
					constantX = 0, constantY = 1;
					k = 6 - myY;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX][myY + constantY + 1] == -1) {
								constantX = 0, constantY = 1;
								while (stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = -1;
									constantY++;
								}
							}
						}
						else {
							break;
						}
						constantY++;
					}
					break;

				case 20: // 右上
					constantX = 1, constantY = -1;
					if (7 - myX < myY) {
						k = 6 - myX;
					}
					else {
						k = myY - 1;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX + 1][myY + constantY - 1] == -1) {
								constantX = 1, constantY = -1;
								while (stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = -1;
									constantX++, constantY--;
								}
							}
						}
						else {
							break;
						}
						constantX++, constantY--;
					}
					break;

				case 21: // 右
					constantX = 1, constantY = 0;
					k = 6 - myX;
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX + 1][myY + constantY] == -1) {
								constantX = 1, constantY = 0;
								while (stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = -1;
									constantX++;
								}
							}
						}
						else {
							break;
						}
						constantX++;
					}
					break;

				case 22: // 右下
					constantX = 1, constantY = 1;
					if (7 - myX > 7 - myY) {
						k = 6 - myY;
					}
					else {
						k = 6 - myX;
					}
					while (k > 0) {
						k--;
						if (stone[myX + constantX][myY + constantY] == 1) {
							if (stone[myX + constantX + 1][myY + constantY + 1] == -1) {
								constantX = 1, constantY = 1;
								while (stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									stone[myX + constantX][myY + constantY] = -1;
									constantX++, constantY++;
								}
							}
						}
						else {
							break;
						}
						constantX++, constantY++;
					}
					break;
				}
			}
		}
	}
}


// クリック→配置処理
void setStone() {
	int mouseX, mouseY, myX, myY;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)		//マウスの左ボタンをクリックしたら
	{
		GetMousePoint(&mouseX, &mouseY);
		if (88 <= mouseX && mouseX <= 552) {
			if (8 <= mouseY && mouseY <= 472) {
				myX = (mouseX - 88) / 58;
				myY = (mouseY - 8) / 58;
				if (stone[myX][myY] == 0) {
					if (checkPosStone(myX, myY) == 1) {
						stone[myX][myY] = turn;
						Reverse(myX, myY);
						turn *= -1;
					}
					else {
						DrawString(20, 20, "そこに石は置けません", RED);
					}
				}
			}
		}
	}
}


// エンドボタン
void gameEndBottan() {
	int mouseX, mouseY;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)		//マウスの左ボタンをクリックしたら
	{
		GetMousePoint(&mouseX, &mouseY);
		if (5 <= mouseX && mouseX <= 75) {
			if (220 <= mouseY && mouseY <= 340) {
				endFlag = 1;
				//winjudge = 1;
			}
		}
	}
}

// パスボタン
void passBottan() {
	int mouseX, mouseY;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)		//マウスの左ボタンをクリックしたら
	{
		GetMousePoint(&mouseX, &mouseY);
		if (5 <= mouseX && mouseX <= 75) {
			if (350 <= mouseY && mouseY <= 470) {
				if (coolTimer == 0) {
					turn *= -1;
				}
			}
		}
		coolTimer = 1;
	}
	else {
		coolTimer = 0;
	}
}

// ゲーム終了処理
// ゲームが終了していれば1、まだ途中であれば0を返す
int gameEnd() {
	int greenField = 0, whiteStone = 0, brackStone = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (stone[i][j] == 0) {
				greenField++;
			}
			else if (stone[i][j] == 1) {
				whiteStone++;
			}
			else if (stone[i][j] == -1) {
				brackStone++;
			}
		}
	}
	if (endFlag == 1) {
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


// 表示設定
void Display() {
	int blackcount = 0, whitecount = 0;
	tmpblack = blackcount;
	tmpwhite = whitecount;
	char BLACKBUFF[128] , WHITEBUFF[128];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (stone[i][j] == -1) {
				blackcount++;
			}
			else if (stone[i][j] == 1) {
				whitecount++;
			}
		}
	}

	DrawString(580, 25, "手番", WHITE);
	if (turn == 1) {
		DrawString(580, 45, "WHITE", WHITE);
	}
	else {
		DrawString(580, 45, "BLACK", WHITE);
	}

	sprintf_s(BLACKBUFF, 128, "黒石 :%d", blackcount);
	sprintf_s(WHITEBUFF, 128, "白石 :%d", whitecount);

	DrawString(570, 320, BLACKBUFF, WHITE);
	DrawString(570, 340, WHITEBUFF, WHITE);
}

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0) {	//初期化と裏画面化
		return -1;
	}

	ChangeWindowMode(TRUE);			// ウィンドウモードで起動する
	SetGraphMode(640, 480, 16);		// ウィンドウサイズ(640 X 480) 使用カラー16bit(65536色)
	SetWindowText("othello");		// タイトル名
	SetMouseDispFlag(TRUE);

	while (1) {
		LoadGraphScreen(100, 80, "othello.png", TRUE);

		SetFontSize(96);
		DrawString(20, 80, "Othello Game", WHITE);

		SetFontSize(24);
		DrawString(200, 400, "START →→→ SPACEKEY", WHITE);

		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			break;
		}
	}

	DrawBox(0, 0, 640, 480, BLACK, TRUE);
	DrawTriangle(180, 194, 195, 202, 180, 210, WHITE, TRUE);
	int count = 0;

	while (1) {

		SetFontSize(24);
		DrawString(200, 190, "vs 人間", WHITE);
		DrawString(200, 210, "vs コンピューター", WHITE);
		DrawString(200, 250, "START →→→ A", WHITE);

		while (CheckHitKey(KEY_INPUT_DOWN) == 1 && count == 0) {
			DrawBox(180, 194, 195, 210, BLACK, TRUE);
			DrawTriangle(180, 214, 195, 222, 180, 230, WHITE, TRUE);
			count = 1;
		}
		while (CheckHitKey(KEY_INPUT_UP) == 1 && count == 1) {
			DrawBox(180, 214, 195, 230, BLACK, TRUE);
			DrawTriangle(180, 194, 195, 202, 180, 210, WHITE, TRUE);
			count = 0;
		}

		if (CheckHitKey(KEY_INPUT_A) == 1) {
			break;
		}
	}

	if (count == 0) {
		while (1) {
			SetFontSize(16);
			boardInit();
			while (gameEnd() == 0) {
				boardPrint();
				setStone();
				passBottan();
				gameEndBottan();
				Display();
				drawStone();
				ScreenFlip(); // 裏のスクリーンを表に投射
				if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { // エスケープキーで強制終了
					return 0;
				}
			}
			/*if (winjudge == 0) {
				DrawBox(0, 0, 640, 480, BLACK, TRUE);
				SetFontSize(96);
				while (1) {
					if (tmpblack < tmpwhite) {
						SetFontSize(96);
						DrawString(40, 80, "白WIN!!!", WHITE);
						SetFontSize(48);
						DrawString(20, 200, "SKIP　→→→　A", WHITE);
					}
					else {
						SetFontSize(96);
						DrawString(40, 80, "黒WIN!!!", WHITE);
						SetFontSize(48);
						DrawString(20, 200, "SKIP　→→→　A", WHITE);
					}
					if (CheckHitKey(KEY_INPUT_A) == 1) {
						break;
					}
				}
			}*/

			SetFontSize(16);
			DrawBox(120, 225, 520, 255, WHITE, TRUE);
			DrawString(140, 233, "もう一度対戦する(continue)　→→→　cボタン", BLUE);
			DrawBox(120, 255, 520, 285, WHITE, TRUE);
			DrawString(140, 263, "やめる場合(end)　→→→　eボタン", RED);
			ScreenFlip(); // 裏のスクリーンを表に投射
			WaitKey();
			if (CheckHitKey(KEY_INPUT_C) == 1) {	// 盤面を初期状態にリセット
				boardInit();
			}
			else if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				break;
			}
		}
	}
	else if (count == 1) {
		while (1) {
			SetFontSize(16);
			boardInit();
			while (gameEnd() == 0) {
				boardPrintAlpha();
				setStone();
				passBottan();
				gameEndBottan();
				Display();
				drawStone();
				ScreenFlip(); // 裏のスクリーンを表に投射
				if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { // エスケープキーで強制終了
					return 0;
				}
			}
			/*if (winjudge == 0) {
				DrawBox(0, 0, 640, 480, BLACK, TRUE);
				SetFontSize(96);
				while (1) {
					if (tmpblack < tmpwhite) {
						SetFontSize(96);
						DrawString(40, 80, "白WIN!!!", WHITE);
						SetFontSize(48);
						DrawString(20, 200, "SKIP　→→→　A", WHITE);
					}
					else {
						SetFontSize(96);
						DrawString(40, 80, "黒WIN!!!", WHITE);
						SetFontSize(48);
						DrawString(20, 200, "SKIP　→→→　A", WHITE);
					}
					if (CheckHitKey(KEY_INPUT_A) == 1) {
						break;
					}
				}
			}*/
			SetFontSize(16);
			DrawBox(120, 225, 520, 255, WHITE, TRUE);
			DrawString(140, 233, "もう一度対戦する(continue)　→→→　cボタン", BLUE);
			DrawBox(120, 255, 520, 285, WHITE, TRUE);
			DrawString(140, 263, "やめる場合(end)　→→→　eボタン", RED);
			ScreenFlip(); // 裏のスクリーンを表に投射
			WaitKey();
			if (CheckHitKey(KEY_INPUT_C) == 1) {	// 盤面を初期状態にリセット
				boardInit();
			}
			else if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				break;
			}
		}
	}

	DxLib_End();
	return 0;
}