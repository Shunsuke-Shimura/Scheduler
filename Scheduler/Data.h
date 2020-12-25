/* Data class
* �\��f�[�^�{�̂�\���N���X
* �f�X�g���N�^���������̂��߃������������Ɋm�ۂ����
*/
#pragma once
#include "ProductionLine.h"


/* �[�i�����Ƃ̗\��f�[�^�N���X */
class Data {
private:
	int id; // ���ʔԍ�
	int type; // �^
	char color; // �F
	char deadline; // �[�i��
	int amount; // ������
	int producible_flag; // �ǂ̃��C���Ő����ł��邩���r�b�g�ŊǗ�
public:
	Data(int type, char color, int amount_v, char deadline);
	int put_on_calender(ProductionLine* line); // �[���ɊԂɍ���Ȃ����0, �Ԃɍ�����1��Ԃ�
	int rtn_type() { return type; };
	char rtn_color() { return color; };
	char rtn_deadline() { return deadline; };
	int rtn_amount() { return amount; };
};
