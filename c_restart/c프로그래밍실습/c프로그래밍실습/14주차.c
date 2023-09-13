#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void print_line(int, int, int);
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		print_line(n - i, i * 2 - 1, n - i);
	}
	return 0;
}
void print_line(int x, int y, int z) {
	for (int i = 0; i < x; i++) printf(" ");
	for (int i = 0; i < y; i++) printf("*");
	for (int i = 0; i < z; i++) printf(" ");
	printf("\n");
}



int count_strike(int, int, int);
int count_ball(int, int, int);




int count_strike(int x, int y, int z) {
	int sum = 0; int a, b, c;
	if (x == a) sum++;
	if (y == b)sum++;
	if (z == c)sum++;
	return sum;
}
int count_ball(int x, int y, int z) {
	int sum = 0,a,b,c;
	if (x == b|| x == c) sum++;
	if (y == a|| y == c)sum++;
	if (z == a|| z ==c)sum++;
	return sum;
}




void input(int* p, int M);
int* sel_max(int* p, int M);
void output(int* p, int N);

int main_124(void) {
	int in[100], out[100], * max, i, N, M;
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i++) {
		input(in, M);// 각 줄에 숫자 입력
		max = sel_max(in, M);//각 줄에서 중복 숫자 포인터 반환
		out[i] = *max;
	}
	output(out, N);
	return 0;
}

void input(int* p, int M) {
	int* q;
	for (q = p; q < p + M; q++) scanf("%d", q);
}

int* sel_max(int* p, int M) {
	int* q, * r, c = 0, max = 0, *result=0;
	for (q = p; q < p + M; q++) {
		c = 0;
		for (r = p; r < p + M; r++) {
			if (*r == *q) c++;
		}
		if (c > max) { max = c; result = q; }
	}
	return result;
}

void output(int* p, int N) {
	int* q;
	for (q = p; q < p + N; q++) printf("%d ", *q);
}
