#include "UI.h"
#include "configuration.h"
#include "Data.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <list>
// #define DEBUG
extern std::list<Data> data_list;

namespace UI {

	// �G���[�o��
	void fatal(std::string msg) {
		std::string error_msg = "�v���I�ȃG���[ : ";
		error_msg += msg;
		printf("\n\n%s", error_msg.c_str());
		printf("�v���O�������I�����܂�...\n");
		exit(-1);
	}


	// print schedule
	void print_schedule(ProductionLine lines[], int n) {
		// �J�����_�[��\��
		// ==================================================================================
		for (int i = 0; i < 100; i++) printf("=");
		printf("\n");

		for (int date = 1; date <= 31; date++) {
			int type, amount;
			char color;

			printf(" %d\t||\t", date);

			// line1
			lines[0].get_data(date, type, color, amount);
			printf("line1:\t");
			Config::print_type(type);
			printf("/");
			Config::print_color(color);
			printf("/%d��\t\t\t", amount);

			// line2
			lines[1].get_data(date, type, color, amount);
			printf("line2:\t");
			Config::print_type(type);
			printf("/");
			Config::print_color(color);
			printf("/%d��", amount);

			printf("\n\t||\t");

			// line3
			lines[2].get_data(date, type, color, amount);
			printf("line3:\t");
			Config::print_type(type);
			printf("/");
			Config::print_color(color);
			printf("/%d��\t\t\t", amount);

			// line4
			lines[3].get_data(date, type, color, amount);
			printf("line4:\t");
			Config::print_type(type);
			printf("/");
			Config::print_color(color);
			printf("/%d��", amount);
			printf("\n\n");
		}

		// ==================================================================================
		for (int i = 0; i < 100; i++) printf("=");
		printf("\n");
	}

	// make template : �\�����͂��邽�߂̃e�L�X�g�t�@�C���̃e���v���[�g������
	void make_template() {
		std::ofstream fout("schedule.txt", std::ios::trunc);
		if (!fout) fatal("�e���v���[�g�t�@�C�����J���܂���ł����B\n");
		else {
			fout << "# ����͗\��𕡐������ɓ��͂��邽�߂̃e���v���[�g�t�@�C���ł��B�e���v���[�g�������̎��̍s����A�P�s�ɗ\���������͂��Ă��������B\n";
			fout << "# \"�E#�Ȃǂ̋L���͓��͂��Ȃ��ł��������B\n";
			fout << "# �\��̓��͎͂��̃t�H�[�}�b�g�ɏ]���Ă��������B�܂��A�K�����p������p���Ă��������B\n";
			fout << "# \"<�^(���p����)> <�F(���p����)> <�[�i��> <�[�i�̓��t>\"\n";
			fout << "# �܂��A�^���A�F�ɂ��Ă͈ȉ��̔ԍ��œ��͂��Ă��������B\n";
			fout << "# �E��~�� : 1�@�@�@,�V��				: 1";
			fout << "# �E���\	: 2�@�@�@,�u���b�N			: 2";
			fout << "# �E���薜�\ : 3�@�@,�v���`�i���^���b�N: 3";
			fout << "# �E���ݖ��\ : 4�@�@,�n�C�V���o�[		: 4";
			fout << "# �E�R�� : 5�@�@�@�@,�`���R			: 5";
			fout << "# �E���� : 6�@�@�@�@,��				: 6";
			fout << "#				   �@,��				: 7";
			fout << "#  			   �@, �I�����W			: 8";
			printf("�e���v���[�g�t�@�C�����쐬���܂����B�t�@�C������\"schedule.txt\"�ł��B\n");
		}
	}

	// set schedule : �e���v���[�g�t�@�C������\��𕡐��܂Ƃ߂ē��͂���
	void set_schedule() {
		std::ifstream reading_file("schedule.txt", std::ios::in);;
		if (!reading_file) {
			printf("�t�@�C�������݂��Ȃ��A�������͊J���܂���ł����B\n");
			printf("\"make template\"�R�}���h��p���ăe���v���[�g�t�@�C�����쐬���Ă��������B\n");
		}
		else {
			std::string reading_file_buffer;
			printf("\"schedule.txt\"��ǂݍ���ł��܂�...\n");
			while (!reading_file.eof()) {
				int type_v, amount_v, color_tmp, deadline_tmp;
				char color_v, deadline_v;
				// getline�œ���
			}
			printf("�e���v���[�g�t�@�C������\������ׂēǂݍ��݂܂����B\n");
		}
	}

	// clear schedule : �\������ׂč폜����
	void clear_schedule() {
		std::string confirm;
		std::cout << "�{���ɒǉ������\������ׂč폜���܂����H" << std::endl;
		while (true) {
			std::cout << "Yes / No >>> ";
			std::cin >> confirm;
			if (confirm == "Yes" || confirm == "yes") {
				data_list.clear();
				std::cout << "�\������ׂč폜���܂����B\n";
				break;
			}
			else if (confirm == "No" || confirm == "no") {
				break;
			}
			else {
				std::cout << "���͂�����������܂���\n";
			}
		}
	}

	// list schedule : �\��̃��X�g��ԍ��t���ŕ\��
	void list_schedule() {

		int num = 1; // �v�f�ԍ�
		for (std::list<Data>::iterator it = data_list.begin(); it != data_list.end(); it++) {
			printf("%d :\t", num++);
			Config::print_type((*it).rtn_type());
			printf("\t");
			Config::print_color((*it).rtn_color());
			printf("\t%d (��)\t�[�i�� / %d(��)\n", (*it).rtn_amount(), (int)(*it).rtn_deadline());
		}
		printf("���͂��ꂽ�\��͈ȏ�ł��B\n");
	}

