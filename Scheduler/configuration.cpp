#include "configuration.h"
#include "UI.h"

namespace Config {
	/*
	* 型番号を受け取って、型の名前を表示する
	* 前後に改行文字は出力しない
	*/
	void print_type(int type) {
		switch (type) {
		case 0:
			printf("ー　　　");
			break;
		case 1:
			printf("雪止め　");
			break;
		case 2:
			printf("万十　　");
			break;
		case 3:
			printf("安定万十");
			break;
		case 4:
			printf("自在万十");
			break;
		case 5:
			printf("紐袖　　");
			break;
		case 6:
			printf("並袖　　");
			break;
		default:
			UI::fatal("型のどれとも一致しません\n");
		}

		return;
	}
	
	/*
	* 色番号を受け取って、型の名前を表示する
	* 前後に改行文字は出力しない
	*/
	void print_color(char color) {
		switch (color) {
		case 0:
			printf("ー　　　　　　　　");
			break;
		case 1:
			printf("新銀　　　　　　　");
			break;
		case 2:
			printf("ブラック　　　　　");
			break;
		case 3:
			printf("プラチナメタリック");
			break;
		case 4:
			printf("ハイシルバー　　　");
			break;
		case 5:
			printf("チョコ　　　　　　");
			break;
		case 6:
			printf("青銅　　　　　　　");
			break;
		case 7:
			printf("青緑　　　　　　　");
			break;
		case 8:
			printf("オレンジ　　　　　");
			break;
		default:
			printf("%d", color);
			UI::fatal("色のどれとも一致しません\n");
		}
		return;
	}
	

}
