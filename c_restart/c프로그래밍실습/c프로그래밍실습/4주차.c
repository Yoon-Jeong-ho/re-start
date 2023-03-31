#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main_4_0_8() {
	int N;
	scanf("%d", &N);
	N % 2 == 0 ? printf("even") : printf("odd");
	return 0;
}	
int main_4_0_9() {
	int N, M;
	scanf("%d %d", &N, &M);
	N > M ? printf("%d", N) : printf("%d", M);
	return 0;
}
int main_4_0_10() {
	int N, M;
	scanf("%d %d", &N, &M);
	N > M ? printf("%d\n %d\n", N / M, N % M) : printf("%d\n%d\n", M / N, M % N);
	return 0;
}
int main_5_0_1() {
	int N;
	scanf("%d", &N);
	if (N < 0) printf("cold, indoor");
	else if (N >= 40) printf("hot, indoor");
	else printf("moderate, outdoor");
	return 0;
}
int main_5_0_2() {
	int N, M;
	scanf("%d %d", &N, &M);
	if (N * N == M) printf("%d*%d=%d", N, N, M);
	else if (M * M == N) printf("%d*%d=%d", M, M, N);
	else printf("none");
	return 0;
}
int main_5_0_3(){
	int N, result=0;
	for (int i = 0; i < 5; i++) {
		scanf("%d", &N);
		if (N > 0) result += N;
	}
	printf("%d", result);
	return 0;
}
int main_5_0_4() {
	char ch;
	scanf("%c", &ch);
	if (ch >= 'a' && ch <= 'z') printf("%c", ch - 32);
	else if (ch >= 'A' && ch <= 'Z') printf("%c", ch + 32);
	else printf("none");
	return 0;
}
int main_5_0_5() {
	int num;
	scanf("%d", &num);
	if (num % 30 == 0) printf("A");
	else if (num % 6 == 0) printf("B");
	else if (num % 10 == 0)printf("C");
	else if (num % 15 == 0)printf("D");
	else if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0) printf("E");
	else printf("N");
	return 0;
}
int main_5_0_6() {
	int num[3],tmp;
	for (int i = 0; i < 3; i++) scanf("%d", &num[i]);
	for (int i = 0; i < 2; i++) if (num[i + 1] > num[i]) {
		tmp = num[i];
		num[i] = num[i + 1];
		num[i + 1] = tmp;
	}
	for (int i = 0; i < 2; i++) if (num[i + 1] > num[i]) {
		tmp = num[i];
		num[i] = num[i + 1];
		num[i + 1] = tmp;
	}
	printf("%d %d", num[0], num[2]);
	return 0;
}
int main_5_0_7() {
	int a = 2;
	if (a = 3) printf("%d", a);
	a = 0;
	printf("%d", a);

	return 0;
}