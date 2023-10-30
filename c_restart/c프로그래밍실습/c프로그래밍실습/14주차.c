#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/*
strlen() : 길이
strcpy(a,b) : a에 b를 복사
strcat(a,b) : a 뒤에 b를 붙임
strcmp(a,b) : s1의 순위
b = atoi,l,f(a): 숫자 형에 따른 문자를 숫자로 변환
*/
typedef struct {
	char *name;
	int k, e, m,num,result,cnt;
	float mean;
}student;
int main() {
	int n,num1=0,numb=0, **nn,m;
	float  * num, max = -99999;
	student* st,ttmp;

	char** c,a = 'a', b,tmp[105];
	scanf("%d", &n); getchar();

	st = (student*)malloc(sizeof(student) * (n));
	if (st == NULL) {
		printf("False");
		return -1;
	}
	for (int i = 0; i < n; i++) {
		scanf("%s", tmp); getchar();
		st[i].name = (char*)malloc(sizeof(char) * (strlen(tmp) + 1));
		strcpy(st[i].name, tmp);
		num1 = 0;
		numb = 0;
		m = 0;
		for (int j = 0; j < strlen(tmp); j++) {
			if (tmp[j] == 'i' || tmp[j] == 'a' || tmp[j] == 'e' || tmp[j] == 'o' || tmp[j] == 'u' || tmp[j] == 'I' || tmp[j] == 'A' || tmp[j] == 'E' || tmp[j] == 'O' || tmp[j] == 'U') numb++;
			else if (tmp[j] >= '0' && tmp[j] <= '9') {
				m = tmp[j] - '0';
			}
			else num1++;
		}
		st[i].cnt = num1;
		st[i].num = m;
		st[i].result = num1 * m;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (st[i].result < st[j].result) {
				ttmp = st[i];
				st[i] = st[j];
				st[j] = ttmp;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%s \n", st[i].name);
	}
	for (int i = 0; i < n; i++) {
		free(st[i].name);
	}	
	free(st);

	return 0;
}