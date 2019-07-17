// projectA.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <stdlib.h>

#define CHARBUFF 124
#define BUFFSIZE 128

#define USEMUTEX


struct Stone
{
	int sx[8];
	int sy[8];
};

struct Color {
	int black;
	int white;
	int none;
};
void getGurrentDirectory(char * currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

// グローバル変数
int stone[8][8];
struct Stone stonelevel[8][8] = {
	{ 100, -40, 20, 5, 5, 20, -40, 100 },
	{ -40, -80, -1, -1, -1, -1, -80, -40 },
	{ 20, -1, 5, 1, 1, 5, -1, 20 },
	{ 5, -1, 1, 0, 0, 1, -1, 5 },
	{ 5, -1, 1, 0, 0, 1, -1, 5 },
	{ 20, -1, 5, 1, 1, 5, -1, 20 },
	{ -40, -80, -1, -1, -1, -1, -80, -40 },
	{ 100, -40, 20, 5, 5, 20, -40, 100 }
};

struct Color set;

int main()
{

	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);

	char section1[CHARBUFF];
	sprintf_s(section1, "stone");

	char keyWord1[CHARBUFF];
	char keyWord2[CHARBUFF];
	char keyWord3[CHARBUFF];
	
	char keyValue[CHARBUFF];

	sprintf_s(keyWord1, "BLACK");
	sprintf_s(keyWord2, "WHITE");
	sprintf_s(keyWord3, "NONE");
	
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	
	if (GetPrivateProfileString(section1, keyWord1, "none", keyValue, CHARBUFF, settingFile) != 0) {
		fprintf_s(stdout, "%s = %s\n", keyWord1, keyValue);
		set.black = atoi(keyValue);
	}
	else {
		fprintf_s(stdout, "%s doesn't contain [%s] %s\n", settingFile, section1, keyWord1);
	}
	if (GetPrivateProfileString(section1, keyWord2, "none", keyValue, CHARBUFF, settingFile) != 0) {
		fprintf_s(stdout, "%s = %s\n", keyWord2, keyValue);
		set.white = atoi(keyValue);
	}
	else {
		fprintf_s(stdout, "%s doesn't contain [%s] %s\n", settingFile, section1, keyWord2);
	}
	if (GetPrivateProfileString(section1, keyWord3, "none", keyValue, CHARBUFF, settingFile) != 0) {
		fprintf_s(stdout, "%s = %s\n", keyWord3, keyValue);
		set.none = atoi(keyValue);
	}
	else {
		fprintf_s(stdout, "%s doesn't contain [%s] %s\n", settingFile, section1, keyWord3);
	}

	return 0;
}
