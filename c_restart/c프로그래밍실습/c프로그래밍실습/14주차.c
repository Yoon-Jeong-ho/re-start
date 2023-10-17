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
//
//typedef struct {
//	char a[100];
//	long b,c;
//}node;
struct person {
	char a[100];
	long b, c;
};
void swap(struct person* p, struct person* q);
int main() {
	int n, m;
	struct person a[100];
	scanf("%d %d", &n, &m);

}
void swap(struct person* p, struct person* q) {
	struct person r;
	r = *p; *p = *q; *q = r;
}