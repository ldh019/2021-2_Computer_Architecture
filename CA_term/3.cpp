#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct command {
	string operation;
	string rs, rt, rd;
	string offset;
};

//Register number, offset �и� �Լ�
void split(string input, string div, vector<string*> data) {
	char* c = strtok((char*)input.c_str(), div.c_str());
	int p = 0;
	while (c) {
		*data[p++] = c;
		c = strtok(NULL, div.c_str());
	}
}

int main(void) {
	command data[10];

	ifstream fin("input.txt");
	ofstream fout("output.txt");
	string input;
	string ans;

	FILE* fi = fopen("input.txt", "r");

	for (int i = 0; !fin.eof(); i++) {
		vector<string*> address;
		fin >> data[i].operation;

		//�Է� ������ ���� : �ԷµǴ� ���� ������ �ٸ��� ����
		if (data[i].operation == "LW" || data[i].operation == "SW") { //memWrite I-format �Է�
			getline(fin, input);
			address.push_back(&data[i].rt);
			address.push_back(&data[i].offset);
			address.push_back(&data[i].rs);
			
			split(input, " ,()$", address);
		}
		else if (data[i].operation == "ADD" || data[i].operation == "OR") { //R-format �Է�
			getline(fin, input);
			address.push_back(&data[i].rd);
			address.push_back(&data[i].rs);
			address.push_back(&data[i].rt);

			split(input, " ,()$", address);
		}
		else { //memWrite ���ϴ� I-format �Է�
			getline(fin, input);
			address.push_back(&data[i].rd);
			address.push_back(&data[i].rs);
			address.push_back(&data[i].offset);

			split(input, " ,()$", address);
		}

		// hazard�� Ȯ���� ���� command�� �����Ƿ�
		if (i == 0) continue;

		//Load-use Data Hazard
		if (data[i - 1].operation == "LW") {
			if (data[i - 1].rt != "" && data[i - 1].rt == data[i].rt || data[i - 1].rt == data[i].rs) {
				ans = "Line number : " + to_string(i + 1);
				ans += ", Hazard Type : Load-use data hazard";
				ans += ", Register : $" + data[i - 1].rt;
				ans += ", Reason : Line " + to_string(i);

				fout << ans << endl;
			}
		}
		else if (data[i - 1].operation != "SW") { //EX Data Hazard
			if (data[i - 1].rd != "" && data[i - 1].rd == data[i].rt || data[i - 1].rd == data[i].rs) {
				ans = "Line number : " + to_string(i + 1);
				ans += ", Hazard Type : Data hazard";
				ans += ", Register : $" + data[i - 1].rd;
				ans += ", Reason : Line " + to_string(i);

				fout << ans << endl;
			}
		}

		//MEM Data Hazard Ȯ���� �ʿ䰡 ���� ���
		if (i == 1) continue;

		if ((data[i - 2].operation != "LW" || data[i - 2].operation != "SW") //MEM Data Hazard
			&& data[i - 2].rd != "" && (data[i - 2].rd == data[i].rt || data[i - 2].rd == data[i].rs)) {
			ans = "Line number : " + to_string(i + 1);
			ans += ", Hazard Type : Data hazard";
			ans += ", Register : $" + data[i - 1].rt;
			ans += ", Reason : Line " + to_string(i);

			fout << ans << endl;
		}
	}

	fin.close();
	fout.close();

	return 0;
}