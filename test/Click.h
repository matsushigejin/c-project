#pragma once

#include "DXlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "Othello.h"

// �N���b�N���z�u����
void setStone() {
	int mouseX, mouseY, myX, myY;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)		//�}�E�X�̍��{�^�����N���b�N������
	{
		GetMousePoint(&mouseX, &mouseY);
		if (88 <= mouseX && mouseX <= 552) {
			if (8 <= mouseY && mouseY <= 472) {
				myX = (mouseX - 88) / 58;
				myY = (mouseY - 8) / 58;
				if (data.stone[myX][myY] == 0) {
					if (checkPosStone(myX, myY) == 1) {
						data.stone[myX][myY] = data.turn;
						Reverse(myX, myY);
						data.turn *= -1;
					}
					else {
						DrawString(20, 20, "�����ɐ΂͒u���܂���", RED);
					}
				}
			}
		}
	}
}

// �G���h�{�^��
void gameEndBottan() {
	int mouseX, mouseY;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)		//�}�E�X�̍��{�^�����N���b�N������
	{
		GetMousePoint(&mouseX, &mouseY);
		if (5 <= mouseX && mouseX <= 75) {
			if (220 <= mouseY && mouseY <= 340) {
				data.endFlag = 1;
				data.winjudge = 1;
			}
		}
	}
}

// �p�X�{�^��
void passBottan() {
	int mouseX, mouseY;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)		//�}�E�X�̍��{�^�����N���b�N������
	{
		GetMousePoint(&mouseX, &mouseY);
		if (5 <= mouseX && mouseX <= 75) {
			if (350 <= mouseY && mouseY <= 470) {
				if (data.coolTimer == 0) {
					data.turn *= -1;
				}
			}
		}
		data.coolTimer = 1;
	}
	else {
		data.coolTimer = 0;
	}
}
