#include "ProductionLine.h"
#include "configuration.h"

/*
* コンストラクタ
* calender[]を、Plan構造体のidメンバ変数が-1のもので
* 初期化する
*/
ProductionLine::ProductionLine(int ptype, int maxp) {
	Plan none;
	none.id = -1;
	
	// Plan.id が-1のもので初期化する
	// これはその場所に予定が入っていないことを表す
	for (int i = 0; i <= 31; i++) {
		calendar[i] = none;
	}

	filled_date = 0; // 予定が入っていない状態で初期化
	producible_type = ptype;
	max_production = maxp;
}



/*
* dateで渡した日付から、calender[]に入った予定を取り出し
* 出力用引数に型と、色と、数量を代入する
* もしdateの場所の予定が空であればすべてに0を代入する
*/
void ProductionLine::get_data(int date, int& type, char& color, int& amount) {
	if (calendar[date].id != -1) {
		type = calendar[date].type;
		color = calendar[date].color;
		amount = calendar[date].amount;
	} else {
		type = amount = 0;
		color = 0;
	}
}


/*
* 型番号を受け取って、それがそのラインで生産可能かどうかを返す
* 生産可能ならば1、生産不能であれば0を返す
*/
int ProductionLine::is_producible(int type) {
	if (type < 1 || type > MAX_TYPE) return 0;
	if (producible_type & (1 << type)) return 1;
	else return 0;
}


/*
* calenderにDataクラスの予定を追加し、filled_dateをその分増やす
*/
void ProductionLine::put_on_calendar(int id, int type, char color, int amount) {
	int days = (amount + max_production - 1) / max_production;
	for (int i = filled_date + 1; i <= filled_date + days; i++) {
		calendar[i].type = type;
		calendar[i].color = color;
		calendar[i].id = id;
		calendar[i].amount = max_production; // とにかく最大量を生産
	}
	filled_date += days;
}
