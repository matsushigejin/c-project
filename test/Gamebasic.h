#pragma once

#include "DXlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "Othello.h"

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