#include "ProductionLine.h"

/*
* �R���X�g���N�^
* calender[]���APlan�\���̂�id�����o�ϐ���-1�̂��̂�
* ����������
*/
ProductionLine::ProductionLine(int type_flag, int m_production) {
	Plan none;
	none.id = -1;
	
	// Plan.id ��-1�̂��̂ŏ���������
	// ����͂��̏ꏊ�ɗ\�肪�����Ă��Ȃ����Ƃ�\��
	for (int i = 0; i <= 31; i++) {
		calender[i] = none;
	}

	filled_date = 0;
	producible_type = type_flag;
	max_production = m_production;
}



/*
* date�œn�������t����Acalender[]�ɓ������\������o��
* �o�͗p�����Ɍ^�ƁA�F�ƁA���ʂ�������
* ����date�̏ꏊ�̗\�肪��ł���΂��ׂĂ�0��������
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
* �^�ԍ����󂯎���āA���ꂪ���̃��C���Ő��Y�\���ǂ�����Ԃ�
* ���Y�\�Ȃ�Δ�0�A���Y�s�\�ł����0��Ԃ�
*/
int ProductionLine::is_producible(int type_v) {
	return 0;
}
