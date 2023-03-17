#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main_3_3() {

	double a, b;
	scanf("%lf %lf", &a, &b);
	printf("area = %.2f", a * b);

	return 0;
}

int main_3_4() {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	printf("purchase 1:%5d won\n",a);
	printf("purchase 2:%5d won\n", b);
	printf("purchase 3:%5d won\n", c);
	return 0;
}

int main_3_5() {
	double a;
	scanf("%lf", &a);
	printf("rounded up to %d", (int)(a + 0.5));
	return 0;
}

int main_3_6() {
	char a, b;
	int year, month, d;
	scanf("%d%c%d%c%d", &year, &a, &month, &b, &d);
	printf("year %04d month %02d date %02d", year, month, d);
	return 0;
}

int main_4_1() {
	int a, b, c, d, e;
	scanf("%d", &a);
	printf("%dTTHO %dTHO %dHUN %dTEN %d",a/10000%10,a/1000%10,a/100%10,a/10%10,a%10);
	return 0;
}

int main_4_2() {
	int a;
	scanf("%d", &a);
	printf("%d:%d:%d",a/3600,a%3600/60,a%60%60);
	return 0;
}

int main_4_3() {
	int a;
	scanf("%d", &a);
	a = a / 100;
	printf("%d", a % 10);

	return 0;
}

int main_4_4() {
	int a;
	scanf("%d", &a);
	a = a + 500;
	a = a / 1000;
	a = a * 1000;
	printf("%d", a);

	return 0;
}

int main_4_5() {
	double n;
	scanf("%lf", &n);
	n = n / 6.28;
	n = n * n * 3.14;
	printf("%d", (int)(n + 0.5));
	return 0;
}

int main_4_6() {
	int N;
	scanf("%d", &N);
	printf("%d", N <= 30 && N >= 20);
	return 0;
}

int main() {
	char a;
	scanf("%c", &a);
	printf("%d",a>= 'A'&& a<='z');
	return 0;
}