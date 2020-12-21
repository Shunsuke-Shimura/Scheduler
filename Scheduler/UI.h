/*
************** ���[�U�[�C���^�[�t�F�[�X *************
* ���[�U�[�C���^�[�t�F�[�X�Ɋւ���֐���e�R�}���h�̏������܂Ƃ߂�����
* �G���[�����֐�fatal��std::string�̃��b�Z�[�W�������Ƃ��āA�G���[���̌�ɂ��̃��b�Z�[�W��\�����ăv���O�������I������B
*
*/
#pragma once
#include <string>
#include "ProductionLine.h"
#include "test.h"
#define DEBUG


namespace UI {
	void fatal(std::string msg); // �v���I�ȃG���[�����֐��Astd::string�̃��b�Z�[�W�������Ƃ��āA�G���[���̌�ɂ��̃��b�Z�[�W��\�����Ă��ׂẴv���O�������I������B
	void print_schedule(ProductionLine lines[], int n);
	void make_template();
	void set_schedule(); // �����̗\����e���v���[�g�t�@�C������܂Ƃ߂ē���
	void clear_schedule();
	void list_schedule();
	void add_schedule();
	void add_plans(int type_v, char color_v, int amount_v, char deadline_v);
	void delete_schedule(int); // �n���ꂽ�ԍ��̗\����폜
	void print_help(int); // �n���ꂽ�R�}���h�̃w���v��\��

}

#ifdef DEBUG
void print_schedule(ProductionLine_Test[], int n);
#endif