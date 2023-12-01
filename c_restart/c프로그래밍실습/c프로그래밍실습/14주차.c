	#define _CRT_SECURE_NO_WARNINGS 

	#include<stdio.h>
	#include<stdlib.h>
	// #include<string.h>
	#include<time.h>
	#include<math.h>
	/*
	strlen() : 길이
	strcpy(a,b) : a에 b를 복사
	strcat(a,b) : a 뒤에 b를 붙임
	strcmp(a,b) : s1의 순위
	b = atoi,l,f(a): 숫자 형에 따른 문자를 숫자로 변환
	*/
	typedef struct  {
		int num,t1,t2;
		double sum;
	}student;

	#define ABS(a) ( (a) > 0 ? (a) : (-a))
	#define MAX(a,b) ((a)>(b)   ? (a):(b))
	int main() {
		int a, b,n,m;
		student st[100],stmp;
		char c[100][100],tmp, prev = 'X';
		scanf("%d",&a);
		double cutline= a;
		cutline = cutline * 0.7;

		for (int i = 0; i < a; i++) {
			scanf("%d %d %d", &st[i].num,&st[i].t1,&st[i].t2);
			st[i].sum = st[i].t1 * 40.0 + st[i].t2 * 60.0;
			st[i].sum = st[i].sum / 100;
			b = st[i].sum * 10;
			st[i].sum = b;
			st[i].sum /= 10;
		}
		for (int i = 0; i < a; i++) {
			for (int j = i + 1; j < a; j++) {
				if (st[i].sum < st[j].sum) {
					stmp = st[i];
					st[i] = st[j];
					st[j] = stmp;
				}
				if (st[i].sum == st[j].sum&& st[i].num > st[j].num) {
					stmp = st[i];
					st[i] = st[j];
					st[j] = stmp;
				}
			}
		}
		printf("%d", (int)(cutline));
		for (int i = 0; i < a; i++) {
			printf("%d %.1f\n", st[i].num, st[i].sum);
			if (i >= (int)(cutline)-1 && st[i].sum != st[i - 1].sum) break;
		}
	}
