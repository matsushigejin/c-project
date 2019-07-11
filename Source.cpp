#include "DxLib.h"

void boardPrint();
void white_stone(int x, int y);
void black_stone(int x, int y);

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);      // �E�B���h�E���[�h�ŋN������
	SetGraphMode(480, 480, 16);  // �E�B���h�E�T�C�Y(540�~540) �g�p�J���[16bit(65536�F)
	SetWindowText("othello");   // �^�C�g����

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	boardPrint();
	white_stone(210, 210);
	white_stone(270, 270);
	black_stone(210, 270);
	black_stone(270, 210);

	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

void boardPrint() {
	DrawBox(0, 0, 479, 479, GetColor(0, 128, 0), TRUE);

	for (int i = 0; i < 8; i++) {
		DrawLine(0, 60 + i * 60, 479, 60 + i * 60, GetColor(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		DrawLine(60 + i * 60, 0, 60 + i * 60, 479, GetColor(0, 0, 0));
	}
}

void white_stone(int x, int y) {
	DrawCircle(x, y, 28, GetColor(255, 255, 255), TRUE);
}

void black_stone(int x, int y) {
	DrawCircle(x, y, 28, GetColor(0, 0, 0), TRUE);
}