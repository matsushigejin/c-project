#pragma once

#include "DXlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "Othello.h"

// �Δz�u����
// 1�Œu���āA0�ł����ɂ͐΂�u�����Ƃ��ł��Ȃ�
int checkPosStone(int myX, int myY) {
	int whichplayer = data.turn;
	int constantX = 0, constantY = 0;		//�萔
	data.count_stone = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int k = 0;
			// �������΂�u�����R�}�̏������΂�
			if (i == 1 && j == 1) {
				continue;
			}

			if (whichplayer == 1) { //��
				switch (i * 10 + j) {
				case 0: // ����
					constantX = -1, constantY = -1;
					if (myX < myY) {
						k = myX - 1;
					}
					else {
						k = myY - 1;
					}
					while (k > 0) {
						k--;
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX - 1][myY + constantY - 1] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX--, constantY--;
						data.count_stone++;
					}
					break;

				case 1: // ��
					constantX = -1, constantY = 0;
					k = myX - 1;
					while (k > 0) {
						k--;
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX - 1][myY + constantY] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX--;
						data.count_stone++;
					}
					break;

				case 2: // ����
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
								return 1;
							}
						}
						else {
							break;
						}
						constantX--, constantY++;
						data.count_stone++;
					}
					break;

				case 10: // ��
					constantX = 0, constantY = -1;
					k = myY - 1;
					while (k > 0) {
						k--;
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX][myY + constantY - 1] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantY--;
						data.count_stone++;
					}
					break;

				case 12: // ��
					constantX = 0, constantY = 1;
					k = 6 - myY;
					while (k > 0) {
						k--;
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX][myY + constantY + 1] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantY++;
						data.count_stone++;
					}
					break;

				case 20: // �E��
					constantX = 1, constantY = -1;
					if (7 - myX < myY) k = 6 - myX;
					else k = myY - 1;
					while (k > 0) {
						k--;
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX + 1][myY + constantY - 1] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX++, constantY--;
						data.count_stone++;
					}
					break;

				case 21: // �E
					constantX = 1, constantY = 0;
					k = 6 - myX;
					while (k > 0) {
						k--;
						if (data.stone[myX + constantX][myY + constantY] == -1) {
							if (data.stone[myX + constantX + 1][myY + constantY] == 1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX++;
						data.count_stone++;
					}
					break;

				case 22: // �E��
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
								return 1;
							}
						}
						else {
							break;
						}
						constantX++, constantY++;
						data.count_stone++;
					}
					break;
				}
			}
			else if (whichplayer == -1) { // �u�������΂����������ꍇ
				switch (i * 10 + j) {
				case 0: // ����
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
								return 1;
							}
						}
						else {
							break;
						}
						constantX--, constantY--;
					}
					break;

				case 1: // ��
					constantX = -1, constantY = 0;
					k = myX - 1;
					while (k > 0) {
						k--;
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX - 1][myY + constantY] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX--;
					}
					break;

				case 2: // ����
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
								return 1;
							}
						}
						else {
							break;
						}
						constantX--, constantY++;
					}
					break;

				case 10: // ��
					constantX = 0, constantY = -1;
					k = myY - 1;
					while (k > 0) {
						k--;
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX][myY + constantY - 1] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantY--;
					}
					break;

				case 12: // ��
					constantX = 0, constantY = 1;
					k = 6 - myY;
					while (k > 0) {
						k--;
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX][myY + constantY + 1] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantY++;
					}
					break;

				case 20: // �E��
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
								return 1;
							}
						}
						else {
							break;
						}
						constantX++, constantY--;
					}
					break;

				case 21: // �E
					constantX = 1, constantY = 0;
					k = 6 - myX;
					while (k > 0) {
						k--;
						if (data.stone[myX + constantX][myY + constantY] == 1) {
							if (data.stone[myX + constantX + 1][myY + constantY] == -1) {
								return 1;
							}
						}
						else {
							break;
						}
						constantX++;
					}
					break;

				case 22: // �E��
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
				DrawString(0, 0, "�G���[���������Ă��܂�", RED);
				return 0;
			}
		}
	}
	return 0;
}
