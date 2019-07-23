#pragma once

#define WHITE	GetColor(255, 255, 255)
#define BLACK	GetColor(0, 0, 0)
#define GREEN	GetColor(0, 128, 0)
#define RED		GetColor(255, 0, 0)
#define BLUE	GetColor(0, 0, 255)
#define YELLOW	GetColor(255, 255, 0)
#define TEAL	GetColor(0, 128, 128)
#define OLIVE	GetColor(128, 128, 0)
#define BUFFSIZE	1024

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

struct Othello {
	// グローバル変数
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
	int turn; // 手番・・・先手黒
	int coolTimer;
	int tmpblack, tmpwhite;
	int winjudge;
	int count_stone;		//反転する石の個数

};

Othello data;

char BLACKBUFF[128], WHITEBUFF[128];


