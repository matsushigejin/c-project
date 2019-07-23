#include "DXlib.h"
#include <stdlib.h>
#include <stdio.h>

#include "Othello.h"
#include "Board.h"
#include "Click.h"
#include "CPU.h"
#include "Gamebasic.h"
#include "Othello.h"
#include "Reverse.h"
#include "Stonejudge.h"

void getGurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(BUFFSIZE, currentDirectory);
}

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0) {	//�������Ɨ���ʉ�
		return -1;
	}

	FileInput();

	char currentDirectory[BUFFSIZE];
	getGurrentDirectory(currentDirectory);

	char str[4][BUFFSIZE] = { "endflag", "turn", "cooltimer", "winjudge" };
	data.endFlag = GetPrivateProfileInt("othello1", str[0], -10, "E:othellodata.ini");
	data.turn = GetPrivateProfileInt("othello1", str[1], -10, "E:othellodata.ini");
	data.coolTimer = GetPrivateProfileInt("othello1", str[2], -10, "E:othellodata.ini");
	data.winjudge = GetPrivateProfileInt("othello1", str[3], -10, "E:othellodata.ini");

	char buff[5][BUFFSIZE];
	char tmpdata[5][BUFFSIZE] = { "p1", "p2", "p3", "p4", "p5" };
	for (int i = 0; i < 5; i++) {
		GetPrivateProfileString("picture1", tmpdata[i], "none", buff[i], BUFFSIZE, "E:othellodata.ini");
	}

	ChangeWindowMode(TRUE);			// �E�B���h�E���[�h�ŋN������
	SetGraphMode(640, 480, 16);		// �E�B���h�E�T�C�Y(640 X 480) �g�p�J���[16bit(65536�F)
	SetWindowText("othello");		// �^�C�g����
	SetMouseDispFlag(TRUE);

	while (1) {
		LoadGraphScreen(100, 80, buff[4], TRUE);

		SetFontSize(96);
		DrawString(20, 80, "Othello Game", WHITE);

		SetFontSize(24);
		DrawString(200, 400, "START ������ SPACEKEY", WHITE);

		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			break;
		}
	}

	DrawBox(0, 0, 640, 480, BLACK, TRUE);
	DrawBox(95, 15, 200, 190, BLUE, FALSE);
	int count = 0;

	while (1) {

		LoadGraphScreen(100, 20, buff[0], TRUE);
		LoadGraphScreen(350, 20, buff[1], TRUE);
		LoadGraphScreen(100, 250, buff[2], TRUE);
		LoadGraphScreen(350, 250, buff[3], TRUE);
		SetFontSize(24);

		DrawString(100, 190, "vs �l��", WHITE);
		DrawString(350, 190, "vs CPU lv1", WHITE);
		DrawString(100, 420, "vs CPU lv2", WHITE);
		DrawString(350, 420, "vs CPU lv3", WHITE);
		DrawString(200, 450, "START ������ A", WHITE);

		while (CheckHitKey(KEY_INPUT_RIGHT) == 1 && count == 0) {
			DrawBox(345, 15, 490, 190, BLUE, FALSE);
			DrawBox(95, 15, 200, 190, BLACK, FALSE);
			count = 1;
		}
		while (CheckHitKey(KEY_INPUT_DOWN) == 1 && count == 0) {
			DrawBox(95, 245, 240, 420, BLUE, FALSE);
			DrawBox(95, 15, 200, 190, BLACK, FALSE);
			count = 10;
		}
		while (CheckHitKey(KEY_INPUT_LEFT) == 1 && count == 1) {
			DrawBox(95, 15, 200, 190, BLUE, FALSE);
			DrawBox(345, 15, 490, 190, BLACK, FALSE);
			count = 0;
		}
		while (CheckHitKey(KEY_INPUT_DOWN) == 1 && count == 1) {
			DrawBox(345, 245, 490, 420, BLUE, FALSE);
			DrawBox(345, 15, 490, 190, BLACK, FALSE);
			count = 11;
		}
		while (CheckHitKey(KEY_INPUT_UP) == 1 && count == 10) {
			DrawBox(95, 15, 200, 190, BLUE, FALSE);
			DrawBox(95, 245, 240, 420, BLACK, FALSE);
			count = 0;
		}
		while (CheckHitKey(KEY_INPUT_RIGHT) == 1 && count == 10) {
			DrawBox(345, 245, 490, 420, BLUE, FALSE);
			DrawBox(95, 245, 240, 420, BLACK, FALSE);
			count = 11;
		}
		while (CheckHitKey(KEY_INPUT_UP) == 1 && count == 11) {
			DrawBox(345, 15, 490, 190, BLUE, FALSE);
			DrawBox(345, 245, 490, 420, BLACK, FALSE);
			count = 1;
		}
		while (CheckHitKey(KEY_INPUT_LEFT) == 1 && count == 11) {
			DrawBox(95, 245, 240, 420, BLUE, FALSE);
			DrawBox(345, 245, 490, 420, BLACK, FALSE);
			count = 10;
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
				ScreenFlip(); // ���̃X�N���[����\�ɓ���
				if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { // �G�X�P�[�v�L�[�ŋ����I��
					return 0;
				}
			}
			if (data.winjudge == 0) {
				DrawBox(0, 0, 640, 480, BLACK, TRUE);
				SetFontSize(96);
				while (1) {
					if (data.tmpblack < data.tmpwhite) {
						SetFontSize(96);
						DrawString(80, 80, "��WIN!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					else if (data.tmpblack > data.tmpwhite) {
						SetFontSize(96);
						DrawString(80, 80, "��WIN!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					else {
						SetFontSize(96);
						DrawString(80, 80, "DRAW!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					if (CheckHitKey(KEY_INPUT_A) == 1) {
						break;
					}
				}
			}
			FileOutput();
			SetFontSize(16);
			DrawBox(120, 225, 520, 255, WHITE, TRUE);
			DrawString(140, 233, "������x�ΐ킷��(continue)�@�������@c�{�^��", BLUE);
			DrawBox(120, 255, 520, 285, WHITE, TRUE);
			DrawString(140, 263, "��߂�ꍇ(end)�@�������@e�{�^��", RED);
			ScreenFlip(); // ���̃X�N���[����\�ɓ���
			WaitKey();
			if (CheckHitKey(KEY_INPUT_C) == 1) {	// �Ֆʂ�������ԂɃ��Z�b�g
				boardInit();
				data.winjudge = 0;
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
				boardPrintCPUlv1();
				if (data.turn == -1) {
					setStone();
				}
				else if (data.turn == 1) {
					CPU1_setStone();
				}
				passBottan();
				gameEndBottan();
				Display();
				drawStone();
				ScreenFlip(); // ���̃X�N���[����\�ɓ���
				if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { // �G�X�P�[�v�L�[�ŋ����I��
					return 0;
				}
			}
			if (data.winjudge == 0) {
				DrawBox(0, 0, 640, 480, BLACK, TRUE);
				SetFontSize(96);
				while (1) {
					if (data.tmpblack < data.tmpwhite) {
						SetFontSize(96);
						DrawString(80, 80, "��WIN!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					else if (data.tmpblack > data.tmpwhite) {
						SetFontSize(96);
						DrawString(80, 80, "��WIN!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					else {
						SetFontSize(96);
						DrawString(80, 80, "DRAW!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					if (CheckHitKey(KEY_INPUT_A) == 1) {
						break;
					}
				}
			}
			FileOutput();
			SetFontSize(16);
			DrawBox(120, 225, 520, 255, WHITE, TRUE);
			DrawString(140, 233, "������x�ΐ킷��(continue)�@�������@c�{�^��", BLUE);
			DrawBox(120, 255, 520, 285, WHITE, TRUE);
			DrawString(140, 263, "��߂�ꍇ(end)�@�������@e�{�^��", RED);
			ScreenFlip(); // ���̃X�N���[����\�ɓ���
			WaitKey();
			if (CheckHitKey(KEY_INPUT_C) == 1) {	// �Ֆʂ�������ԂɃ��Z�b�g
				boardInit();
				data.winjudge = 0;
			}
			else if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				break;
			}
		}
	}
	else if (count == 10) {
		while (1) {
			SetFontSize(16);
			boardInit();
			while (gameEnd() == 0) {
				boardPrintCPUlv2();
				if (data.turn == -1) {
					setStone();
				}
				else if (data.turn == 1) {
					for (int i = 0; i < 10000; i++) {
					}
					CPU2_setStone();
				}
				passBottan();
				gameEndBottan();
				Display();
				drawStone();
				ScreenFlip(); // ���̃X�N���[����\�ɓ���
				if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { // �G�X�P�[�v�L�[�ŋ����I��
					return 0;
				}
			}
			if (data.winjudge == 0) {
				DrawBox(0, 0, 640, 480, BLACK, TRUE);
				SetFontSize(96);
				while (1) {
					if (data.tmpblack < data.tmpwhite) {
						SetFontSize(96);
						DrawString(80, 80, "��WIN!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					else if (data.tmpblack > data.tmpwhite) {
						SetFontSize(96);
						DrawString(80, 80, "��WIN!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					else {
						SetFontSize(96);
						DrawString(80, 80, "DRAW!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					if (CheckHitKey(KEY_INPUT_A) == 1) {
						break;
					}
				}
			}
			FileOutput();
			SetFontSize(16);
			DrawBox(120, 225, 520, 255, WHITE, TRUE);
			DrawString(140, 233, "������x�ΐ킷��(continue)�@�������@c�{�^��", BLUE);
			DrawBox(120, 255, 520, 285, WHITE, TRUE);
			DrawString(140, 263, "��߂�ꍇ(end)�@�������@e�{�^��", RED);
			ScreenFlip(); // ���̃X�N���[����\�ɓ���
			WaitKey();
			if (CheckHitKey(KEY_INPUT_C) == 1) {	// �Ֆʂ�������ԂɃ��Z�b�g
				boardInit();
				data.winjudge = 0;
			}
			else if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				break;
			}
		}
	}
	else if (count == 11) {
		while (1) {
			SetFontSize(16);
			boardInit();
			while (gameEnd() == 0) {
				boardPrintCPUlv3();
				if (data.turn == -1) {
					setStone();
				}
				else if (data.turn == 1) {
					for (int i = 0; i < 10000; i++) {
					}
					CPU3_setStone();
				}
				passBottan();
				gameEndBottan();
				Display();
				drawStone();
				ScreenFlip(); // ���̃X�N���[����\�ɓ���
				if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { // �G�X�P�[�v�L�[�ŋ����I��
					return 0;
				}
			}
			if (data.winjudge == 0) {
				DrawBox(0, 0, 640, 480, BLACK, TRUE);
				SetFontSize(96);
				while (1) {
					if (data.tmpblack < data.tmpwhite) {
						SetFontSize(96);
						DrawString(80, 80, "��WIN!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					else if (data.tmpblack > data.tmpwhite) {
						SetFontSize(96);
						DrawString(80, 80, "��WIN!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					else {
						SetFontSize(96);
						DrawString(80, 80, "DRAW!!!", WHITE);
						SetFontSize(32);
						DrawString(100, 200, "SKIP�@�������@A", WHITE);
					}
					if (CheckHitKey(KEY_INPUT_A) == 1) {
						break;
					}
				}
			}
			FileOutput();
			SetFontSize(16);
			DrawBox(120, 225, 520, 255, WHITE, TRUE);
			DrawString(140, 233, "������x�ΐ킷��(continue)�@�������@c�{�^��", BLUE);
			DrawBox(120, 255, 520, 285, WHITE, TRUE);
			DrawString(140, 263, "��߂�ꍇ(end)�@�������@e�{�^��", RED);
			ScreenFlip(); // ���̃X�N���[����\�ɓ���
			WaitKey();
			if (CheckHitKey(KEY_INPUT_C) == 1) {	// �Ֆʂ�������ԂɃ��Z�b�g
				boardInit();
				data.winjudge = 0;
			}
			else if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				break;
			}
		}
	}

	DxLib_End();
	return 0;
}



