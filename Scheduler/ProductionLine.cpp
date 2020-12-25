#include "ProductionLine.h"

/*
* コンストラクタ
* calender[]を、Plan構造体のidメンバ変数が-1のもので
* 初期化する
*/
ProductionLine::ProductionLine(int type_flag, int m_production) {
	Plan none;
	none.id = -1;
	
	// Plan.id が-1のもので初期化する
	// これはその場所に予定が入っていないことを表す
	for (int i = 0; i <= 31; i++) {
		calender[i] = none;
	}

	filled_date = 0;
	producible_type = type_flag;
	max_production = m_production;
}



/*
* dateで渡した日付から、calender[]に入った予定を取り出し
* 出力用引数に型と、色と、数量を代入する
* もしdateの場所の予定が空であればすべてに0を代入する
*/
void ProductionLine::get_data(int date, int& type, char& color, int& amount) {
	if (calender[date].id != -1) {
		type = calender[date].type;
		color = calender[date].color;
		amount = calender[date].amount;
	} else {
		type = amount = 0;
		color = 0;
	}
}

/*
* 型番号を受け取って、それがそのラインで生産可能かどうかを返す
* 生産可能ならば非0、生産不能であれば0を返す
*/
int ProductionLine::is_producible(int type_v) {
	return 0;
}
