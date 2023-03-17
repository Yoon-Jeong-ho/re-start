#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>


int sum(int n);

void ABBC(int* num, int k);

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

struct gread {
	char name[7];
	int ko;
	int en;
	int ma;
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
	for (int k = 0; k < 9; k++) ABBC(num, k);
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

int main_6() {
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

int main_7() {
	int* num1, * num2, N;
	scanf("%d", &N);
	num1 = (int*)malloc(sizeof(int) * N);
	num2 = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num1[i]);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &num2[i]);
		num1[N - 1 - i] += num2[i];
	}
	for (int i = 0; i < N; i++) printf(" %d", num1[i]);
	free(num1);
	free(num2);
	return 0;
}

int main_8() {
	int N;
	double* ave;
	scanf("%d", &N);
	ave = (double*)malloc(sizeof(double) * N);
	struct gread *student;
	student = (struct gread*)malloc(N * sizeof(struct gread));
	for (int i = 0; i < N; i++) {
		scanf("%s %d %d %d", (student+i)->name, &(student + i)->ko, &(student + i)->en, &(student + i)->ma);
		ave[i] = (double)((student + i)->ko + (student + i)->en + (student + i)->ma) / 3;
	}
	for (int i = 0; i < N; i++) {
		printf("%s %.1f", (student + i)->name, ave[i]);
		if ((student + i)->ko >= 90 || (student + i)->en >= 90 || (student + i)->ma >= 90) {
			printf(" GREAT");
		}
		if ((student + i)->ko <70 || (student + i)->en <70 || (student + i)->ma <70) {
			printf(" BAD");
		}
		printf("\n");
	}
	return 0;	
}


int sum(int n) {
	int total= 0;
	for (int i = 1;i < n + 1; i++) total += i;
	return total;
}

void ABBC(int* num, int k) {
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

