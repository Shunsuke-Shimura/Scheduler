#include "Data.h"
extern ProductionLine lines[MAX_LINES];


/* コンストラクタ
* 型番号、色番号、数量、納品日を受け取ってメンバ変数に代入する
* producible_flagを設定する
*/
Data::Data(int type_v, char color_v, int amount_v, char deadline_v) {
	id = 1; // 製作途中のためとりあえずの値として1を代入している
	type = type_v;
	color = color_v;
	amount = amount_v;
	deadline = deadline_v;
	// producible_flagの右からi番目のフラグは、"Scheduler.cpp"で宣言した生産ラインの配列
	// "lines"の添え字に対応しており、そのラインで予定の型が生産可能かどうかを示す
	producible_flag = 0; // まず0で初期化
	
	// producible_flagを設定
	for (int i = 0; i < MAX_LINES; i++) {
		int tmp = 0;
		tmp = lines[i].is_producible(type);
		if (tmp != 0) producible_flag += (1 << i);
	}
}

/*
* 
*/
int Data::put_on_calender(ProductionLine* line) {
	return 0;
}