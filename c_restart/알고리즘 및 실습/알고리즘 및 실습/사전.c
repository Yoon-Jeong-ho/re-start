#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main_3() {
	int a, b, k,n=0;
	char c;
	scanf("%d %d %d", &a, &b, &k); getchar();
	
	for (int i = 0; i < k; i++) {
		n = (a + b) / 2;
		scanf("%c", &c);
		if (c == 'Y') a = n+1;
		else b = n;
	}
	n = (a + b) / 2;
	printf("%d", n);
}


int findkey(int*, int, int,int);

int main() {
	int n, k,*num;
	scanf("%d %d", &n, &k);
	num = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)scanf("%d", &num[i]);
	printf("%d", findkey(num, 0, n - 1, k));

	return 0;
}

int findkey(int*num, int p, int q, int k) {
	int m = (p + q) / 2;
	if (num[q] < k) return q;
	if (num[p] > k) return p - 1;
	if (m==p) return p;
	if (num[m] < k) return findkey(num, m, q, k);
	else if (num[m] > k)  return findkey(num, p, m, k);
	else return m;
}

int main_1() {
	int n, k, * num,p=0,q,m;
	scanf("%d %d", &n, &k);
	num = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)scanf("%d", &num[i]);
	q = n - 1;
	while (p < q) {
		m = (p + q) / 2;
		if (num[m] > k)q = m - 1;
		else if (num[m] < k) p = m + 1;
		else { p = m; break; }
	}
	printf("%d", p);
	return 0;
}