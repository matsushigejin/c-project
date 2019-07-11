#include "DxLib.h"

void boardPrint();
void white_stone(int x, int y);
void black_stone(int x, int y);

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);      // ウィンドウモードで起動する
	SetGraphMode(480, 480, 16);  // ウィンドウサイズ(540×540) 使用カラー16bit(65536色)
	SetWindowText("othello");   // タイトル名

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	boardPrint();
	white_stone(210, 210);
	white_stone(270, 270);
	black_stone(210, 270);
	black_stone(270, 210);

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
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