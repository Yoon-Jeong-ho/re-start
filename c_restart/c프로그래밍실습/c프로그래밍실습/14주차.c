#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct {
	//node* next;
	int num;
	char name[100];
}node;


int main() {
	node a[100];
	int n;
	char tmp[100];
	int tmpn;
	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {
		gets(a[i].name);
		scanf("%d", &a[i].num);
		getchar();
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (strcmp(a[i].name, a[j].name) > 0) {
				strcpy(tmp, a[i].name);
				strcpy(a[i].name, a[j].name);
				strcpy(a[j].name, tmp);
				tmpn = a[i].num;
				a[i].num = a[j].num;
				a[j].num = tmpn;

			}
			if (strcmp(a[i].name, a[j].name) == 0 && a[i].num > a[j].num) {
				tmpn = a[i].num;
				a[i].num = a[j].num;
				a[j].num = tmpn;
			}

		}
	}
	for (int i = 0; i < n; i++) {
		printf("%s %d\n", a[i].name, a[i].num);
	}
	return 0;
}
