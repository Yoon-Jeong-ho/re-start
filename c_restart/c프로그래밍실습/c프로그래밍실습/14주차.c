#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int check_w(char* p, char* q);

int main() {
	int n,m, num[20] = {0},max=0;
	char a[20][200];
	scanf("%d %d", &n,&m); getchar();
	for(int i = 0 ; i < n ; i++)gets(a[i]); // 문자열 입력받기
	for (int i = 0; i < n; i++) {
		num[i] = check_w(a[i], a[i]+m); // 함수값 배열에 저장
		printf("%d ", num[i]);
	}
	while (1) {
		max = 0;
		for (int i = 0; i < n; i++) { // 큰값 찾기
			if (num[i] > max) max = num[i];
		}
		if (max == 0) break;// max가 모두 0이면 반복문 끝
		for (int i = 0; i < n; i++) {//큰값들 앞에서 부터 출력하기
			if (num[i] == max) {
				printf("%s\n", a[i]);
				num[i] = 0;
			}
		}
	}
	return 0;
}
int check_w(char* p, char* q) {
	int sum = 0;
	for (p; p <= q; p++) {
		if (*p == '\0')break;
		if ((*p < 'a' || *p > 'z') && (*p < 'A' || *p > 'Z') && *p != ' ') { // 알파벳과 공백이 아닌경우
			sum++; // 하나씩 늘린다.
		}
	}
	return sum;
}
