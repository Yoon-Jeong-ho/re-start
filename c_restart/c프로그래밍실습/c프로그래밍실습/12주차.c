#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main_938761827412() {
	char x[100],y[100],tmp,result[100];
	int c = 0, n = 0, same, m, now, prev = -1, count = 0, max=0;
	for (int i = 0; i < 26; i++) {
		scanf("%c", &tmp);
		if (tmp == '!') break;
		x[c++] = tmp;
		same = 0;
		for (int j = 0; j < n; j++) {
			if (y[j] == x[i]) same = 1;
		}
		if (same == 0)y[n++] = x[i];
	}
	scanf("%d", &m);
	for (int i = 0; i < n; i++) {
		printf("%c", y[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++) {
		if (y[i] >= 'a' && y[i] <= 'z') { // 소문자
			y[i] = y[i] + m - 'a' + 'A';
			if (y[i] > 'Z') y[i] = y[i] - 'Z' + 'A' -1;
			now = 1;
		}
		else if (y[i] >= 'A' && y[i] <= 'Z') { //대문자
			y[i] = y[i] + m - 'A' + 'a';
			if (y[i] > 'z') y[i] = y[i] - 'z' + 'a' -1;
			now = 2;
		}
		if (now * prev == 2) {
			count++;
			if (count > max) {
				max = count;
				for (int j = 0; j < max + 1; j++) {
					result[j] = y[i - max+j];
				}
			}
		}
		else count = 0;
		prev = now;
	}
	for (int i = 0; i < n; i++) {
		printf("%c", y[i]);
	}
	printf("\n");
	if (max == 0) printf("none\n");
	else {
		for (int i = 0; i < max + 1; i++) {
			printf("%c", result[i]);
		}
	}
	return 0;
}

int reverse_num(int n);
int is_palindromic(int n);
int del_digit(int n, int t);

int main_123126() {
	int n,t;
	scanf("%d %d", &n, &t);
	printf("%d %d %d %d", n, reverse_num(n), is_palindromic(n), del_digit(n, t));
	return 0;
}

int reverse_num(int n) {
	int result=0;
	while (n > 0) {
		result = n % 10 + result * 10;
		n /= 10;
	}
	return result;
}
int is_palindromic(int n) {
	int num;
	num = reverse_num(n);
	if (num == n) return 1;
	else return 0;
}
int del_digit(int n, int t) {
	int count = 0, num = 0, x[10];
	if (is_palindromic(n) == 1) {
		num = n;
		while (num > 0) {
			count++;
			num /= 10;
		}
		num = 0;
		if (count < t * 2) { // 중앙값 하나만 빼야되는 경우
			for (int i = 0; i < count; i++) {
				if (i == t - 1) {
					n /= 10;
					continue;
					
				}
				num = num * 10 + n % 10;
				n /= 10;
			}
		}
		else { // 두개 빼야하는 경우
			for (int i = 0; i < count; i++) {
				if (i == t - 1 || i == count - t) {
					n /= 10;
					continue;
				}
				num = num * 10 + n % 10;
				n /= 10;
			}
		}
	}
	else { // 600
		num = n; // 600
		while (num > 0) {
			x[count++] = num % 10;
			num /= 10; // 0 0 6
		}
		num = 0;
		for (int i = 0; i < count; i++) { // 006
			if (i == count - t) continue; 
			num = num * 10 + x[count - i - 1]; // 6 0 0 
		}
	}
	return num;
}

char decrypt(char ch, int m);
char encrypt(char ch, int m);

int main_12746182741() {
	char c,tmp, x[101];
	int m,count = 0,n;
	while (1) {
		scanf("%c", &tmp);
		if (tmp == '*')break;
		x[count++] = tmp;
	}
	scanf("%d %d", &m,&n);
	for (int i = 0; i < count; i++) {
		x[i] = decrypt(x[i], m);
		printf("%c", x[i]);
	}
	printf("\n");
	for (int i = 0; i < count; i++) {
		printf("%c", encrypt(x[i], n));
	}
	return 0;
}


char decrypt(char ch, int m) {
	if(ch >= 'a' && ch <= 'z') {
		ch = ch - m;
		if (ch < 'a') ch = ch - 'a' + 'z'+1;
	}
	else if ( ch >= 'A' && ch<='Z'){
		ch = ch - m;
		if (ch < 'A') ch = ch - 'A' + 'Z'+1;
	}
	return ch;
}
char encrypt(char ch, int m) {
	if (ch >= 'a' && ch <= 'z') {	
		return (ch - 'a' + m) % 26 + 'a';
	}
	else if (ch >= 'A' && ch <= 'Z') {
		return (ch - 'A' + m) % 26 + 'A';
	}
	return ch;
}

int main_23972387() {
	int n, m[100], tmp, count = 0, c = 0, max = 0,result[100];
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		if (tmp > 0) m[count++] = tmp;
	}
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count ; j++) {
			if (m[i] > m[j]) {
				tmp = m[i];
				m[i] = m[j];
				m[j] = tmp;
			}
		}
	}
	
	for (int i = 0; i < count; i++) {
		printf("%d ", m[i]);
		if (m[i] % 2 == 0) c = 0;
		else {
			c++;
			if (c > max) {
				max = c;
				for (int j = 0; j < max; j++) result[j] = m[i - max+j+1];
			}
		}
	}
	if (max > 0) {
		printf("\n");
		for (int i = 0; i < max; i++) printf("%d ", result[i]);
		printf("\n%d", max);
	}
	else printf("\nnone");
}


int main() {
	int n, m[100],prev=0,result[100], c = 0, max = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &m[i]);
	}
	for (int i = 1; i < n; i++) {
		if (m[i - 1] < m[i]) {
			c++;
			if (c > max) {
				max = c;
				for (int j = 0; j < max+1; j++) {
					result[j] = m[i - max + j];
				}
			}
		}
		else c = 0;
	}
	for (int i = 0; i < max+1; i++)printf("%d ", result[i]);
	return 0;
}