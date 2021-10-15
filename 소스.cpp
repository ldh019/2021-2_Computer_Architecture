#include <iostream>

using namespace std;

int i = 0;
int a[2] = { 1,1 };

void call_by_reference(int& x, int& y);
void call_by_value_result_call(int* x, int* y);
void call_by_value_result_return(int* x, int* y);
void call_by_name(int x, int y);

int main() {
	i = 0;
	a[0] = a[1] = 1;
	call_by_reference(a[i], a[i]);
	printf("Call by reference : %d %d\n", a[0], a[1]);

	i = 0;
	a[0] = a[1] = 1;
	call_by_value_result_call(&a[i], &a[i]);
	printf("Call by value-result when call : %d %d\n", a[0], a[1]);

	i = 0;
	a[0] = a[1] = 1;
	call_by_value_result_return(&a[i], &a[i]);
	printf("Call by value-result when exit : %d %d\n", a[0], a[1]);

	i = 0;
	a[0] = a[1] = 1;
	call_by_name(a[i], a[i]);
	printf("Call by name : %d %d\n", a[0], a[1]);

	return 0;
}

void call_by_reference(int& x, int& y) { // i=0�� �� a[i]�� �����ϴ� ������ ������ ������
	x++; i++; y++; //x�� y�� ���� a[0]�� ����Ű�Ƿ� a[0] = 3, a[1] = 1�� ��
}

void call_by_value_result_call(int* x, int* y) { // i=0�� �� a[i]�� �ּ� ���� ������ ������ ������ �ҷ���
	int xx, yy; // ������ local ������ ������ ���� �ҷ���
	xx = *x; yy = *y;
	
	xx++; i++; yy++;

	*x = xx; *y = yy; // ���� �� ȣ�� �ÿ� �ҷ��Դ� �ּҰ� ����Ű�� ������ ���� ����
}

void call_by_value_result_return(int* x, int* y) {
	int xx, yy; // ������ local ������ ������ ���� �ҷ���
	xx = *x; yy = *y;

	xx++; i++; yy++;

	x = &a[i]; y = &a[i]; // ���� �� ��ȯ�� �ּҸ� �ҷ���
	*x = xx; *y = yy; // �ּҸ� �ҷ��� �� �� ����
}

void call_by_name(int x, int y) { // C++������ �Լ��� �ҷ����� ���ϱ� ������ ���긶�� �ش�Ǵ� ������ �ҷ����鼭 ����� �����
	x = a[i]; // ���� ������ �ش� �Լ��� �ҷ�����
	x++; // ���� �� 
	a[i] = x; // �ٽ� ���� ����

	i++;

	y = a[i]; // ���� ������ �ش� �Լ��� ���� �� 
	y++; // ����
	a[i] = y; // ���� �ٽ� ���� ����
}