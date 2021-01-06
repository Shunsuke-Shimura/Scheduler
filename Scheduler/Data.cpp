#include <algorithm>
#include "Data.h"
// #define DBG_DATA

#ifndef DBG_DATA
#include "ProductionLine.h"
#include "UI.h"
#include "configuration.h"

extern ProductionLine lines[MAX_LINES];
#endif

int Data::sum = 0; // �ÓI�����o�ϐ��̒�`

#ifdef DBG_DATA
#include <iostream>
#endif

/* �R���X�g���N�^
* �^�ԍ��A�F�ԍ��A���ʁA�[�i�����󂯎���ă����o�ϐ��ɑ������
* �ÓI�����o�ϐ��ɂ����id�����Ă���
* producible_flag��ݒ肷��
*/
Data::Data(int type_v, char color_v, int amount_v, int deadline_v) {
	id = ++sum;
	type = type_v;
	color = color_v;
	amount = amount_v;
	deadline = deadline_v;
	// producible_flag�̉E����i�Ԗڂ̃t���O�́A"Scheduler.cpp"�Ő錾�������Y���C���̔z��
	// "lines"�̓Y�����ɑΉ����Ă���A���̃��C���ŗ\��̌^�����Y�\���ǂ���������
	producible_flag = 0; // �܂�0�ŏ�����
	
	// producible_flag��ݒ�
	for (int i = 0; i < MAX_LINES; i++) {
		int tmp = 0;
		tmp = lines[i].is_producible(type);
		if (tmp == 1) producible_flag += (1 << i);
	}
}



/*
* producible_flag ����ł��\��̏��Ȃ����C����I��ŁA
* �\������̃��C����calendar�ɉ�����
* ����ɗ\���ǉ����邱�Ƃ��ł��Ȃ����FUNC_ERROR��Ԃ�
*/
int Data::schedule() {
	int line_num = choose_line();
	if (line_num == FUNC_ERROR) {
		return FUNC_ERROR;
	}
	else {
		lines[line_num].put_on_calendar(id, type, color, amount);
		return 1;
	}
}

/*
* producible_flag ����ł��\��̏��Ȃ����C����I��
* �[�i���Ȃǂ̏����ɍ���Ȃ��ꍇ��FUNC_ERROR��Ԃ�("UI.h")
*/
int Data::choose_line() {
	int min_date = 0;
	int line_num = -1;
	for (int i = 0; i <= MAX_LINES; i++) {
		if (producible_flag & (1 << i)) {
			int date;
			date = (int)lines[i].rtn_date() + (amount / (int)lines[i].rtn_max_production()) + 1;
			if (date < min_date) {
				min_date = date;
				line_num = i;
			}
		}
	}
	if (line_num == -1 || min_date > deadline) return FUNC_ERROR;
	else return line_num;
}

#ifdef DBG_DATA
// �f�o�b�O����
// ���j�b�g�e�X�g
using namespace std;

int main() {
	Data data_ary[] = { (1, 8, 600, 24), 
						(2, 7, 400, 20), 
						(3, 6, 300, 15), 
						(4, 1, 200, 1),
						(5, 3, 1000, 31)};
	for (int i = 0; i < 5, i++) {
		cout << data_ary[i].rtn_type() << " " << (int)data_ary[i].rtn_color() << " " << (int)data_ary[i].rtn_deadline() << " " << (int)data_ary[i].rtn_amount() << endl;
	}

}
#endif