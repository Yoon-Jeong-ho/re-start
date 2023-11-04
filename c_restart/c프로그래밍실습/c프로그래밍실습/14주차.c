#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/*
strlen() : 길이
strcpy(a,b) : a에 b를 복사
strcat(a,b) : a 뒤에 b를 붙임
strcmp(a,b) : s1의 순위
b = atoi,l,f(a): 숫자 형에 따른 문자를 숫자로 변환
*/
typedef struct {
	char* name;
	int id,test1,test2, e, m, num, result, cnt,rank;
	float mean;
}student;
void input(int*, int);

void output(int*, int);
int main() {
	int n, num1 = 0, num2 = 0, ** nn, m,intstore[100],*p,*q,k=0,test1pass,test2pass;
	float* num, max = -99999;
	student* st, ttmp;

	char** c, a = 'a', b, tmp[105], minc[100] = "",str[11][105];
	
	scanf("%d", &n); getchar();
	st = (student*)malloc(sizeof(student) * n);
	if (st == NULL) return -1;
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &st[i].id, &st[i].test1, &st[i].test2);
		st[i].mean = (st[i].test1*40 + st[i].test2*60);
		st[i].mean /= 100;

	}
	test1pass = n * 0.6;
	test2pass = n * 0.8;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (st[i].id > st[j].id) {
				ttmp = st[i];
				st[i] = st[j];
				st[j] = ttmp;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		num1 = 1;
		num2 = 1;
		for (int j = 0; j < n; j++) {
			if (st[i].mean < st[j].mean) num1++;
			if (st[i].test2 < st[j].test2) num2++;
		}
		if (num1 <= test1pass) k++;
		st[i].rank = num1;
		st[i].cnt = num2;
	}
	for (int i = 0; i < n; i++) {
		if (st[i].rank <= test1pass) printf("%d\n", st[i].id);
		else if (st[i].cnt <= test2pass && k < test2pass) {
			printf("%d\n", st[i].id);
		}
	}
	free(st);
	return 0;
}
void input(int* p, int n) {
	int* q;
	for (q = p; q < p + n; q++) scanf("%d ", q);
}

void output(int* p, int k) {
	int* q;
	for (q = p; q < p + k; q++) printf("%d ", *q);
}