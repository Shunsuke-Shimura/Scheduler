/* Data class
* �\��f�[�^�{�̂�\���N���X
*/
#pragma once

/* �[�i�����Ƃ̗\��f�[�^�N���X */
class Data {
private:
	int id; // ���ʔԍ�
	int type; // �^
	char color; // �F
	char deadline; // �[�i��
	int amount; // ������
	int producible_flag; // �ǂ̃��C���Ő����ł��邩���r�b�g�ŊǗ�
	int choose_line();
public:
	Data(int type, char color, int amount_v, char deadline);
	int schedule();
	int rtn_type() { return type; };
	char rtn_color() { return color; };
	char rtn_deadline() { return deadline; };
	int rtn_amount() { return amount; };
};
