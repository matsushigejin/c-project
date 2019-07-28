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
入力

	100 -40 20 5 5 20 -40 100
	-40 -80 -1 -1 -1 -1 -80 -40
	20 -1 5 1 1 5 -1 20
	5 -1 1 0 0 1 -1 5
	5 -1 1 0 0 1 -1 5
	20 -1 5 1 1 5 -1 20
	-40 -80 -1 -1 -1 -1 -80 -40
	100 -40 20 5 5 20 -40 100
	
出力

	

	
