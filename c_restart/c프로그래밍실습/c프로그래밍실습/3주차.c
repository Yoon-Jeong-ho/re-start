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

	scanf("%d", &N); //정수입력
	num = (N%3==0 && N %5  == 0)*15 + // 15의 배수만 찾기
		(N % 3 == 0 && N % 5 != 0) * 3 +  // 3의 배수만 찾기
		(N % 3 != 0 && N % 5 == 0) * 5 +  // 5의 배수만 찾기
		(N % 3 != 0 && N % 5 != 0) * N; // 3,5의 배수도 아닌 정수의 값(N) num에 넣기

	printf("%d is a multiple of %d.", N, num);
	
	return 0;
}

int main_4_0_2() {
	int year;
	char day='C';
	scanf("%d", &year);
	day = (year % 4 == 0 && year % 100 != 0) ? 'L' : 'C';//4로 나누어 떨어지고, 100으로는 안 나누어 떨어지는 년도
	day = year % 400 == 0 ? 'L' : 'C'; //위의 식에서 100으로 나누어 떨어진 숫자들 중에 400으로 나누어 떨어지는 숫자 모음
	
	printf("%c", day);
	return 0;
}

int main_4_0_3() {
	int num1, num2, num3;
	char result;
	scanf("%d %d %d", &num1, &num2, &num3);
	num1 /= 100; //백의 자리 구하기
	num2 /= 100;
	num3 /= 100;
	result = (num1 == num2 || num2 == num3 || num1 == num3) ? 'D' : 'S'; //두가지와 세가지 모두 같은 경우를 일단 먼저 'D'로 둔다
	result = (num1 == num2 && num2 == num3) ? 'T' : result; // 여기서 세가지가 모두 같은 경우를 'T'로 두어서 두가지가 같은 경우와 차별점을 둔다
	printf("%c", result);

	return 0;
}

int main_4_0_4() {
	int num, result = 0,a;
	scanf("%d", &num);
	a = num % 10; //a라는 변수에 입력받은 수 1의 자리 넣기
	result = a * 1000; // 1의자리를 천의 자리로 바꾸기
	a = num / 10 % 10; //a라는 변수에 입력받은 수 10의 자리 넣기
	result = result + a * 100; // 입력받은 10의자리 100의 자리로 바꾸기
	a = num / 100 % 10;//a라는 변수에 입력받은 수 100의 자리 넣기
	result = result + a * 10; // 입력받은 100의자리 10의자리로 바꾸기
	a = num / 1000 % 10; // 입력받은 수의 1000의 자리 a에 넣기
	result = result + a; //1000의자리 수 1의 자리에 넣기
	result = result - num; // 빼서 결과값 만들기
	result = result > 0 ? result : -result; // 0보다 크면 원래값, -값이면 - 붙여서 양수 만들기
	printf("%d", result);
	return 0;
}

int main_4_0_5() {
	int num,num1, num2, num3, result;
	scanf("%d", &num);
	num1 = num % 10; // 1의자리
	num2 = num / 10 % 10;  // 10의자리
	num3 = num / 100 % 10; // 100의자리
	result = (num1 == num2 || num2 == num3 || num1 == num3) ? 2 : 1; //두가지와 세가지 모두 같은 경우를 일단 먼저 2로 둔다
	result = (num1 == num2 && num2 == num3) ? 3 : result; // 여기서 세가지가 모두 같은 경우를 3로 두어서 두가지가 같은 경우와 차별점을 둔다
	printf("%d", result);

	return 0;
}

int main_04_0_05() {
	int num1, num2, num3,result;
	scanf("%d %d %d", &num1, &num2, &num3);
	result = ((num1 > num2 && num1 < num3) || (num1 < num2&& num1 > num3)) ? num1 : 0; // 1num이 중앙값인경우 좌우 값을 2,3 번갈아서 한다
	result = ((num1 > num2 && num2 > num3) || (num1 < num2&& num2 < num3)) ? num2 : result;// 2num이 중앙값인경우 좌우 값을 1,3 번갈아서 한다 아닐 경우 이전의 결과값을 그대로 가지고 온다
	result = ((num3 > num2 && num1 > num3) || (num3 < num2&& num1 < num3)) ? num3 : result;// 3num이 중앙값인경우 좌우 값을 2,1 번갈아서 한다 아닐 경우 이전의 결과값을 그대로 가지고 온다
	printf("%d", result); // 출력
	return 0;
}