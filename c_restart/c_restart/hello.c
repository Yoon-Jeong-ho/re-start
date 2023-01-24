#include <stdio.h>

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
	float f = 46.5f;
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
	return 0;
}