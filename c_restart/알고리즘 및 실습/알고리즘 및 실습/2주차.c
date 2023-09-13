#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//#include <Windows.h>

int main() {
	int n, * num, tmp;
	scanf("%d", &n);
	num = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) scanf("%d", &num[i]);
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0; j--) {
			if (num[j] < num[j - 1]) {
				tmp = num[j];
				num[j] = num[j - 1];
				num[j - 1] = tmp;
			}
			else break;
		}
	}
	for (int i = 0; i < n; i++) printf(" %d", num[i]);
	return 0;
}