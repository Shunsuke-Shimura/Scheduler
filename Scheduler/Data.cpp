#include <algorithm>
#include "Data.h"
// #define DBG_DATA

#ifndef DBG_DATA
#include "ProductionLine.h"
#include "UI.h"
#include "configuration.h"

extern ProductionLine lines[MAX_LINES];
#endif

int Data::sum = 0; // 静的メンバ変数の定義

#ifdef DBG_DATA
#include <iostream>
#endif

/* コンストラクタ
* 型番号、色番号、数量、納品日を受け取ってメンバ変数に代入する
* 静的メンバ変数によってidをつけていく
* producible_flagを設定する
*/
Data::Data(int type_v, char color_v, int amount_v, int deadline_v) {
	id = ++sum;
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
		if (tmp == 1) producible_flag += (1 << i);
	}
}



/*
* producible_flag から最も予定の少ないラインを選んで、
* 予定をそのラインのcalendarに加える
* 正常に予定を追加することができなければFUNC_ERRORを返す
*/
int Data::schedule() {
	int line_num = choose_line();
	if (line_num == FUNC_ERROR) {
		return FUNC_ERROR;
	}
	else {
		lines[line_num].put_on_calendar(id, type, color, amount);
		return 1;
	}
}

/*
* producible_flag から最も予定の少ないラインを選ぶ
* 納品日などの条件に合わない場合はFUNC_ERRORを返す("UI.h")
*/
int Data::choose_line() {
	int min_date = 0;
	int line_num = -1;
	for (int i = 0; i <= MAX_LINES; i++) {
		if (producible_flag & (1 << i)) {
			int date;
			date = (int)lines[i].rtn_date() + (amount / (int)lines[i].rtn_max_production()) + 1;
			if (date < min_date) {
				min_date = date;
				line_num = i;
			}
		}
	}
	if (line_num == -1 || min_date > deadline) return FUNC_ERROR;
	else return line_num;
}

#ifdef DBG_DATA
// デバッグ処理
// ユニットテスト
using namespace std;

int main() {
	Data data_ary[] = { (1, 8, 600, 24), 
						(2, 7, 400, 20), 
						(3, 6, 300, 15), 
						(4, 1, 200, 1),
						(5, 3, 1000, 31)};
	for (int i = 0; i < 5, i++) {
		cout << data_ary[i].rtn_type() << " " << (int)data_ary[i].rtn_color() << " " << (int)data_ary[i].rtn_deadline() << " " << (int)data_ary[i].rtn_amount() << endl;
	}

}
#endif