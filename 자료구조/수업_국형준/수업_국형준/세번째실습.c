#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

int sum(int N);
int AA_03_02(int N);
int AA_03_03(int num);
int bignum(int N, int* num,int max);
void hanoi(int N);
void rhanoi(int N, char from, char aux, char to);
int gcd(int num1, int num2);
int numchar(char *c, char test,int num1, int num2); // 문자열, 고를 문자, 반복한 횟수, 나온 횟수

int main_03_01() {
	int N;
	scanf("%d", &N);//N값 입력받기
	printf("%d", sum(N));
	return 0;
}

int main_03_02() {
	int num;
	scanf("%d", &num); // num값 입력받기
	AA_03_02(num); // 함수 호출
	return 0;
}

int main_03_03() {
	int num;
	scanf("%d", &num); //num값 입력받기
	AA_03_03(num); // 함수 호출
	return 0;
}

int main_03_04() {
	int N,num[20], max = 0;
	scanf("%d", &N); // N 입력받기
	if (N > 20) exit; // 20이하면 그냥 끝
	else {
		for (int i = 0; i < N; i++) {
			scanf("%d", &num[i]); // 숫자 입력
		}
		printf("%d", bignum(N, num,max)); // max값 프린트
	}
	
	return 0;
}

int main_03_05() {
	int N;
	scanf("%d", &N);
	hanoi(N);
	return 0;
}

int main_03_06() {
	int num1, num2;
	scanf("%d %d", &num1, &num2); // 입력받기
	printf("%d", gcd(num1, num2)); // 두 숫자 gcd에 넣어서 리턴값 출력하기
	return 0;
}
int main_03_07() {
	char c[100],tmp,test;
	scanf("%s %c", c,&test);//문자열 입력
	printf("%d",numchar(c, test, 0, 0));
	return 0;
}

int sum(int n) {
	if (n <= 1) return  1; // 1이하이면 재귀 끝난다.
	else return n + sum(n - 1); // 1보다 크면 n-1값을 재귀로 한번 더 돌리면서 n값을 계속 더한다.
}

int AA_03_02(int N) {
	if (N < 10) printf("%d\n",N);
	else {
		AA_03_02(N / 10);// 정수가 10이상이므로 자리수 하나를 없애서 재귀하여 보낸다.
		printf("%d\n", N % 10);// 값은 재귀 하고나서 돌아올 때 출력할 수 있도록 뒤에 적기
	}

}

int AA_03_03(int num) {
	if (num < 10) printf("%d\n", num);
	else {
		printf("%d\n", num % 10);// 일의자리 부터 출력을 해야 하므로 프린트를 하고 재귀를 시킨다.
		AA_03_03(num / 10);// 정수가 10이상이므로 자리수 하나를 없애서 재귀하여 보낸다.		
	}

}

int bignum(int N,int* num, int max) {
	if (N == 1) {
		if (num[N - 1] > max) return num[N - 1]; // max값 호출하기
		else return max;
	}
	else {
		if (num[N - 1] > max) bignum(N - 1, num, num[N - 1]); // N하나씩 줄여가면서 max 값 바꾸면서 재귀
		else bignum(N - 1, num, max);
	}
}

void hanoi(int N) {
	rhanoi(N, 'A', 'B', 'C');
}

void rhanoi(int N, char from, char aux, char to) {
	if (N == 1) {
		printf("%c %c\n", from, to);
		return 0;
	}
	rhanoi(N-1, from, to, aux);
	printf("%c %c\n", from, to);
	rhanoi(N - 1, aux, from, to);
}

int gcd(int num1, int num2) {
	if (num2 == 0) return num1; // 마지막 값 출력하기
	else gcd(num2, num1 % num2);
}
int numchar(char* c, char test, int num1, int num2) {  // 문자열, 고를 문자, 반복한 횟수, 나온 횟수
	if (c[num1] == '\0') return num2; // 문자열 끝나면 나온 횟수 리턴해주기
	else if (c[num1] == test) numchar(c, test, ++num1, ++num2); // 동일한 것이 있으면 나온 횟수 올려주고 재귀
	else numchar(c, test, ++num1, num2); // 동일한것 없으면 횟수 그대로 두고 재귀
}