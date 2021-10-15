#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

struct info {
	string size;
	string condition;
	string price;
};

map<int, string> kind;

vector<string> split(string input, char delimiter) {
	vector<string> answer;
	stringstream ss(input);
	string tmp;

	while (getline(ss, tmp, delimiter)) {
		answer.push_back(tmp);
	}
	
	return answer;
}
int start();
int sales();
int purchase();
void regi_cloth(int category, info cloth);
int filter();
void refresh_db(vector<info> db);

int category;

int main(void) {
	
	kind.insert(make_pair(1, "shirts.txt"));
	kind.insert(make_pair(2, "jacket.txt"));
	kind.insert(make_pair(4, "skirts.txt"));
	kind.insert(make_pair(6, "pants_summer.txt"));
	kind.insert(make_pair(3, "pants_winter.txt"));
	kind.insert(make_pair(5, "none.txt"));

	int menu = 0;

	while (1) {
		switch (menu) {
		case 9:
			break;
		case 0: 
			menu = start();
			break;
		case 1:
			menu = purchase();
			break;
		case 2:
			menu = sales();
			break;
		case 3:
			menu = filter();
			break;
		default:
			break;
		}
		if (menu == 9) break;
	}

	return 0;
}

int start() {
	int input;

	cout << "\n------교복 구매 프로그램-----\n";
	do {
		cout << "1. 교복 구매     2. 교복 판매 등록      3. 종료\n";
		cout << "입력 : ";
		cin >> input;
	} while (input != 1 && input != 2 && input != 3);

	system("cls");
	if (input == 3) return 9;
	return input;
}

int sales() {
	int category;
	info admit_info;
	cout << "\n------교복 정보 입력------\n";
	do{
		cout << "1. 셔츠    2. 재킷    3. 바지    4. 치마    5. ??\n";
		cout << "교복 종류 입력 : ";
		cin >> category;
	} while (category < 1 || category > 6);

	if (category == 3) {
		do {
			cout << "1. 동복     2. 하복\n";
			cout << "종류 입력 : ";
			cin >> category;

			if (category == 1) category = 3;
			else if (category == 2) category = 6;
		} while (category != 1 && category != 2);
	}

	cout << "옷 사이즈(S, M, L, XL, 2XL) : ";
	cin >> admit_info.size;
	cout << "옷 상태(G(Good), S(Soso), B(Bad)) : ";
	cin >> admit_info.condition;
	cout << "옷 가격(원) : ";
	cin >> admit_info.price;

	system("cls");
	cout << "교복 등록중...\n";
	regi_cloth(category, admit_info);
	Sleep(1000);
	cout << "등록 완료!\n";
	Sleep(2000);
	system("cls");

	return 0;
}

int purchase() {
	info admit_info;
	cout << "\n------교복 정보 입력------\n";
	do {
		cout << "1. 셔츠    2. 재킷    3. 바지    4. 치마    5. ??\n";
		cout << "교복 종류 입력 : ";
		cin >> category;
	} while (category < 1 || category > 6);

	if (category == 3) {
		do {
			cout << "1. 동복     2. 하복\n";
			cout << "종류 입력 : ";
			cin >> category;

			if (category == 1) category = 3;
			else if (category == 2) category = 6;
		} while (category != 1 && category != 2);
	}

	return 3;
}

void regi_cloth(int category, info cloth) {
	ofstream fout;
	string filename;
	filename = kind[category];

	fout.open(filename, ios_base::app);

	if (fout.is_open()) {
		fout << cloth.size + " " + cloth.condition + " " + cloth.price << endl;
	}
	fout.close();
}

int filter() {
	info search;
	vector<info> db;

	cout << "옷 사이즈(S, M, L, XL, 2XL) : ";
	cin >> search.size;

	ifstream fin;
	fin.open(kind[category]);
	string tmp;
	vector<string> tmpp;
	info info_tmp;

	while (!fin.eof() ) {
		getline(fin, tmp);
		if (tmp == "") break;
		tmpp = split(tmp, ' ');
		info_tmp.size = tmpp[0];
		info_tmp.condition = tmpp[1];
		info_tmp.price = tmpp[2];

		if(info_tmp.size == search.size) db.push_back(info_tmp);
	}

	fin.close();

	system("cls");

	cout << "  번호    사이즈    상태    가격  " << endl;
	char t[65];
	for (int i = 0; i < db.size(); i++) {
		cout << "   ";
		cout << i + 1;
		cout << "        " + db[i].size + "        " + db[i].condition + "     " + db[i].price + "\n";
	}
	cout << "   0 : 나가기" << endl;
	cout << "구매할 옷 번호 입력 : ";
	int num;
	cin >> num;

	if (num == 0) return 0;

	cout << "선택한 옷 - " + db[num - 1].size + " " + db[num - 1].condition + " " + db[num - 1].price << endl;

	string cost;
	do {
		cout << "돈을 입력해주세요 : ";
		cin >> cost;
	} while (db[num - 1].price != cost);

	db.erase(db.begin() + num - 1);
	system("cls");
	cout << "구매가 완료되었습니다.";
	Sleep(1000);
	system("cls");

	refresh_db(db);

	return 0;
}

void refresh_db(vector<info> db) {
	ofstream fout;
	fout.open(kind[category], ios_base::out);
	
	string input;
	for (auto i : db) {
		input = i.size + " " + i.condition + " " + i.price;
		fout << input << endl;
	}
	fout.close();
}