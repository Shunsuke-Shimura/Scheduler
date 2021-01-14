#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include "UI.h"
#include "configuration.h"
#include "Data.h"

// #define DEBUG
extern std::vector<Data> data_list;
extern ProductionLine lines[MAX_LINES];

namespace UI {

	/* 
	* ���̂܂܃v���O�����𑱍s�ł��Ȃ��v���I�ȃG���[����������
	* msg�������Ƃ��āA"�v���I�ȃG���[�F"�Ƃ�����^���̌��msg���o�͂���
	* �S�̂̃v���O�������ُ�I������B
	*/
	void fatal(std::string msg) {
		std::string error_msg = "�v���I�ȃG���[ : ";
		error_msg += msg;
		printf("\n\n%s", error_msg.c_str());
		printf("�v���O�������I�����܂�...\n");
		exit(-1);
	}


	/* 
	* ���X�g����t���Ƀ\�[�g���Ă��琶�Y���C����calendar�ɑg�ݍ���ŁA
	* �X�P�W���[�����J�����_�[�`���ŕ\������
	* ���Y���C���̐��� n �Ƃ��Ĉ����ɓn��
	*/
	void print_schedule(ProductionLine lines[], int n) {
		// ���X�g����t���Ƀ\�[�g
		sort_data_list();

		// lines[]�̏�����
		init_lines();

		// ���X�g�������\������C����calendar�ɑg�ݍ���ł���
		for (std::vector<Data>::iterator it = data_list.begin(); it != data_list.end(); it++) (*it).schedule();

		if (n != 4) {
			fatal("print_schedule�֐����Ń��C���̐�����v���܂���B");
		}

		// �J�����_�[��\��
		// ==================================================================================
		for (int i = 0; i < 100; i++) printf("=");
		printf("\n");

		for (int date = 1; date <= 31; date++) {
			int type, amount;
			char color;

			printf(" %d\t||\t", date);

			// LINE0
			lines[0].get_data(date, type, color, amount);
			printf("line1:\t");
			Config::print_type(type);
			printf("/");
			Config::print_color(color);
			printf("/%d��\t\t\t", amount);

			// LINE1
			lines[1].get_data(date, type, color, amount);
			printf("line2:\t");
			Config::print_type(type);
			printf("/");
			Config::print_color(color);
			printf("/%d��", amount);

			printf("\n\t||\t");

			// LINE2
			lines[2].get_data(date, type, color, amount);
			printf("line3:\t");
			Config::print_type(type);
			printf("/");
			Config::print_color(color);
			printf("/%d��\t\t\t", amount);

			// LINE3
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


	/*
	* lines[]��calendar, filled_days������������
	*/
	void init_lines() {
		for (int i = 0; i < MAX_LINES; i++) {
			lines[i].init();
		}
	}

	/*
	* data_list����t���Ƀ\�[�g����i�}���\�[�g�j
	*/
	void sort_data_list() {
		for (int i = 1; i < data_list.size(); i++) {
			Data tmp = data_list[i];
			int j = i - 1;
			while (j >= 0 && data_list[j].rtn_deadline() > tmp.rtn_deadline()) {
				data_list[j + 1] = data_list[j];
				j--;
			}
			data_list[j + 1] = tmp;
		}
	}
	

	/* 
	* �\�����͂��邽�߂̃e�L�X�g�t�@�C���̃e���v���[�g������
	* �e�L�X�g�t�@�C���̃e���v���[�g�ɂ́A�\�����͂��邽�߂̌`��������
	*/
	void make_template() {
		std::ofstream fout("template.txt", std::ios::trunc);
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

	/*
	* data_list�̓��e��"template.txt"�ɋL�^����
	*/
	void record_in_template() {

	}

	/*
	* �e���v���[�g�t�@�C������\��𕡐��܂Ƃ߂Ď󂯎��
	* ************************ ������ ******************
	*/
	void set_schedule() {
		std::ifstream reading_file("schedule.txt", std::ios::in);
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
				std::getline(reading_file, reading_file_buffer);
				

			}
			printf("�e���v���[�g�t�@�C������\������ׂēǂݍ��݂܂����B\n");
		}
	}

	

	/*
	* "clear"�R�}���h�̏���������
	* �{���ɗ\����폜���邩���m�F���Ă���\������ׂč폜����
	*/
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

	/*
	* "list"�R�}���h�̏���������
	* �\��̃��X�g����t���ɑ}���\�[�g������ɁA���̃��X�g��ԍ��t���ŕ\������
	*/
	void list_schedule() {
		int size = data_list.size();
		if (size == 0) {
			std::cout << "�ǉ�����Ă���\��͂���܂���\n";
			return;
		}
		else {
			// ���t�ɂ��\�[�g����
			sort_data_list();
			
			// ��������\��
			int num = 1; // �v�f�ԍ�
			for (std::vector<Data>::iterator it = data_list.begin(); it != data_list.end(); it++) {
				printf("%d :\t", num++);
				Config::print_type((*it).rtn_type());
				printf("\t");
				Config::print_color((*it).rtn_color());
				printf("\t%d (��)\t�[�i�� / %d(��)\n", (*it).rtn_amount(), (int)(*it).rtn_deadline());
			}
			printf("���͂��ꂽ�\��͈ȏ�ł��B\n");
		}
	}

	/*
	* "add"�R�}���h�̏���������
	* �^��F�Ȃǂ𐔎��̓��͂ɂ���đI�����ė\����ЂƂ��X�g�ɉ�����
	*/
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

	/*
	* ���ۂ�Data�N���X�̃C���X�^���X���쐬������ɁA
	* �\��̃��X�g�ɒǉ�����
	*/
	void add_plans(int type_v, char color_v, int amount_v, char deadline_v) {
		Data plan(type_v, color_v, amount_v, deadline_v);
		data_list.push_back(plan);
	}
	
	/*
	* "delete"�R�}���h�̏���������
	* "list"�R�}���h�ŉ��Ɏ������\��ԍ�����\����ЂƂI��ō폜����
	*/
	void delete_schedule() {
		int del_num;
		
		std::cin.exceptions(std::ios::failbit); // cin �̗�O������L����
		while (true) {
			try {
				std::cout << "���Ԗڂ̗\����폜���܂���?�i�������L�����Z������ɂ�0����͂��Ă�������\n";
				std::cout << std::endl;
				std::cin >> del_num;
				if (del_num == 0) {
					printf("�R�}���h�������L�����Z�����܂����B\n");
					return;
				}
				else if (del_num < 0 || del_num > data_list.size()) {
					throw - 1;
				}
			}
			catch (...) {
				printf("�s�K�؂ȓ��͂ł��B������x���͂��Ă��������B\n");
				continue;
			}
			break;
		}
		delete_data(del_num);
	}

	/*
	* ���ۂɗ\��̃��X�g����del_num�Ԗڂ̂��̂��폜����
	*/
	void delete_data(int del_num) {
		data_list.erase(data_list.begin() + (del_num - 1));
		std::cout << del_num << "�Ԗڂ̗\����폜���܂����B\n";
	}

	/*
	* "help"�R�}���h�̏���������
	* �e�R�}���h��ԍ��ŕ\���A����help_num�̔ԍ��ɂ����
	* ���̃R�}���h�̎g�p�@��\������
	*/
	void print_help() {
		std::cout << "< �e�R�}���h�̓��� >\n";
		std::cout << "\"print\" : �o�^�����\����J�����_�[�`���ŕ\��\n";
		std::cout << "\"list\" : �o�^�����\����m�F����\n";
		std::cout << "\"delete\" : list�R�}���h�ŕ\�������\��ɑ΂��āA\n";
			std::cout << "\t\t�w�肵���ԍ��̗\����폜����\n";
		std::cout << "\"add\" : �\���ǉ�����\n";
		std::cout << "\"make template\" : �\��𕡐������ɓo�^���邽�߂�\n";
			std::cout << "\t\t�e���v���[�g�t�@�C�����쐬����\n";
		std::cout << "\"set\" : �e���v���[�g�t�@�C������\���o�^����\n";
		std::cout << "\"clear\" : �o�^�����\������ׂč폜����\n";
		std::cout << "\"quit\" : ���̃v���O�������I������\n";
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

