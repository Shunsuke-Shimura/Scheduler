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
	// ファイル内リンク用プロトタイプ宣言
	static bool is_appropriate(int, char, int, char);
	static std::vector<int> buffer_to_array(std::string);
	

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
		std::ifstream reading_file(".temp_conf.txt", std::ios::in);
		if (!reading_file) {
			fatal("テンプレート初期化用ファイルが紛失しています。");
		}
		std::ofstream fout("template.txt", std::ios::trunc);
		if (!fout) fatal("テンプレートファイルを開けませんでした。\n");

		std::string reading_buffer;
		while (!reading_file.eof()) {
			std::getline(reading_file, reading_buffer);
			fout << reading_buffer << std::endl;
		}
		printf("テンプレートファイルを作成しました。ファイル名は\"template.txt\"です。\n");
	}

	/*
	* data_listの内容を"template.txt"に記録する
	*/
	void record_in_template() {

	}

	/*
	* テンプレートファイルから予定を複数まとめて受け取る
	*/
	void set_schedule() {
		std::ifstream reading_file("template.txt", std::ios::in);
		if (!reading_file) {
			printf("ファイルが存在しない、もしくは開けませんでした。\n");
			printf("\"make template\"コマンドを用いてテンプレートファイルを作成してください。\n");
		}
		std::string reading_file_buffer;
		printf("\"template.txt\"を読み込んでいます...\n");
		std::vector<std::string> fail_str; // 読み込みに失敗した行を保存
		while (!reading_file.eof()) {
			int type_v, amount_v;
			char color_v, deadline_v;
			// getlineで入力
			std::getline(reading_file, reading_file_buffer);
			if (reading_file_buffer[0] == '#' || reading_file_buffer[0] == '\0' || reading_file_buffer[0] == '\n') continue; // コメント行を飛ばす処理
			std::vector<int> vec = buffer_to_array(reading_file_buffer);
			if (vec.size() != 4) {
				fail_str.push_back(reading_file_buffer);
			}
			else {
				type_v = vec[0];
				color_v = (char)vec[1];
				amount_v = vec[2];
				deadline_v = (char)vec[3];
				if (!is_appropriate(type_v, color_v, amount_v, deadline_v)) {
					fail_str.push_back(reading_file_buffer);
				}
				else {
					add_plans(type_v, color_v, amount_v, deadline_v);
				}
			}
		}
		int f_str_size = fail_str.size();
		if (f_str_size == 0) {
			printf("テンプレートファイルから予定をすべて読み込みました。\n");
		}
		else {
			printf("テンプレートファイルから予定を読み込みました。\n");
			printf("フォーマットに合わない文が %d 行ありました。\n", f_str_size);
			for (int i = 0; i < f_str_size; i++) {
				std::cout << i + 1 << " : " << fail_str[i] << std::endl;
			}
			std::cout << std::endl;
			printf("コマンド処理を終了します。\n");
		}
	}

	/*
	* getlineで読み込んだ行から数値を配列要素として取り出す
	*/
	static std::vector<int> buffer_to_array(std::string buffer) {
		std::vector<int> vec;
		int N = buffer.size();
		char c;
		int tmp = 0;
		for (int i = 0; i < N; i++) {
			c = buffer[i];
			if (c == ' ' || c == '　') {
				vec.push_back(tmp);
				tmp = 0;
			}
			else {
				tmp *= 10;
				tmp += (c - '0');
			}
		}
		vec.push_back(tmp);
		return vec;
	}
	/*
	* vector内の数値が適切な値かを調べる
	*/
	static bool is_appropriate(int type_v, char color_v, int amount_v, char deadline_v) {
		if (type_v < 0 || type_v > MAX_TYPE) return false;
		if (color_v < 0 || color_v > MAX_COLOR) return false;
		if (amount_v < 0) return false;
		if (deadline_v < 0 || deadline_v > 31) return false;
		return true;
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
				std::cout << "何番目の予定を削除しますか?（処理をキャンセルするには0を入力してください）\n";
				std::cout << ">>> ";
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

