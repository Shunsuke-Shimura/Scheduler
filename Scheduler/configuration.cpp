#include "configuration.h"
#include "UI.h"

namespace Config {
	/*
	* �^�ԍ����󂯎���āA�^�̖��O��\������
	* �O��ɉ��s�����͏o�͂��Ȃ�
	*/
	void print_type(int type) {
		switch (type) {
		case 0:
			printf("�[�@�@�@");
			break;
		case 1:
			printf("��~�߁@");
			break;
		case 2:
			printf("���\�@�@");
			break;
		case 3:
			printf("���薜�\");
			break;
		case 4:
			printf("���ݖ��\");
			break;
		case 5:
			printf("�R���@�@");
			break;
		case 6:
			printf("�����@�@");
			break;
		default:
			UI::fatal("�^�̂ǂ�Ƃ���v���܂���\n");
		}

		return;
	}
	
	/*
	* �F�ԍ����󂯎���āA�^�̖��O��\������
	* �O��ɉ��s�����͏o�͂��Ȃ�
	*/
	void print_color(char color) {
		switch (color) {
		case 0:
			printf("�[�@�@�@�@�@�@�@�@");
			break;
		case 1:
			printf("�V��@�@�@�@�@�@�@");
			break;
		case 2:
			printf("�u���b�N�@�@�@�@�@");
			break;
		case 3:
			printf("�v���`�i���^���b�N");
			break;
		case 4:
			printf("�n�C�V���o�[�@�@�@");
			break;
		case 5:
			printf("�`���R�@�@�@�@�@�@");
			break;
		case 6:
			printf("���@�@�@�@�@�@�@");
			break;
		case 7:
			printf("�΁@�@�@�@�@�@�@");
			break;
		case 8:
			printf("�I�����W�@�@�@�@�@");
			break;
		default:
			printf("%d", color);
			UI::fatal("�F�̂ǂ�Ƃ���v���܂���\n");
		}
		return;
	}
	

}
