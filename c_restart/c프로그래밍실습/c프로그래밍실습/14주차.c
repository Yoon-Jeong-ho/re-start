#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int check_w(char* p, char* q);

int main() {
	int n,m, num[20] = {0},max=0;
	char a[20][200];
	scanf("%d %d", &n,&m); getchar();
	for(int i = 0 ; i < n ; i++)gets(a[i]); // ���ڿ� �Է¹ޱ�
	for (int i = 0; i < n; i++) {
		num[i] = check_w(a[i], a[i]+m); // �Լ��� �迭�� ����
		printf("%d ", num[i]);
	}
	while (1) {
		max = 0;
		for (int i = 0; i < n; i++) { // ū�� ã��
			if (num[i] > max) max = num[i];
		}
		if (max == 0) break;// max�� ��� 0�̸� �ݺ��� ��
		for (int i = 0; i < n; i++) {//ū���� �տ��� ���� ����ϱ�
			if (num[i] == max) {
				printf("%s\n", a[i]);
				num[i] = 0;
			}
		}
	}
	return 0;
}
int check_w(char* p, char* q) {
	int sum = 0;
	for (p; p <= q; p++) {
		if (*p == '\0')break;
		if ((*p < 'a' || *p > 'z') && (*p < 'A' || *p > 'Z') && *p != ' ') { // ���ĺ��� ������ �ƴѰ��
			sum++; // �ϳ��� �ø���.
		}
	}
	return sum;
}
