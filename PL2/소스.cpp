#include <iostream>

using namespace std;

int i = 0;
int a[2] = { 1,1 };

void call_by_reference(int& x, int& y);
void call_by_value_result_call(int* x, int* y);
void call_by_value_result_return(int* x, int* y);
void call_by_name(int* x, int* y);

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
	call_by_name(&a[i], &a[i]);
	printf("Call by name : %d %d\n", a[0], a[1]);

	return 0;
}

void call_by_reference(int& x, int& y) { // i=0일 때 a[i]를 참조하는 참조형 변수를 선언함
	x++; i++; y++; //x와 y는 각각 a[0]을 가리키므로 a[0] = 3, a[1] = 1이 됨
}

void call_by_value_result_call(int* x, int* y) { // i=0일 때 a[i]의 주소 값을 저장한 포인터 변수를 불러옴
	int xx, yy; // 임의의 local 변수를 생성해 값을 불러옴
	xx = *x; yy = *y;
	
	xx++; i++; yy++;

	*x = xx; *y = yy; // 연산 후 호출 시에 불러왔던 주소가 가리키는 변수에 값을 저장
}

void call_by_value_result_return(int* x, int* y) {
	int xx, yy; // 임의의 local 변수를 생성해 값을 불러옴
	xx = *x; yy = *y;

	xx++; i++; yy++;

	x = x + i; y = y + i; // 연산 후 반환할 주소를 불러옴 
	*x = xx; *y = yy; // 주소를 불러온 후 값 저장
}

void call_by_name(int* x, int* y) { 
	int xx = *x;
	xx++;
	*x = xx;

	i++; x = x + i; y = y + i;

	int yy = *y;
	yy++;
	*y = yy;
}