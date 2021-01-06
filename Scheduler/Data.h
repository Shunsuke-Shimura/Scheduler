/* Data class
* 予定データ本体を表すクラス
*/
#pragma once

/* 納品物ごとの予定データクラス */
class Data {
private:
	int id; // 識別番号
	int type; // 型
	char color; // 色
	int deadline; // 納品日
	int amount; // 注文個数
	int producible_flag; // どのラインで製造できるかをビットで管理
	static int sum; // id管理用として
	int choose_line();
public:
	Data(int type, char color, int amount_v, int deadline);
	int schedule();
	int rtn_type() { return type; };
	char rtn_color() { return color; };
	int rtn_deadline() { return deadline; };
	int rtn_amount() { return amount; };
};

int Data::sum = 0;