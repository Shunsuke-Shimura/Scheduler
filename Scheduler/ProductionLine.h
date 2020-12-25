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

#define MAX_LINES 4

#endif


class ProductionLine {
private:
	int producible_type; // どの種類を製造できるか(ビット)
	int max_production; // 最大何個製造できるか
	Plan calender[32]; // 配列の添え字が日付に対応（１スタート）
	char filled_date; // 何日まで予定が埋まっているか
public:
	ProductionLine(int producible_type, int max_production);
	char rtn_date() { return filled_date; };
	int is_producible(int type_flag);
	void get_data(int date, int& type, char& color, int& amount);
};

