#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/*
strlen() : ����
strcpy(a,b) : a�� b�� ����
strcat(a,b) : a �ڿ� b�� ����
strcmp(a,b) : s1�� ����
b = atoi,l,f(a): ���� ���� ���� ���ڸ� ���ڷ� ��ȯ
*/
struct parking_info {
	char goods, longs;
	int num, pnum, date, time;
	double price;

}parking_info;

int main() {
	int n,tmp,num[100],m=0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		if (tmp < 1)continue;
		num[m++] = tmp;
	}
	if (m % 2 == 0) {
		for (int i = 0; i < m; i++) {
			tmp = i;
			for (int j = i + 1; j < m; j++) {
				if (num[tmp] < num[j]) tmp = j;
			}
			if (tmp == i) continue;
			n = num[tmp];
			num[tmp] = num[i];
			num[i] = n;
		}
	}
	else{
		for (int i = 0; i < m; i++) {
			tmp = i;
			for (int j = i + 1; j < m; j++) {
				if (num[tmp] > num[j]) tmp = j;
			}
			if (tmp == i) continue;
			n = num[tmp];
			num[tmp] = num[i];
			num[i] = n;
		}
	}
	n = 0;
	tmp = 0;
	printf("%d\n", m);
	for (int i = 0; i < m; i++) {
		printf("%d ", num[i]);
		if (num[i] % 2 == 1) n++;
		else n = 0;
		if (n > tmp) tmp = n;
	}
	printf("\n%d", tmp);
}