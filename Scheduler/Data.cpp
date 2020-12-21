#include "Data.h"
extern ProductionLine lines[MAX_LINES];


/* コンストラクタ */

Data::Data(int type_v, char color_v, int amount_v, char deadline_v) {
	id = 1; // とりあえず
	type = type_v;
	color = color_v;
	amount = amount_v;
	deadline = deadline_v;
	producible_flag = 0; // まず0で初期化
	
	for (int i = 0; i < MAX_LINES; i++) {
		int tmp = 0;
		tmp = lines[i].is_producible(type);
		if (tmp != 0) producible_flag += (1 << i);
	}
}

int Data::put_on_calender(ProductionLine* line) {
	return 0;
}