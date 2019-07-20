#include "DXlib.h"
#include <stdlib.h>
#include <stdio.h>

#define WHITE	GetColor(255, 255, 255)
#define BLACK	GetColor(0, 0, 0)
#define GREEN	GetColor(0, 128, 0)
#define RED		GetColor(255, 0, 0)
#define BLUE	GetColor(0, 0, 255)
#define YELLOW	GetColor(255, 255, 0)
#define TEAL	GetColor(0, 128, 128)
#define OLIVE	GetColor(128, 128, 0)
#define BUFFSIZE	1024

struct Othello {
	// �O���[�o���ϐ�
	int stone[8][8];
	int stonelevel[8][8];
	/*	{ 100, -40, 20, 5, 5, 20, -40, 100 },
		{ -40, -80, -1, -1, -1, -1, -80, -40 },
		{ 20, -1, 5, 1, 1, 5, -1, 20 },
		{ 5, -1, 1, 0, 0, 1, -1, 5 },
		{ 5, -1, 1, 0, 0, 1, -1, 5 },
		{ 20, -1, 5, 1, 1, 5, -1, 20 },
		{ -40, -80, -1, -1, -1, -1, -80, -40 },
		{ 100, -40, 20, 5, 5, 20, -40, 100 }	*/
	int endFlag;
	int turn; // ��ԁE�E�E��荕
	int coolTimer;
	int tmpblack, tmpwhite;
	int winjudge;
	int count_stone;		//���]����΂̌�
	
};

Othello data;

char BLACKBUFF[128], WHITEBUFF[128];

// �֐�
void boardInit();
void boardInitCPU();
void boardPrint();
void boardPrintCPUlv1();
void boardPrintCPUlv2();
void boardPrintCPUlv3();
void drawStone();
void setStone();
int gameEnd();
void passBottan();
void gameEndBottan();
void Display();
int checkPosStone(int myX, int myY);
void Reverse(int myX, int myY);
void FileInput();
void FileOutput();
void CPU1_setStone();
void CPU2_setStone();
void CPU3_setStone();

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

// �Ֆʏ������
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

// �I�Z���Օ`��
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

	// �G���h�{�^��
	DrawBox(5, 220, 75, 340, TEAL, TRUE);
	DrawString(28, 280, "End", BLACK);
	
	// �p�X�{�^��
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

	// �G���h�{�^��
	DrawBox(5, 220, 75, 340, TEAL, TRUE);
	DrawString(28, 280, "End", BLACK);

	// �p�X�{�^��
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

	// �G���h�{�^��
	DrawBox(5, 220, 75, 340, TEAL, TRUE);
	DrawString(28, 280, "End", BLACK);

	// �p�X�{�^��
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

	// �G���h�{�^��
	DrawBox(5, 220, 75, 340, TEAL, TRUE);
	DrawString(28, 280, "End", BLACK);

	// �p�X�{�^��
	DrawBox(5, 350, 75, 470, OLIVE, TRUE);
	DrawString(25, 410, "PASS", BLACK);

}

// �Ε`��
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


// ���]����
void Reverse(int myX, int myY) {
	int whichplayer = data.turn;
	int constantX = 0, constantY = 0;		//�萔

	for (int i = 0; i < 3; i++) {		//3x3
		for (int j = 0; j < 3; j++) {
			int k = 0;
			// �������΂�u�����R�}�̏����𖳎�
			if (i == 1 && j == 1) {
				continue;
			}

			if (whichplayer == 1) { //��
				switch (i * 10 + j) {
				case 0: // ����
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

				case 1: // ��
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

				case 10: // ��
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

				case 12: // ��
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

				case 21: // �E
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
			else if (whichplayer == -1) { //��
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

				case 1: // ��
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

				case 10: // ��
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

				case 12: // ��
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

				case 21: // �E
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

void CPU1_setStone() {		//1�ԑ�������Ƃ���ɐ΂�u��
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

void CPU2_setStone() {		//1�ԏ��Ȃ�����Ƃ���ɐ΂�u��
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

void CPU3_setStone() {		//�D��x�̍����Ƃ���ɒu��
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


// �Q�[���I������
// �Q�[�����I�����Ă����1�A�܂��r���ł����0��Ԃ�
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

	if (greenField == 0) {	// �Ֆʂ�0�����݂��Ȃ����󂫔Ղ��Ȃ���1��Ԃ�
		return 1;
	}
	else {	// 0�����݂���(�󂫔Ղ�����)�ꍇ
		if (whiteStone == 0) {	// ���̐΂����݂��Ȃ���1��Ԃ�
			return 1;
		}
		if (brackStone == 0) {	// ���̐΂����݂��Ȃ���1��Ԃ�
			return 1;
		}
		return 0;
	}
	return 1;
}


// �\���ݒ�
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

	DrawString(580, 25, "���", WHITE);
	if (data.turn == 1) {
		DrawString(580, 45, "WHITE", WHITE);
	}
	else {
		DrawString(580, 45, "BLACK", WHITE);
	}

	sprintf_s(BLACKBUFF, 128, "���� :%d", blackcount);
	sprintf_s(WHITEBUFF, 128, "���� :%d", whitecount);
	data.tmpblack = blackcount;
	data.tmpwhite = whitecount;

	DrawString(570, 320, BLACKBUFF, WHITE);
	DrawString(570, 340, WHITEBUFF, WHITE);
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

		//txt�t�@�C���ɕ\��
		fprintf(fp, "���� : %d\n", data.tmpblack);
		fprintf(fp, "���� : %d\n", data.tmpwhite);
		if (data.tmpblack > data.tmpwhite) {
			fputs("���̏���!!!", fp);
		}
		else if (data.tmpblack < data.tmpwhite) {
			fputs("���̏���!!!", fp);
		}

		fclose(fp);
	}
}

