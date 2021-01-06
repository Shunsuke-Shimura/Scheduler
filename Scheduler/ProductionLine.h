/* ProductionLine class
* 生産ラインを表すクラス
*/
#pragma once

// include guard
#ifndef INCLUDED_PRODUCTIONLINE
#define INCLUDED_PRODUCTIONLINE

typedef struct Plan {
	int id, type, amount; // id が-1なら空を示す
	char color;
} Plan;

#endif
const int MAX_LINES = 4; // 製造ライン数
const int CALENDAR_NIL_ID = -1;


class ProductionLine {
private:
	int producible_type_flag; // どの種類を製造できるか(ビット)
	int max_production; // 最大何個製造できるか
	Plan calendar[32]; // 配列の添え字が日付に対応（１スタート）
	char filled_date; // 何日まで予定が埋まっているか
public:
	ProductionLine(int producible_type, int max_production);
	void init(); // ラインに組み込まれた予定をクリア
	void put_on_calendar(int, int, char, int);
	char rtn_date() { return filled_date; };
	int rtn_max_production() { return max_production; };
	void get_data(int date, int& type, char& color, int& amount);
	int is_producible(int);
};

