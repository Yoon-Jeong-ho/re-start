#include <stdio.h>
#include <time.h>
void p(int num);
void qwer (int *a);

int main(void)
{
	int age = 14;
	
	//printf("awer");
	/* �ּ�ó���ϴ� ��
	adsf
	asdf
	asdfad
	dssds		
	*/
	/*float f = 46.5f;
	double d = 4.4258;
	printf("%d\n%.2f\n%lf\n",age,f,d);
	const int cons = 1; //c�� ������ �� ���� ����� ����
	int a, b, c;
	char str[99];
	scanf_s("%d %d %d", &a, &b, &c);
	scanf_s("%s", str, sizeof(str));
	printf("%d, %d, %d, %s\n",a, b, c, str);

	for (int i = 1; i  <11; i++) 
	{
		printf("%d\n", i);
	}
	printf("*��� ��?");
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

	printf("c���� �ּҴ� &�� ���̸� �ȴ�. age�� �ּҴ� %d�Դϴ�.\n", &age);

	int *a;
	a = &age;
	printf("%d %d %d\n",age,a,*a); // age ��, age �ּ�, age ��
	*a = *a - 1;
	printf("%d %d %d\n", age, a, *a);  // &�� �ּҷ� *�� ������
	int b = a;
	printf("%d %d %d %d %d\n",a,b, &a, &b,*a); // age�ּ�, a�� ���� ���� b, a�ּ�(age�ּ��� �ּ�), b�� �ּ� ���� a�� ���Ƶ� �ּҴ� �ٸ�,  age)

	int c[3] = { 1,2,3 };
	qwer(c);
	printf("%d\n", c[2]);

	// ������ �迭 int arr[4][2]�� 2�������� 4���ִ°� , arr[4][2][3] �� 3��¥���� 2���ְ� �̰��� 4���ִ°� ��ǥ������ ����(4,2,3)

	int d[2][4][8];
	d[0][1][2] = 3;
	printf("%d %d %d %d\n", *d,d,d[0][0][0], d[0][1][2]);



	return 0;
}

void p(int num) {

	printf("���ڴ� %d�Դϴ�", num);

}	

void qwer(int *c) {
	c[2] = 4;
}