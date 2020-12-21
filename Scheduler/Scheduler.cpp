/*
*********************メインソースコード ********************** 
* メイン関数や各種大域変数宣言を行っている。
* 他ファイルで大域変数を用いるにはexternコマンドを用いる
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <list>
#include "Data.h"
#include "ProductionLine.h"
#include "Test.h"
#include "UI.h"
#include "configuration.h"
#define DEBUG

// 大域変数宣言
ProductionLine lines[MAX_LINES] = { ProductionLine(1023, 200), ProductionLine(1023, 300),  ProductionLine(1023, 100),  ProductionLine(1023, 100) };
std::list<Data> data_list; // 予定を格納する

int main() {
	ProductionLine_Test lines_t[4] = { ProductionLine_Test(1023, 200), ProductionLine_Test(1023, 300), ProductionLine_Test(1023, 100), ProductionLine_Test(1023, 100) };
	std::string com;


	printf("*****    起動しました   *****\n");
	printf("コマンドを入力してください\n");

	while (true) {
		printf(">>> ");
		std::getline(std::cin, com);
		// print
		if (com == "print") {
			print_schedule(lines_t, 4);
			continue;
		}
		// list
		else if (com == "list") {
			// 処理
			printf("コマンドがまだありません\n");
			continue;
		}
		else if (com == "add schedule") {
			// 処理
			UI::add_schedule();
			continue;
		}
		// clear schedule
		else if (com == "clear schedule") {
			// 処理
			printf("コマンドがまだありません\n");
			continue;
		}
		// make template
		else if (com == "make template") {
			// 処理
			UI::make_template();
			continue;
		}
		else if (com == "set schedule") {
			// 処理
		}
		// help
		else if (com == "help") {
			// 処理
			printf("コマンドがまだありません\n");
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
			continue;
		}
	}




	return 0;
}

