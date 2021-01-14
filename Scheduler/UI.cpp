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
	* そのままプログラムを続行できない致命的なエラーを処理する
	* msgを引数として、"致命的なエラー："という定型文の後にmsgを出力して
	* 全体のプログラムを異常終了する。
	*/
	void fatal(std::string msg) {
		std::string error_msg = "致命的なエラー : ";
		error_msg += msg;
		printf("\n\n%s", error_msg.c_str());
		printf("プログラムを終了します...\n");
		exit(-1);
	}


	/* 
	* リストを日付順にソートしてから生産ラインのcalendarに組み込んで、
	* スケジュールをカレンダー形式で表示する
	* 生産ラインの数を n として引数に渡す
	*/
	void print_schedule(ProductionLine lines[], int n) {
		// リストを日付順にソート
		sort_data_list();

		// lines[]の初期化
		init_lines();

		// リストから一つずつ予定をラインのcalendarに組み込んでいく
		for (std::vector<Data>::iterator it = data_list.begin(); it != data_list.end(); it++) (*it).schedule();

		if (n != 4) {
			fatal("print_schedule関数内でラインの数が一致しません。");
		}

		// カレンダーを表示
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
			printf("/%d個\t\t\t", amount);

			// LINE1
			lines[1].get_data(date, type, color, amount);
			printf("line2:\t");
			Config::print_type(type);
			printf("/");
			Config::print_color(color);
			printf("/%d個", amount);

			printf("\n\t||\t");

			// LINE2
			lines[2].get_data(date, type, color, amount);
			printf("line3:\t");
			Config::print_type(type);
			printf("/");
			Config::print_color(color);
			printf("/%d個\t\t\t", amount);

			// LINE3
			lines[3].get_data(date, type, color, amount);
			printf("line4:\t");
			Config::print_type(type);
			printf("/");
			Config::print_color(color);
			printf("/%d個", amount);
			printf("\n\n");
		}

		// ==================================================================================
		for (int i = 0; i < 100; i++) printf("=");
		printf("\n");
	}


	/*
	* lines[]のcalendar, filled_daysを初期化する
	*/
	void init_lines() {
		for (int i = 0; i < MAX_LINES; i++) {
			lines[i].init();
		}
	}

	/*
	* data_listを日付順にソートする（挿入ソート）
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
	* 予定を入力するためのテキストファイルのテンプレートをつくる
	* テキストファイルのテンプレートには、予定を入力するための形式を示す
	*/
	void make_template() {
		std::ofstream fout("template.txt", std::ios::trunc);
		if (!fout) fatal("テンプレートファイルを開けませんでした。\n");
		else {
			fout << "# これは予定を複数同時に入力するためのテンプレートファイルです。テンプレート説明文の次の行から、１行に予定を一つずつ入力してください。\n";
			fout << "# \"・#などの記号は入力しないでください。\n";
			fout << "# 予定の入力は次のフォーマットに従ってください。また、必ず半角文字を用いてください。\n";
			fout << "# \"<型(半角数字)> <色(半角数字)> <納品量> <納品の日付>\"\n";
			fout << "# また、型名、色については以下の番号で入力してください。\n";
			fout << "# ・雪止め : 1　　　,新銀				: 1";
			fout << "# ・万十	: 2　　　,ブラック			: 2";
			fout << "# ・安定万十 : 3　　,プラチナメタリック: 3";
			fout << "# ・自在万十 : 4　　,ハイシルバー		: 4";
			fout << "# ・紐袖 : 5　　　　,チョコ			: 5";
			fout << "# ・並袖 : 6　　　　,青銅				: 6";
			fout << "#				   　,青緑				: 7";
			fout << "#  			   　, オレンジ			: 8";
			printf("テンプレートファイルを作成しました。ファイル名は\"schedule.txt\"です。\n");
		}
	}

	/*
	* data_listの内容を"template.txt"に記録する
	*/
	void record_in_template() {

	}

	/*
	* テンプレートファイルから予定を複数まとめて受け取る
	* ************************ 未完成 ******************
	*/
	void set_schedule() {
		std::ifstream reading_file("schedule.txt", std::ios::in);
		if (!reading_file) {
			printf("ファイルが存在しない、もしくは開けませんでした。\n");
			printf("\"make template\"コマンドを用いてテンプレートファイルを作成してください。\n");
		}
		else {
			std::string reading_file_buffer;
			printf("\"schedule.txt\"を読み込んでいます...\n");
			while (!reading_file.eof()) {
				int type_v, amount_v, color_tmp, deadline_tmp;
				char color_v, deadline_v;
				// getlineで入力
				std::getline(reading_file, reading_file_buffer);
				

			}
			printf("テンプレートファイルから予定をすべて読み込みました。\n");
		}
	}

	

	/*
	* "clear"コマンドの処理をする
	* 本当に予定を削除するかを確認してから予定をすべて削除する
	*/
	void clear_schedule() {
		std::string confirm;
		std::cout << "本当に追加した予定をすべて削除しますか？" << std::endl;
		while (true) {
			std::cout << "Yes / No >>> ";
			std::cin >> confirm;
			if (confirm == "Yes" || confirm == "yes") {
				data_list.clear();
				std::cout << "予定をすべて削除しました。\n";
				break;
			}
			else if (confirm == "No" || confirm == "no") {
				break;
			}
			else {
				std::cout << "入力が正しくありません\n";
			}
		}
	}

	/*
	* "list"コマンドの処理をする
	* 予定のリストを日付順に挿入ソートした後に、そのリストを番号付きで表示する
	*/
	void list_schedule() {
		int size = data_list.size();
		if (size == 0) {
			std::cout << "追加されている予定はありません\n";
			return;
		}
		else {
			// 日付によるソート処理
			sort_data_list();
			
			// ここから表示
			int num = 1; // 要素番号
			for (std::vector<Data>::iterator it = data_list.begin(); it != data_list.end(); it++) {
				printf("%d :\t", num++);
				Config::print_type((*it).rtn_type());
				printf("\t");
				Config::print_color((*it).rtn_color());
				printf("\t%d (枚)\t納品日 / %d(日)\n", (*it).rtn_amount(), (int)(*it).rtn_deadline());
			}
			printf("入力された予定は以上です。\n");
		}
	}

	/*
	* "add"コマンドの処理をする
	* 型や色などを数字の入力によって選択して予定をひとつリストに加える
	*/
	void add_schedule() {
		int type_v, amount_v, color_tmp, deadline_tmp;
		char color_v, deadline_v;
		// 処理
		std::cin.exceptions(std::ios::failbit); // cin の例外処理を有効化
		while (true) {
			try {
				printf("型番号を選択して入力してください。(予定の追加をキャンセルするには0を入力してください。)\n");
				printf("雪止め	: 1\n");
				printf("万十	: 2\n");
				printf("安定万十: 3\n");
				printf("自在万十: 4\n");
				printf("紐袖	: 5\n");
				printf("並袖	: 6\n");
				printf(">>> ");
				std::cin >> type_v;
				if (type_v == 0) {
					printf("入力をキャンセルしました。\n");
					return;
				}
				else if (type_v < 0 || type_v > 6) {
					throw -1;
				}
			}
			catch (...) {
				printf("不適切な入力です。もう一度入力してください。\n");
				continue;
			}
			break;
		}

		// エラーフラグを初期化
		std::cin.clear();
		std::cin.seekg(0);
		while (true) {
			try {
				color_tmp = -1;
				printf("色番号を選択して入力してください。(予定の追加をキャンセルするには0を入力してください。)\n");
				printf("新銀　　　　　　　: 1\n");
				printf("ブラック　　　　　: 2\n");
				printf("プラチナメタリック: 3\n");
				printf("ハイシルバー　　　: 4\n");
				printf("チョコ			　: 5\n");
				printf("青銅			　: 6\n");
				printf("青緑			　: 7\n");
				printf("オレンジ		　: 8\n");
				printf(">>> ");
				std::cin >> color_tmp;
				if (color_tmp == 0) {
					printf("入力をキャンセルしました。\n");
					return;
				}
				else if (color_tmp < 1 || color_tmp > 8) {
					throw -1;
				}
			}
			catch (...) {
				printf("不適切な入力です。もう一度入力してください。\n");
				continue;
			}
			color_v = (char)color_tmp;
			break;
		}

		// エラーフラグを初期化
		std::cin.clear();
		std::cin.seekg(0);
		while (true) {
			try {
				amount_v = -1;
				printf("必要な数量を入力してください。(予定の追加をキャンセルするには0を入力してください。)\n");
				printf(">>> ");
				std::cin >> amount_v;
				if (amount_v == 0) {
					printf("入力をキャンセルしました。\n");
					return;
				}
				else if (amount_v < 1) {
					throw - 1;
				}
			}
			catch (...) {
				printf("不適切な入力です。もう一度入力してください。\n");
				continue;
			}
			break;
		}
		// エラーフラグを初期化
		std::cin.clear();
		std::cin.seekg(0);
		while (true) {
			try {
				deadline_tmp = -1;
				printf("納品の日付を入力してください。(予定の追加をキャンセルするには0を入力してください。)\n");
				printf(">>> ");
				std::cin >> deadline_tmp;
				if (deadline_tmp == 0) {
					printf("入力をキャンセルしました。\n");
					return;
				}
				else if (deadline_tmp < 1 || deadline_tmp > 31) {
					throw - 1;
				}
			}
			catch (...) {
				printf("不適切な入力です。もう一度入力してください。\n");
				continue;
			}
			deadline_v = (char)deadline_tmp;
			break;
		}
		add_plans(type_v, color_v, amount_v, deadline_v);
		printf("予定を追加しました。\n");
	}

	/*
	* 実際にDataクラスのインスタンスを作成した後に、
	* 予定のリストに追加する
	*/
	void add_plans(int type_v, char color_v, int amount_v, char deadline_v) {
		Data plan(type_v, color_v, amount_v, deadline_v);
		data_list.push_back(plan);
	}
	
	/*
	* "delete"コマンドの処理をする
	* "list"コマンドで横に示した予定番号から予定をひとつ選んで削除する
	*/
	void delete_schedule() {
		int del_num;
		
		std::cin.exceptions(std::ios::failbit); // cin の例外処理を有効化
		while (true) {
			try {
				std::cout << "何番目の予定を削除しますか?（処理をキャンセルするには0を入力してください\n";
				std::cout << std::endl;
				std::cin >> del_num;
				if (del_num == 0) {
					printf("コマンド処理をキャンセルしました。\n");
					return;
				}
				else if (del_num < 0 || del_num > data_list.size()) {
					throw - 1;
				}
			}
			catch (...) {
				printf("不適切な入力です。もう一度入力してください。\n");
				continue;
			}
			break;
		}
		delete_data(del_num);
	}

	/*
	* 実際に予定のリストからdel_num番目のものを削除する
	*/
	void delete_data(int del_num) {
		data_list.erase(data_list.begin() + (del_num - 1));
		std::cout << del_num << "番目の予定を削除しました。\n";
	}

	/*
	* "help"コマンドの処理をする
	* 各コマンドを番号で表し、そのhelp_numの番号によって
	* そのコマンドの使用法を表示する
	*/
	void print_help() {
		std::cout << "< 各コマンドの動作 >\n";
		std::cout << "\"print\" : 登録した予定をカレンダー形式で表示\n";
		std::cout << "\"list\" : 登録した予定を確認する\n";
		std::cout << "\"delete\" : listコマンドで表示した予定に対して、\n";
			std::cout << "\t\t指定した番号の予定を削除する\n";
		std::cout << "\"add\" : 予定を追加する\n";
		std::cout << "\"make template\" : 予定を複数同時に登録するための\n";
			std::cout << "\t\tテンプレートファイルを作成する\n";
		std::cout << "\"set\" : テンプレートファイルから予定を登録する\n";
		std::cout << "\"clear\" : 登録した予定をすべて削除する\n";
		std::cout << "\"quit\" : このプログラムを終了する\n";
	}
}

#ifdef DEBUG
// テスト用
void print_schedule(ProductionLine_Test lines[], int n) { // nは要素数
	if (n != 4) UI::fatal("配列の要素数が想定外です\n");
	// カレンダーを表示
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
		printf("/%d個\t\t\t", amount);

		// line2
		lines[1].get_data(date, type, color, amount);
		printf("line2:\t");
		Config::print_type(type);
		printf("/");
		Config::print_color(color);
		printf("/%d個", amount);

		printf("\n\t||\t");
		


		// line3
		lines[2].get_data(date, type, color, amount);
		printf("line3:\t");
		Config::print_type(type);
		printf("/");
		Config::print_color(color);
		printf("/%d個\t\t\t", amount);

		// line4
		lines[3].get_data(date, type, color, amount);
		printf("line4:\t");
		Config::print_type(type);
		printf("/");
		Config::print_color(color);
		printf("/%d個", amount);
		printf("\n\n");
	}

	// ==================================================================================
	for (int i = 0; i < 100; i++) printf("=");
	printf("\n");
}


#endif

