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
int numchar(char *c, char test,int num1, int num2); // ���ڿ�, �� ����, �ݺ��� Ƚ��, ���� Ƚ��

int main_03_01() {
	int N;
	scanf("%d", &N);//N�� �Է¹ޱ�
	printf("%d", sum(N));
	return 0;
}

int main_03_02() {
	int num;
	scanf("%d", &num); // num�� �Է¹ޱ�
	AA_03_02(num); // �Լ� ȣ��
	return 0;
}

int main_03_03() {
	int num;
	scanf("%d", &num); //num�� �Է¹ޱ�
	AA_03_03(num); // �Լ� ȣ��
	return 0;
}

int main_03_04() {
	int N,num[20], max = 0;
	scanf("%d", &N); // N �Է¹ޱ�
	if (N > 20) exit; // 20���ϸ� �׳� ��
	else {
		for (int i = 0; i < N; i++) {
			scanf("%d", &num[i]); // ���� �Է�
		}
		printf("%d", bignum(N, num,max)); // max�� ����Ʈ
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
	scanf("%d %d", &num1, &num2); // �Է¹ޱ�
	printf("%d", gcd(num1, num2)); // �� ���� gcd�� �־ ���ϰ� ����ϱ�
	return 0;
}
int main_03_07() {
	char c[100],tmp,test;
	scanf("%s %c", c,&test);//���ڿ� �Է�
	printf("%d",numchar(c, test, 0, 0));
	return 0;
}

int sum(int n) {
	if (n <= 1) return  1; // 1�����̸� ��� ������.
	else return n + sum(n - 1); // 1���� ũ�� n-1���� ��ͷ� �ѹ� �� �����鼭 n���� ��� ���Ѵ�.
}

int AA_03_02(int N) {
	if (N < 10) printf("%d\n",N);
	else {
		AA_03_02(N / 10);// ������ 10�̻��̹Ƿ� �ڸ��� �ϳ��� ���ּ� ����Ͽ� ������.
		printf("%d\n", N % 10);// ���� ��� �ϰ��� ���ƿ� �� ����� �� �ֵ��� �ڿ� ����
	}

}

int AA_03_03(int num) {
	if (num < 10) printf("%d\n", num);
	else {
		printf("%d\n", num % 10);// �����ڸ� ���� ����� �ؾ� �ϹǷ� ����Ʈ�� �ϰ� ��͸� ��Ų��.
		AA_03_03(num / 10);// ������ 10�̻��̹Ƿ� �ڸ��� �ϳ��� ���ּ� ����Ͽ� ������.		
	}

}

int bignum(int N,int* num, int max) {
	if (N == 1) {
		if (num[N - 1] > max) return num[N - 1]; // max�� ȣ���ϱ�
		else return max;
	}
	else {
		if (num[N - 1] > max) bignum(N - 1, num, num[N - 1]); // N�ϳ��� �ٿ����鼭 max �� �ٲٸ鼭 ���
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
	if (num2 == 0) return num1; // ������ �� ����ϱ�
	else gcd(num2, num1 % num2);
}
int numchar(char* c, char test, int num1, int num2) {  // ���ڿ�, �� ����, �ݺ��� Ƚ��, ���� Ƚ��
	if (c[num1] == '\0') return num2; // ���ڿ� ������ ���� Ƚ�� �������ֱ�
	else if (c[num1] == test) numchar(c, test, ++num1, ++num2); // ������ ���� ������ ���� Ƚ�� �÷��ְ� ���
	else numchar(c, test, ++num1, num2); // �����Ѱ� ������ Ƚ�� �״�� �ΰ� ���
}