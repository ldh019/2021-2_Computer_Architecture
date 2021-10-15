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

	cout << "\n------���� ���� ���α׷�-----\n";
	do {
		cout << "1. ���� ����     2. ���� �Ǹ� ���      3. ����\n";
		cout << "�Է� : ";
		cin >> input;
	} while (input != 1 && input != 2 && input != 3);

	system("cls");
	if (input == 3) return 9;
	return input;
}

int sales() {
	int category;
	info admit_info;
	cout << "\n------���� ���� �Է�------\n";
	do{
		cout << "1. ����    2. ��Ŷ    3. ����    4. ġ��    5. ??\n";
		cout << "���� ���� �Է� : ";
		cin >> category;
	} while (category < 1 || category > 6);

	if (category == 3) {
		do {
			cout << "1. ����     2. �Ϻ�\n";
			cout << "���� �Է� : ";
			cin >> category;

			if (category == 1) category = 3;
			else if (category == 2) category = 6;
		} while (category != 1 && category != 2);
	}

	cout << "�� ������(S, M, L, XL, 2XL) : ";
	cin >> admit_info.size;
	cout << "�� ����(G(Good), S(Soso), B(Bad)) : ";
	cin >> admit_info.condition;
	cout << "�� ����(��) : ";
	cin >> admit_info.price;

	system("cls");
	cout << "���� �����...\n";
	regi_cloth(category, admit_info);
	Sleep(1000);
	cout << "��� �Ϸ�!\n";
	Sleep(2000);
	system("cls");

	return 0;
}

int purchase() {
	info admit_info;
	cout << "\n------���� ���� �Է�------\n";
	do {
		cout << "1. ����    2. ��Ŷ    3. ����    4. ġ��    5. ??\n";
		cout << "���� ���� �Է� : ";
		cin >> category;
	} while (category < 1 || category > 6);

	if (category == 3) {
		do {
			cout << "1. ����     2. �Ϻ�\n";
			cout << "���� �Է� : ";
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

	cout << "�� ������(S, M, L, XL, 2XL) : ";
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

	cout << "  ��ȣ    ������    ����    ����  " << endl;
	char t[65];
	for (int i = 0; i < db.size(); i++) {
		cout << "   ";
		cout << i + 1;
		cout << "        " + db[i].size + "        " + db[i].condition + "     " + db[i].price + "\n";
	}
	cout << "   0 : ������" << endl;
	cout << "������ �� ��ȣ �Է� : ";
	int num;
	cin >> num;

	if (num == 0) return 0;

	cout << "������ �� - " + db[num - 1].size + " " + db[num - 1].condition + " " + db[num - 1].price << endl;

	string cost;
	do {
		cout << "���� �Է����ּ��� : ";
		cin >> cost;
	} while (db[num - 1].price != cost);

	db.erase(db.begin() + num - 1);
	system("cls");
	cout << "���Ű� �Ϸ�Ǿ����ϴ�.";
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