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

#endif
const int MAX_LINES = 4; // �������C����
const int CALENDAR_NIL_ID = -1;


class ProductionLine {
private:
	int producible_type_flag; // �ǂ̎�ނ𐻑��ł��邩(�r�b�g)
	int max_production; // �ő剽�����ł��邩
	Plan calendar[32]; // �z��̓Y���������t�ɑΉ��i�P�X�^�[�g�j
	char filled_date; // �����܂ŗ\�肪���܂��Ă��邩
public:
	ProductionLine(int producible_type, int max_production);
	void init(); // ���C���ɑg�ݍ��܂ꂽ�\����N���A
	void put_on_calendar(int, int, char, int);
	char rtn_date() { return filled_date; };
	int rtn_max_production() { return max_production; };
	void get_data(int date, int& type, char& color, int& amount);
	int is_producible(int);
};

