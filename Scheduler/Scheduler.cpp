/*
*********************メインソースコード ********************** 
* メイン関数や各種大域変数宣言を行っている。
* 他ファイルで大域変数を用いるにはexternコマンドを用いる
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "Data.h"
#include "ProductionLine.h"
#include "Test.h"
#include "UI.h"
#include "configuration.h"
// #define DEBUG

/* 大域変数宣言 */
// linesという配列として生産ライン自体を管理する
// MAX_LINESは生産ラインの数で、"ProductionLine.h"フォルダに
// マクロとして定義される
ProductionLine lines[MAX_LINES] = { ProductionLine(1023, 200), ProductionLine(1023, 300),  ProductionLine(1023, 100),  ProductionLine(1023, 100) };

// data_listは追加された予定を保持する
std::vector<Data> data_list;


/*
* メイン関数
*/
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
			UI::list_schedule();
			continue;
		}
		else if (com == "add") {
			// 処理
			UI::add_schedule();
			continue;
		}
		// clear schedule
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
		else if (com == "set") {
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
		else if (com != "") {
			printf("エラー：コマンドに誤りがあります\n");
			printf("使用法を見るには、\"help\"コマンドを入力してください\n");
			printf("終了するには\"quit\"を入力してください\n");
			continue;
		}
		else {
			printf("\n");
			continue;
		}
	}




	return 0;
}

