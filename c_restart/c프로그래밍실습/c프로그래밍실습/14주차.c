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