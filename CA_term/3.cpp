#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

ofstream fout("test.out");

class command {
public:
	string operation;
	string rs, rt, rd;
	string offset;
	command() {
		operation = "";
		rs = rt = rd = "";
		offset = "";
	}
};

vector<command> asm_data;

//Register number, offset 분리 함수
void split(string input, string div, vector<string*> asm_data) {
	char* c = strtok((char*)input.c_str(), div.c_str());
	int p = 0;
	while (c) {
		*asm_data[p++] = c;
		c = strtok(NULL, div.c_str());
	}
}

void printHazard(int idx, int type) {
	string ans;

	ans = "Line number : " + to_string(idx + 1);
	ans += ", Hazard Type : ";
	switch (type) {
		case 0: 
			ans += "Load - use Data hazard";
			ans += ", Register : $" + asm_data.at(idx - 1).rt;
			break;
		case 1: 
			ans += "EX Data hazard";
			ans += ", Register : $" + asm_data.at(idx - 1).rd;
			break;
		case 2: 
			ans += "MEM Data hazard";
			ans += ", Register : $" + asm_data.at(idx - 1).rt;
			break;
	}
	ans += ", Reason : Line " + to_string(idx);

	fout << ans << endl;
}

bool ex_DataHazard(int idx) {
	if (idx == 0 || asm_data.at(idx - 1).operation == "SW") return false;
	
	if (asm_data.at(idx - 1).rd == asm_data.at(idx).rt || asm_data.at(idx - 1).rd == asm_data.at(idx).rs)
		return true;
	else return false;
}

bool mem_DataHazard(int idx) {
	if (idx < 2) return false;
	if (asm_data.at(idx - 2).operation == "LW" || asm_data.at(idx - 2).operation == "SW") return false;

	if (asm_data.at(idx - 2).rd == asm_data.at(idx).rt || asm_data.at(idx - 2).rd == asm_data.at(idx).rs)
		return true;
	else return false;
}

bool load_DataHazrd(int idx) {
	if (idx == 0 || asm_data.at(idx - 1).operation != "LW") return false;

	if (asm_data.at(idx - 1).rt == asm_data.at(idx).rt || asm_data.at(idx - 1).rt == asm_data.at(idx).rs)
		return true;
	else return false;
}

int main(void) {

	ifstream fin("input.txt");

	string input;
	string ans;
	command tmp;

	for (int i = 0; !fin.eof(); i++) {
		vector<string*> address;
		asm_data.push_back(tmp);
		fin >> asm_data.at(i).operation;

		//입력 구분한 이유 : 입력되는 값의 순서가 다르기 때문
		if (asm_data.at(i).operation == "LW" || asm_data.at(i).operation == "SW") { //memWrite I-format 입력
			getline(fin, input);
			address.push_back(&asm_data.at(i).rt);
			address.push_back(&asm_data.at(i).offset);
			address.push_back(&asm_data.at(i).rs);
			
			split(input, " ,()$", address);
		}
		else if (asm_data.at(i).operation == "ADD" || asm_data.at(i).operation == "OR") { //R-format 입력
			getline(fin, input);
			address.push_back(&asm_data.at(i).rd);
			address.push_back(&asm_data.at(i).rs);
			address.push_back(&asm_data.at(i).rt);

			split(input, " ,()$", address);
		}
		else { //memWrite 안하는 I-format 입력
			getline(fin, input);
			address.push_back(&asm_data.at(i).rd);
			address.push_back(&asm_data.at(i).rs);
			address.push_back(&asm_data.at(i).offset);

			split(input, " ,()$", address);
		}

		if (load_DataHazrd(i)) printHazard(i, 0); //Load-use asm_data Hazard
		else if (ex_DataHazard(i)) printHazard(i, 1); //EX asm_data Hazard
		else if (mem_DataHazard(i)) printHazard(i, 2); //MEM asm_data hazard
	}

	fin.close();
	fout.close();
	return 0;
}