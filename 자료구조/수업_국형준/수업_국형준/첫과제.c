#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>

int sum(int n);

void ABC(int* num, int k);

void swap(int *a, int *b);

struct time {
	int hour;
	int min;
	int sec;
};

struct test {
	char name[9];
	int score;
};

int main_1() {
	int n, total = 0;
	scanf_s("%d", &n);
	for (int i = 1; i < n + 1; i++) total += sum(i);
	printf("%d", total);
	return 0;
}

int main_2() {
	int num[10];
	for (int i = 0; i < 10; i++) scanf_s("%d", &num[i]);
	for (int k = 0; k < 9; k++) ABC(num, k);
	for (int i = 0; i < 10; i++) printf(" %d", num[i]);
	return 0;
}

int main_3() {
	int num[50], N,a,b;
	scanf_s("%d", &N);
	for (int i = 0; i < N; i++) scanf_s("%d", &num[i]);
	scanf_s("%d %d", &a, &b);
	swap(&num[a], &num[b]);
	for (int i = 0; i < N; i++) printf(" %d", num[i]);
	return 0;
}

int main_4() {
	char str[100],tmp;
	int size = 0;
	scanf("%s", str);
	while (str[size]) size++;
	for (int i = 0; i < size;i++) {
		printf("%s\n", str);
		tmp = str[0];
		for (int j = 0; j < size-1; j++) {
			str[j] = str[j + 1];
		}
		str[size - 1] = tmp;
	}
	return 0;
}

int main_5() {
	struct time first, second,result;
	scanf("%d %d %d", &first.hour, &first.min, &first.sec);
	scanf("%d %d %d", &second.hour, &second.min, &second.sec);
	result.hour = second.hour - first.hour;
	result.min = second.min - first.min;
	result.sec = second.sec - first.sec;
	if (result.min < 0) {
		result.hour--;
		result.min += 60;
	}
	if (result.sec < 0) {
		result.min--;
		result.sec += 60;
	}
	printf("%d %d %d", result.hour, result.min, result.sec);
	return 0;
}

int main() {
	struct test student[5];
	int low[5], ave=0;
	for (int i = 0; i < 5; i++) {
		scanf("%s %d", student[i].name, &student[i].score);
		ave += student[i].score;
	}
	ave = ave / 5;
	for (int i = 0; i < 5;i++) {
		if (student[i].score < ave) {
			printf("%s\n", student[i].name);
		}
	}
	return 0;
}

int sum(int n) {
	int total= 0;
	for (int i = 1;i < n + 1; i++) total += i;
	return total;
}

void ABC(int* num, int k) {
	for (int i = k; i < 10; i++) {
		if (num[i] > num[k]) {
			int tmp;
			tmp = num[i];
			num[i] = num[k];
			num[k] = tmp;
		}
	}
}

void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

