# c-project
構造体

	struct Othello {

	int stone[8][8];
	
	int stonelevel[8][8]；
	
	int endFlag;
	
	int turn; // 手番・・・先手黒
	
	int coolTimer;
	
	int tmpblack, tmpwhite;
	
	int winjudge;
	
	int count_stone;		//反転する石の個数
	
	};

	Othello data;

ファイル入出力

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

		//txtファイルに表示

		fprintf(fp, "黒石 : %d\n", data.tmpblack);

		fprintf(fp, "白石 : %d\n", data.tmpwhite);

		if (data.tmpblack > data.tmpwhite) {

			fputs("黒の勝ち!!!", fp);

		}

		else if (data.tmpblack < data.tmpwhite) {

			fputs("白の勝ち!!!", fp);

		}

		fclose(fp);

	}
	
	}
	
iniファイル