	// // add schedule : �\�������X�g�ɉ�����
	void add_schedule() {
		int type_v, amount_v, color_tmp, deadline_tmp;
		char color_v, deadline_v;
		// ����
		std::cin.exceptions(std::ios::failbit); // cin �̗�O������L����
		while (true) {
			try {
				printf("�^�ԍ���I�����ē��͂��Ă��������B(�\��̒ǉ����L�����Z������ɂ�0����͂��Ă��������B)\n");
				printf("��~��	: 1\n");
				printf("���\	: 2\n");
				printf("���薜�\: 3\n");
				printf("���ݖ��\: 4\n");
				printf("�R��	: 5\n");
				printf("����	: 6\n");
				printf(">>> ");
				std::cin >> type_v;
				if (type_v == 0) {
					printf("���͂��L�����Z�����܂����B\n");
					return;
				}
				else if (type_v < 0 || type_v > 6) {
					throw -1;
				}
			}
			catch (...) {
				printf("�s�K�؂ȓ��͂ł��B������x���͂��Ă��������B\n");
				continue;
			}
			break;
		}

		// �G���[�t���O��������
		std::cin.clear();
		std::cin.seekg(0);
		while (true) {
			try {
				color_tmp = -1;
				printf("�F�ԍ���I�����ē��͂��Ă��������B(�\��̒ǉ����L�����Z������ɂ�0����͂��Ă��������B)\n");
				printf("�V��@�@�@�@�@�@�@: 1\n");
				printf("�u���b�N�@�@�@�@�@: 2\n");
				printf("�v���`�i���^���b�N: 3\n");
				printf("�n�C�V���o�[�@�@�@: 4\n");
				printf("�`���R			�@: 5\n");
				printf("��			�@: 6\n");
				printf("��			�@: 7\n");
				printf("�I�����W		�@: 8\n");
				printf(">>> ");
				std::cin >> color_tmp;
				if (color_tmp == 0) {
					printf("���͂��L�����Z�����܂����B\n");
					return;
				}
				else if (color_tmp < 1 || color_tmp > 8) {
					throw -1;
				}
			}
			catch (...) {
				printf("�s�K�؂ȓ��͂ł��B������x���͂��Ă��������B\n");
				continue;
			}
			color_v = (char)color_tmp;
			break;
		}

		// �G���[�t���O��������
		std::cin.clear();
		std::cin.seekg(0);
		while (true) {
			try {
				amount_v = -1;
				printf("�K�v�Ȑ��ʂ���͂��Ă��������B(�\��̒ǉ����L�����Z������ɂ�0����͂��Ă��������B)\n");
				printf(">>> ");
				std::cin >> amount_v;
				if (amount_v == 0) {
					printf("���͂��L�����Z�����܂����B\n");
					return;
				}
				else if (amount_v < 1) {
					throw - 1;
				}
			}
			catch (...) {
				printf("�s�K�؂ȓ��͂ł��B������x���͂��Ă��������B\n");
				continue;
			}
			break;
		}
		// �G���[�t���O��������
		std::cin.clear();
		std::cin.seekg(0);
		while (true) {
			try {
				deadline_tmp = -1;
				printf("�[�i�̓��t����͂��Ă��������B(�\��̒ǉ����L�����Z������ɂ�0����͂��Ă��������B)\n");
				printf(">>> ");
				std::cin >> deadline_tmp;
				if (deadline_tmp == 0) {
					printf("���͂��L�����Z�����܂����B\n");
					return;
				}
				else if (deadline_tmp < 1 || deadline_tmp > 31) {
					throw - 1;
				}
			}
			catch (...) {
				printf("�s�K�؂ȓ��͂ł��B������x���͂��Ă��������B\n");
				continue;
			}
			deadline_v = (char)deadline_tmp;
			break;
		}
		add_plans(type_v, color_v, amount_v, deadline_v);
		printf("�\���ǉ����܂����B\n");
	}

	void add_plans(int type_v, char color_v, int amount_v, char deadline_v) {
		Data plan(type_v, color_v, amount_v, deadline_v);
		data_list.push_back(plan);
	}
	

	// // delete schedule : ���X�g�̔ԍ��ɂ���ė\�����폜
	void delete_schedule(int dlt_num) {

	}

	// help : �w���v��\��
	void print_help(int help_num) {

	}
}

#ifdef DEBUG
// �e�X�g�p
void print_schedule(ProductionLine_Test lines[], int n) { // n�͗v�f��
	if (n != 4) UI::fatal("�z��̗v�f�����z��O�ł�\n");
	// �J�����_�[��\��
	// ==================================================================================
	for (int i = 0; i < 100; i++) printf("=");
	printf("\n");

	for (int date = 1; date <= 31; date++) {
		int type, amount;
		char color;

		printf(" %d\t||\t", date);

		// line1
		lines[0].get_data(date, type, color, amount);
		printf("line1:\t");
		Config::print_type(type);
		printf("/");
		Config::print_color(color);
		printf("/%d��\t\t\t", amount);

		// line2
		lines[1].get_data(date, type, color, amount);
		printf("line2:\t");
		Config::print_type(type);
		printf("/");
		Config::print_color(color);
		printf("/%d��", amount);

		printf("\n\t||\t");
		


		// line3
		lines[2].get_data(date, type, color, amount);
		printf("line3:\t");
		Config::print_type(type);
		printf("/");
		Config::print_color(color);
		printf("/%d��\t\t\t", amount);

		// line4
		lines[3].get_data(date, type, color, amount);
		printf("line4:\t");
		Config::print_type(type);
		printf("/");
		Config::print_color(color);
		printf("/%d��", amount);
		printf("\n\n");
	}

	// ==================================================================================
	for (int i = 0; i < 100; i++) printf("=");
	printf("\n");
}


#endif

