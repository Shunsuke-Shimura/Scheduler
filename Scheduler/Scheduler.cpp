/*
*********************メインソースコード ********************** 
* メイン関数や各種大域変数宣言を行っている。
* 他ファイルで大域変数を用いるにはexternコマンドを用いる
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
// #define DEBUG

#ifndef DEBUG
#include "Data.h"
#include "ProductionLine.h"
#include "Test.h"
#include "UI.h"
#include "configuration.h"
#endif


/* 各ラインで生産できる種類（数字と種類の対応はconfiguration.h） */
static const int LINE0_TYPES = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4); // 雪止めと万十
static const int LINE1_TYPES = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4); // 雪止めと万十
static const int LINE2_TYPES = (1 << 5) + (1 << 6); // 袖
static const int LINE3_TYPES = (1 << 5) + (1 << 6); // 袖
static const int LINE0_MAXPRODUCTION = 3100;
static const int LINE1_MAXPRODUCTION = 3100;
static const int LINE2_MAXPRODUCTION = 2100;
static const int LINE3_MAXPRODUCTION = 2100;


/* 大域変数宣言 */
// linesという配列として生産ライン自体を管理する
// MAX_LINESは生産ラインの数で、"ProductionLine.h"フォルダに
// マクロとして定義される
ProductionLine lines[MAX_LINES] = { ProductionLine(LINE0_TYPES, LINE0_MAXPRODUCTION), ProductionLine(LINE1_TYPES, LINE1_MAXPRODUCTION),  ProductionLine(LINE2_TYPES, LINE2_MAXPRODUCTION),  ProductionLine(LINE3_TYPES, LINE3_MAXPRODUCTION) };

// data_listは追加された予定を保持する
std::vector<Data> data_list;

// テスト用ProductionLine
ProductionLine_Test lines_t[4] = { ProductionLine_Test(1023, 200), ProductionLine_Test(1023, 300), ProductionLine_Test(1023, 100), ProductionLine_Test(1023, 100) };


/*
* メイン関数
*/
int main() {
	std::string com;


	printf("*****    起動しました   *****\n");
	printf("コマンドを入力してください\n");
	printf("コマンドの使用法を見るには、\"help\"コマンドを入力してください\n");

	while (true) {
		printf(">>> ");
		std::getline(std::cin, com);
		// print
		if (com == "print") {
			UI::print_schedule(lines, MAX_LINES);
			continue;
		}
		// list
		else if (com == "list") {
			// 処理
			UI::list_schedule();
			continue;
		}
		// add
		else if (com == "add") {
			// 処理
			UI::add_schedule();
			continue;
		}
		// delete
		else if (com == "delete") {
			// 処理
			UI::delete_schedule();
			continue;
		}
		// clear
		else if (com == "clear") {
			// 処理
			UI::clear_schedule();
			continue;
		}
		// make template
		else if (com == "make template") {
			// 処理
			UI::make_template();
			continue;
		}
		// set
		else if (com == "set") {
			// 処理
			UI::set_schedule();
			continue;
		}
		// help
		else if (com == "help") {
			// 処理
			UI::print_help();
			continue;
		}
		// quit
		else if (com == "quit") {
			// 登録した予定を破棄するか、テンプレートファイルに保存するかを尋ねてから終了!!
			// 処理
			printf("プログラムを終了します\n");
			break;
		}
		// コマンドにない
		else {
			printf("エラー：コマンドに誤りがあります\n");
			printf("使用法を見るには、\"help\"コマンドを入力してください\n");
			printf("終了するには\"quit\"を入力してください\n");
			continue;
		}
	}




	return 0;
}

#ifdef DEBUG
// デバッグ処理
#endif