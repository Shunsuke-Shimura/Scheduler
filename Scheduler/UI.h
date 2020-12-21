/*
************** ユーザーインターフェース *************
* ユーザーインターフェースに関する関数や各コマンドの処理をまとめたもの
* エラー処理関数fatalはstd::stringのメッセージを引数として、エラー文の後にそのメッセージを表示してプログラムを終了する。
*
*/
#pragma once
#include <string>
#include "ProductionLine.h"
#include "test.h"
#define DEBUG


namespace UI {
	void fatal(std::string msg); // 致命的なエラー処理関数、std::stringのメッセージを引数として、エラー文の後にそのメッセージを表示してすべてのプログラムを終了する。
	void print_schedule(ProductionLine lines[], int n);
	void make_template();
	void set_schedule(); // 複数の予定をテンプレートファイルからまとめて入力
	void clear_schedule();
	void list_schedule();
	void add_schedule();
	void add_plans(int type_v, char color_v, int amount_v, char deadline_v);
	void delete_schedule(int); // 渡された番号の予定を削除
	void print_help(int); // 渡されたコマンドのヘルプを表示

}

#ifdef DEBUG
void print_schedule(ProductionLine_Test[], int n);
#endif