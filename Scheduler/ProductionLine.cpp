#include "ProductionLine.h"

// コンストラクタ
ProductionLine::ProductionLine(int type_flag, int m_production) {
	Plan none;
	none.id = -1;
	

	for (int i = 0; i <= 31; i++) {
		calender[i] = none;
	}

	filled_date = 0;
	producible_type = type_flag;
	max_production = m_production;
}



// メソッド
void ProductionLine::get_data(int date, int& type, char& color, int& amount) {
	if (calender[date].id != 0) {
		type = calender[date].type;
		color = calender[date].color;
		amount = calender[date].amount;
	} else {
		type = amount = 0;
		color = 0;
	}
}

int ProductionLine::is_producible(int type_v) {
	return 0;
}
