#include "Test.h"
#include <cstdlib>

// コンストラクタ
ProductionLine_Test::ProductionLine_Test(int type_flag, int m_production) {
	return;
}


void ProductionLine_Test::get_data(int date, int& type, char& color, int& amount) {
	type = rand() % 6 + 1;
	color = (char)(rand() % 8 + 1);
	amount = (rand() % 4 + 1) * 100;
}