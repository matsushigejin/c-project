#pragma once

#include "DXlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "Othello.h"

// 反転処理
void Reverse(int myX, int myY) {
	int whichplayer = data.turn;
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
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX - 1][myY + constantY - 1] == 1) {
								constantX = -1, constantY = -1;
								while (data.stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = 1;
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
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX - 1][myY + constantY] == 1) {
								constantX = -1, constantY = 0;
								while (data.stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = 1;
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
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX - 1][myY + constantY + 1] == 1) {
								constantX = -1, constantY = 1;
								while (data.stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = 1;
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
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX][myY + constantY - 1] == 1) {
								constantX = 0, constantY = -1;
								while (data.stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = 1;
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
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX][myY + constantY + 1] == 1) {
								constantX = 0, constantY = 1;
								while (data.stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = 1;
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
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX + 1][myY + constantY - 1] == 1) {
								constantX = 1, constantY = -1;
								while (data.stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = 1;
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
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX + 1][myY + constantY] == 1) {
								constantX = 1, constantY = 0;
								while (data.stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = 1;
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
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX + 1][myY + constantY + 1] == 1) {
								constantX = 1, constantY = 1;
								while (data.stone[myX + constantX][myY + constantY] == -1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = 1;
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
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX - 1][myY + constantY - 1] == -1) {
								constantX = -1, constantY = -1;
								while (data.stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = -1;
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
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX - 1][myY + constantY] == -1) {
								constantX = -1, constantY = 0;
								while (data.stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = -1;
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
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX - 1][myY + constantY + 1] == -1) {
								constantX = -1, constantY = 1;
								while (data.stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = -1;
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
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX][myY + constantY - 1] == -1) {
								constantX = 0, constantY = -1;
								while (data.stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = -1;
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
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX][myY + constantY + 1] == -1) {
								constantX = 0, constantY = 1;
								while (data.stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = -1;
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
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX + 1][myY + constantY - 1] == -1) {
								constantX = 1, constantY = -1;
								while (data.stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = -1;
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
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX + 1][myY + constantY] == -1) {
								constantX = 1, constantY = 0;
								while (data.stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = -1;
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
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX + 1][myY + constantY + 1] == -1) {
								constantX = 1, constantY = 1;
								while (data.stone[myX + constantX][myY + constantY] == 1) {
									if ((myX + constantX) <= -1 || (myX + constantX) >= 8 || (myY + constantY) <= -1 || (myY + constantY) >= 8) {
										break;
									}
									data.stone[myX + constantX][myY + constantY] = -1;
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
