//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//
//char atoA(char c) {
//	if (c >= 'A' && c <= 'Z') return c;
//	else return c - 32;
//}
//
//
//int main_876536() {
//	char c;
//	int m;
//	scanf("%d", &m);
//	getchar();
//	for (int i = 0; i < m; i++) {
//		scanf("%c", &c);
//		printf("%c", atoA(c));
//	}
//	return 0;
//}
//int add(int x, int y);
//int main_298736() {
//	int n;
//	scanf("%d", &n);
//	printf("%d", add(1, n));
//	return 0;
//}
//
//int add(int x, int y) {
//	if (x == y) return x;
//	else if (x + 1 == y) return x + y;
//	return x + y + add(x + 1, y - 1);
//}
//int sum(int a);
//int main_12976127() {
//	int a,result = 0;
//	scanf("%d", &a);
//	for (int i = 1; i <= a; i++) result += sum(i);
//	printf("%d", result);
//	return 0;
//}
//
//int sum(int a) {
//
//	return a * (a + 1) / 2;
//}
//int count_3(int n);
//int main_8318371() {
//	int n;
//	scanf("%d", &n);
//	printf("%d", count_3(n));
//
//	return 0;
//}
//int count_3(int n) {
//	int result = 0,m;
//	for (int i = 1; i <= n; i++) {
//		m = i;
//		while (m > 2) {
//			if (m % 10 == 3) result++;
//			m /= 10;
//		}
//	}
//	return result;
//}
//
//void print_prime(int n, int m);
//int is_prime(int c);
//int next_prime(int n, int m);
//int main_237628374() {
//	int n, m;
//	scanf("%d %d", &n, &m);
//	next_prime(n, m);
//	return 0;
//}
//
//void print_prime(int n, int m) {
//	int c = 0;
//	for (int i = 2; i <= n; i++) {
//		if (is_prime(i) == 1) {
//			printf(" %d", i);
//			c++;
//		}
//		if (c == m) {
//			printf("\n");
//			c = 0;
//		}
//	}
//}
//int is_prime(int c) {
//	int count = 0;
//	for (int i = 2; i < c; i++) {
//		if (c % i == 0) return 0;
//	}
//	return 1;
//}
//
//
//int next_prime(int n, int m) {
//	int count = 0;
//	while (count < m) {
//		if (is_prime(++n) == 1) {
//			count++;
//			printf(" %d",n);
//		}
//	}
//	return 0;
//}
//
//int reverse_num(int n);
//int del_dupnum(int n);
//int main_124124_4124124_24124() {
//	int n,num,max=0,result=0,m;
//	while (1) {
//		scanf("%d", &n);
//		num = n;
//		if (n < 0) break;
//		n = reverse_num(n);
//		n = del_dupnum(n);
//		printf(" %d", n);
//		m = num - n;
//		if (m < 0) m = -m;
//		if (result < m) {
//			max = num;
//			result = m;
//		}
//
//	}
//	printf("\n%d %d", max, result);
//	return 0;
//}
//
//
//int reverse_num(int n) {
//	int result = 0;
//	while (n > 0) {
//		result = result * 10 + n % 10;
//		n /= 10;
//	}
//	return result;
//}
//int del_dupnum(int n) {
//	int N[9],num, t = 0,tmp,flag = 0;
//	num = n;
//	while (num > 0) {
//		N[t++] = num % 10;
//		num /= 10;
//	}
//	for (int i = t - 1; i >= 0; i--) {
//		flag = 0;
//		for (int j = i+1; j < t; j++) {
//			if (N[i] == N[j]) flag = 1;
//		}
//		if (flag == 0) num = num * 10 + N[i];
//	}
//	return num;
//}