#pragma once

#include "DXlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "Othello.h"

void CPU1_setStone() {		//1番多く取れるところに石を置く
	int max = 0;
	int cpuX, cpuY;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (data.stone[i][j] == 0) {
				if (checkPosStone(i, j) == 1) {
					if (max < data.count_stone || (max == data.count_stone && GetRand(1) == 0)) {
						max = data.count_stone;
						cpuX = i;
						cpuY = j;
					}
				}
			}
		}
	}
	data.stone[cpuX][cpuY] = data.turn;
	Reverse(cpuX, cpuY);
	data.turn *= -1;

}

void CPU2_setStone() {		//1番少なく取れるところに石を置く
	int min = 100;
	int cpuX, cpuY;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (data.stone[i][j] == 0) {
				if (checkPosStone(i, j) == 1) {
					if (min > data.count_stone || (min == data.count_stone && GetRand(1) == 0)) {
						min = data.count_stone;
						cpuX = i;
						cpuY = j;
					}
				}
			}
		}
	}
	data.stone[cpuX][cpuY] = data.turn;
	Reverse(cpuX, cpuY);
	data.turn *= -1;

}

void CPU3_setStone() {		//優先度の高いところに置く
	int tmp = -100;
	int cpuX, cpuY;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (data.stone[i][j] == 0) {
				if (checkPosStone(i, j) == 1) {
					if (tmp < data.stonelevel[i][j] || (tmp == data.stonelevel[i][j] && GetRand(1) == 0)) {
						tmp = data.count_stone;
						cpuX = i;
						cpuY = j;
					}
				}
			}
		}
	}
	data.stone[cpuX][cpuY] = data.turn;
	Reverse(cpuX, cpuY);
	data.turn *= -1;
}

