#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	int tmp, a[10] = { 0 }, b[10] = { 0 }, n = 0, * p, c = 0,m=0,max,*q;
	p = a;
	while (1) {
		scanf("%d", &tmp);
		if (tmp == -1)break;
		*p = tmp;
		p++; n++;
	}
	p = b;
	while (1) {
		scanf("%d", &tmp);
		if (tmp == -1)break;
		*p = tmp;
		p++; m++;
	}
	for (q = a; q < a + n; q++) {
		for (p = q + 1; p < a + n; p++) {
			if (*q <= *p) { tmp = *p; *p = *q; *q = tmp; }
		}
	}
	for (q = b; q < b + m; q++) {
		for (p = q + 1; p < b + m; p++) {
			if (*q <= *p) { tmp = *p; *p = *q; *q = tmp; }
		}
	}
	p = a; q = b; c = 0;
	while (1) {
		if (c == n) break;
		if (*p >= *q) { printf("%d ", *p); p++; }
		else { printf("%d ", *q); q++; }
		c++;
	}
	printf("\n");
	p = a+n-1; q = b+m-1; c = 0;
	while (1) {
		if (c == m) break;
		if (*p >= *q) { printf("%d ", *q); q--; } 
		else { printf("%d ", *p); p--; }
		c++;
	}
}

