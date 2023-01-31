#include <stdio.h>
#include <time.h>
void p(int num);
void qwer (int *a);

int main(void)
{
	int age = 14;
	
	//printf("awer");
	/* 주석처리하는 법
	adsf
	asdf
	asdfad
	dssds		
	*/
	/*float f = 46.5f;
	double d = 4.4258;
	printf("%d\n%.2f\n%lf\n",age,f,d);
	const int cons = 1; //c를 변경할 수 없게 상수로 설정
	int a, b, c;
	char str[99];
	scanf_s("%d %d %d", &a, &b, &c);
	scanf_s("%s", str, sizeof(str));
	printf("%d, %d, %d, %s\n",a, b, c, str);

	for (int i = 1; i  <11; i++) 
	{
		printf("%d\n", i);
	}
	printf("*몇번 해?");
	scanf_s("%d", &a);
	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= i; j++) {
			printf("*");

		}
		printf("\n");

	}*/
	// %% : and || : or  
	// if, else if, else

	p(3);

	printf("c에서 주소는 &를 붙이면 된다. age의 주소는 %d입니다.\n", &age);

	int *a;
	a = &age;
	printf("%d %d %d\n",age,a,*a); // age 값, age 주소, age 값
	*a = *a - 1;
	printf("%d %d %d\n", age, a, *a);  // &는 주소로 *은 값으로
	int b = a;
	printf("%d %d %d %d %d\n",a,b, &a, &b,*a); // age주소, a와 같은 값인 b, a주소(age주소의 주소), b의 주소 값은 a와 같아도 주소는 다름,  age)

	int c[3] = { 1,2,3 };
	qwer(c);
	printf("%d\n", c[2]);

	// 다차원 배열 int arr[4][2]는 2개공간이 4개있는것 , arr[4][2][3] 는 3개짜리가 2개있고 이것이 4개있는것 좌표축으로 생각(4,2,3)

	int d[2][4][8];
	d[0][1][2] = 3;
	printf("%d %d %d %d\n", *d,d,d[0][0][0], d[0][1][2]);



	return 0;
}

void p(int num) {

	printf("숫자는 %d입니다", num);

}	

void qwer(int *c) {
	c[2] = 4;
}