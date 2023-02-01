#define _CRT_SECURE_NO_WARNINGS
#define MAX 10000
#include <stdio.h>
#include <time.h>



struct friends {
	char * name;
	int age;

};

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

	struct friends kko;
	kko.name = "kkobbo";
	kko.age = 26;
	printf("name : %8s age : %d \n", kko.name, kko.age);

	struct friends yoon = {"jh", 25};
	printf("name : %8s age : %d \n", yoon.name, yoon.age);
	// 구조체 배열도 가능
	struct friends sp[2] = {
		{"young", 24} ,
		{"hea" , 22}
	};
	printf("name : %8s age : %d \n", sp[0].name, sp[0].age);
	printf("name : %8s age : %d \n", sp[1].name, sp[1].age);

	struct friends * heck;
	heck = &yoon;
	printf("name : %8s age : %d \n", (*heck).name, (*heck).age); // *의 지정을 위해 괄호 필수!
	printf("name : %8s age : %d \n", heck->name, heck->age);   // 이렇게 변동도 가능!

	//typedef float 실수 ; typedef는 이미 있는 것을 다른 이름에도 적용할 때 사용 (실수 i = 3.23f) 로 사용 가능
	typedef struct friends 친구정보;
	친구정보 상;
	상.name = "huk";
	상.age = 25;
	printf("name : %8s age : %d \n", 상.name, 상.age);

	// 파일 입출력 > fputs, fgets, fprintf, fscanf
	char line[MAX];
	FILE *file = fopen("C:\\Users\\k\\OneDrive\\문서\\re-start\\c_restart\\test.txt","wb");
	if (file == NULL) {
		printf("열기 실패");
		return 1;
	}
	fputs("이게 잘 저장이 될까? \n", file);
	fputs("저장이 되면 밑에 나올꺼야  \n", file);
	fclose(file);
	FILE* files = fopen("C:\\Users\\k\\OneDrive\\문서\\re-start\\c_restart\\test.txt", "rb");
	while (fgets(line, MAX, files) != NULL) {
		printf("%s", line);
	}
	fclose(files);




	return 0;
}

void p(int num) {

	printf("숫자는 %d입니다", num);

}	

void qwer(int *c) {
	c[2] = 4;
}