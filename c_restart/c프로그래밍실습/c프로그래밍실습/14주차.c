#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
// #include<string.h>
#include<time.h>
/*
strlen() : ����
strcpy(a,b) : a�� b�� ����
strcat(a,b) : a �ڿ� b�� ����
strcmp(a,b) : s1�� ����
b = atoi,l,f(a): ���� ���� ���� ���ڸ� ���ڷ� ��ȯ
*/
struct reserve {
	int id,price;
	char grad[4];
};

int main() {
	int n, m, num = 0, a, b, max = 0, count[100] = { 0, };
	double dd;
	char tmp[105],**store= NULL,ttmp[105],x[124],**y;
	scanf("%d %s", &n, &x); getchar();
	y = (char**)malloc(sizeof(char*) * n);
	for (int i = 0; i < n; i++) {
		gets(tmp);
		y[i] = (char*)malloc(sizeof(char) * (strlen(tmp)));
		strcpy(y[i], tmp);
		for (int j = 0; j < strlen(y[i]); j++) {
			if (strncmp(&y[i][j], x, strlen(x)) == 0) {
				count[i]++;
				j += strlen(x);
				j--;
			}
		}
		if (count[i] > count[max]) max = i;
	}
	if (count[max] == 0) printf("NONE");
	else printf("%s", y[max]);



	for (int i = 0; i < n; i++) free(y[i]);
	free(y);

}