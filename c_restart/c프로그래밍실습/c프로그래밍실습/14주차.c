#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
// #include<string.h>
#include<time.h>
/*
strlen() : ����
strcpy(a,b) : a�� b�� ����
strcat(a,b) : a �ڿ� b�� ����
strcmp(a,b) : s1�� ����
b = atoi,l,f(a): ���� ���� ���� ���ڸ� ���ڷ� ��ȯ
*/
struct student {
	int firstStage, interview;
	double sum;
	char* name;
};
int input(int *p);
int* sel_next(int* p);
int number(int* p, int* q);
int main() {
	int *p, * q = NULL, n, a;
	p = (int*)malloc(sizeof(int) * 100);
	n = input(p);
	p = realloc(p, sizeof(int) * (n + 1));

	while (1) {
		q = sel_next(p);
		a = number(p, q);
		if (a < 10) break;
		printf("%d\n", a);
		p = q;
	}
}
int input(int* p) {

	int sum = 0;
	int* q = p;
	while (1) {
		scanf("%d", q);
		if (*q == -1) break;
		q++;
		sum++;
	}
	return sum;
}
int* sel_next(int* p) {
	int* q = p, c;
	if (*q > *(q + 1)) c = 1;
	else c = 0;
	while (1) {
		if ((*q > *(q + 1) && c == 0)|| *(q+1) == -1) break;
		else if (*q < *(q + 1) && c == 1) break;
		q++;
	}
	return q;
}
int number(int* p, int* q) {
	int sum = 0;
	while (p != q) {
		sum *= 10;
		sum += *p;
		p++;
	}
	sum *= 10;
	sum += *p;
	return sum;
}

