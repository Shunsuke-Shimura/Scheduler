#include "ProductionLine.h"
#include "configuration.h"

/*
* �R���X�g���N�^
* calender[]���APlan�\���̂�id�����o�ϐ���-1�̂��̂�
* ����������
*/
ProductionLine::ProductionLine(int ptype, int maxp) {
	Plan none;
	none.id = -1;
	
	// Plan.id ��-1�̂��̂ŏ���������
	// ����͂��̏ꏊ�ɗ\�肪�����Ă��Ȃ����Ƃ�\��
	for (int i = 0; i <= 31; i++) {
		calendar[i] = none;
	}

	filled_date = 0; // �\�肪�����Ă��Ȃ���Ԃŏ�����
	producible_type = ptype;
	max_production = maxp;
}



/*
* date�œn�������t����Acalender[]�ɓ������\������o��
* �o�͗p�����Ɍ^�ƁA�F�ƁA���ʂ�������
* ����date�̏ꏊ�̗\�肪��ł���΂��ׂĂ�0��������
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
* �^�ԍ����󂯎���āA���ꂪ���̃��C���Ő��Y�\���ǂ�����Ԃ�
* ���Y�\�Ȃ��1�A���Y�s�\�ł����0��Ԃ�
*/
int ProductionLine::is_producible(int type) {
	if (type < 1 || type > MAX_TYPE) return 0;
	if (producible_type & (1 << type)) return 1;
	else return 0;
}


/*
* calender��Data�N���X�̗\���ǉ����Afilled_date�����̕����₷
*/
void ProductionLine::put_on_calendar(int id, int type, char color, int amount) {
	int days = (amount + max_production - 1) / max_production;
	for (int i = filled_date + 1; i <= filled_date + days; i++) {
		calendar[i].type = type;
		calendar[i].color = color;
		calendar[i].id = id;
		calendar[i].amount = max_production; // �Ƃɂ����ő�ʂ𐶎Y
	}
	filled_date += days;
}
