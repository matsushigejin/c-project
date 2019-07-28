# c-project
構造体
struct Othello {
	// グローバル変数
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
