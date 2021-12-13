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

//Register number, offset 분리 함수
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

		//입력 구분한 이유 : 입력되는 값의 순서가 다르기 때문
		if (data[i].operation == "LW" || data[i].operation == "SW") { //memWrite I-format 입력
			getline(fin, input);
			address.push_back(&data[i].rt);
			address.push_back(&data[i].offset);
			address.push_back(&data[i].rs);
			
			split(input, " ,()$", address);
		}
		else if (data[i].operation == "ADD" || data[i].operation == "OR") { //R-format 입력
			getline(fin, input);
			address.push_back(&data[i].rd);
			address.push_back(&data[i].rs);
			address.push_back(&data[i].rt);

			split(input, " ,()$", address);
		}
		else { //memWrite 안하는 I-format 입력
			getline(fin, input);
			address.push_back(&data[i].rd);
			address.push_back(&data[i].rs);
			address.push_back(&data[i].offset);

			split(input, " ,()$", address);
		}

		// hazard를 확인할 이전 command가 없으므로
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

		//MEM Data Hazard 확인할 필요가 없는 경우
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