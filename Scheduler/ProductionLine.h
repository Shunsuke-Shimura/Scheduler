/* ProductionLine class
* ���Y���C����\���N���X
*/
#pragma once

// include guard
#ifndef INCLUDED_PRODUCTIONLINE
#define INCLUDED_PRODUCTIONLINE
typedef struct Plan {
	int id, type, amount; // id ��-1�Ȃ�������
	char color;
} Plan;

#define MAX_LINES 4

#endif


class ProductionLine {
private:
	int producible_type; // �ǂ̎�ނ𐻑��ł��邩(�r�b�g)
	int max_production; // �ő剽�����ł��邩
	Plan calender[32]; // �z��̓Y���������t�ɑΉ��i�P�X�^�[�g�j
	char filled_date; // �����܂ŗ\�肪���܂��Ă��邩
public:
	ProductionLine(int producible_type, int max_production);
	char rtn_date() { return filled_date; };
	int is_producible(int type_flag);
	void get_data(int date, int& type, char& color, int& amount);
};

