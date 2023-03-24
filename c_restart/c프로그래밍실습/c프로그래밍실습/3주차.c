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

int main_4_7() {
	char a;
	scanf("%c", &a);
	printf("%d",a>= 'A'&& a<='z');
	return 0;
}

int main_4_0_1() {
	int N, num = 1; 

	scanf("%d", &N); //�����Է�
	num = (N%3==0 && N %5  == 0)*15 + // 15�� ����� ã��
		(N % 3 == 0 && N % 5 != 0) * 3 +  // 3�� ����� ã��
		(N % 3 != 0 && N % 5 == 0) * 5 +  // 5�� ����� ã��
		(N % 3 != 0 && N % 5 != 0) * N; // 3,5�� ����� �ƴ� ������ ��(N) num�� �ֱ�

	printf("%d is a multiple of %d.", N, num);
	
	return 0;
}

int main_4_0_2() {
	int year;
	char day='C';
	scanf("%d", &year);
	day = (year % 4 == 0 && year % 100 != 0) ? 'L' : 'C';//4�� ������ ��������, 100���δ� �� ������ �������� �⵵
	day = year % 400 == 0 ? 'L' : 'C'; //���� �Ŀ��� 100���� ������ ������ ���ڵ� �߿� 400���� ������ �������� ���� ����
	
	printf("%c", day);
	return 0;
}

int main_4_0_3() {
	int num1, num2, num3;
	char result;
	scanf("%d %d %d", &num1, &num2, &num3);
	num1 /= 100; //���� �ڸ� ���ϱ�
	num2 /= 100;
	num3 /= 100;
	result = (num1 == num2 || num2 == num3 || num1 == num3) ? 'D' : 'S'; //�ΰ����� ������ ��� ���� ��츦 �ϴ� ���� 'D'�� �д�
	result = (num1 == num2 && num2 == num3) ? 'T' : result; // ���⼭ �������� ��� ���� ��츦 'T'�� �ξ �ΰ����� ���� ���� �������� �д�
	printf("%c", result);

	return 0;
}

int main_4_0_4() {
	int num, result = 0,a;
	scanf("%d", &num);
	a = num % 10; //a��� ������ �Է¹��� �� 1�� �ڸ� �ֱ�
	result = a * 1000; // 1���ڸ��� õ�� �ڸ��� �ٲٱ�
	a = num / 10 % 10; //a��� ������ �Է¹��� �� 10�� �ڸ� �ֱ�
	result = result + a * 100; // �Է¹��� 10���ڸ� 100�� �ڸ��� �ٲٱ�
	a = num / 100 % 10;//a��� ������ �Է¹��� �� 100�� �ڸ� �ֱ�
	result = result + a * 10; // �Է¹��� 100���ڸ� 10���ڸ��� �ٲٱ�
	a = num / 1000 % 10; // �Է¹��� ���� 1000�� �ڸ� a�� �ֱ�
	result = result + a; //1000���ڸ� �� 1�� �ڸ��� �ֱ�
	result = result - num; // ���� ����� �����
	result = result > 0 ? result : -result; // 0���� ũ�� ������, -���̸� - �ٿ��� ��� �����
	printf("%d", result);
	return 0;
}

int main_4_0_5() {
	int num,num1, num2, num3, result;
	scanf("%d", &num);
	num1 = num % 10; // 1���ڸ�
	num2 = num / 10 % 10;  // 10���ڸ�
	num3 = num / 100 % 10; // 100���ڸ�
	result = (num1 == num2 || num2 == num3 || num1 == num3) ? 2 : 1; //�ΰ����� ������ ��� ���� ��츦 �ϴ� ���� 2�� �д�
	result = (num1 == num2 && num2 == num3) ? 3 : result; // ���⼭ �������� ��� ���� ��츦 3�� �ξ �ΰ����� ���� ���� �������� �д�
	printf("%d", result);

	return 0;
}

int main_04_0_05() {
	int num1, num2, num3,result;
	scanf("%d %d %d", &num1, &num2, &num3);
	result = ((num1 > num2 && num1 < num3) || (num1 < num2&& num1 > num3)) ? num1 : 0; // 1num�� �߾Ӱ��ΰ�� �¿� ���� 2,3 �����Ƽ� �Ѵ�
	result = ((num1 > num2 && num2 > num3) || (num1 < num2&& num2 < num3)) ? num2 : result;// 2num�� �߾Ӱ��ΰ�� �¿� ���� 1,3 �����Ƽ� �Ѵ� �ƴ� ��� ������ ������� �״�� ������ �´�
	result = ((num3 > num2 && num1 > num3) || (num3 < num2&& num1 < num3)) ? num3 : result;// 3num�� �߾Ӱ��ΰ�� �¿� ���� 2,1 �����Ƽ� �Ѵ� �ƴ� ��� ������ ������� �״�� ������ �´�
	printf("%d", result); // ���
	return 0;
}