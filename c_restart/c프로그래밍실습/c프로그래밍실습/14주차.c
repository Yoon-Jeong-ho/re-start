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
struct student {
	char* name; // 이름 저장
	int firstStage; // 1단계 점수 저장
	int interview; // 면접 점수 저장
	double sum; // 총점 저장
};
int main() {
	int n, m,num=0;
	struct student* st, tmpst;
	char tmp[100];
	scanf("%d %d", &n, &m); getchar(); // 입력
	st = (struct student*)malloc(sizeof(struct student) * n); // 동적할당
	if (st == NULL) return -1; // 오류 확인
	for (int i = 0; i < n; i++) { // 입력받기
		scanf("%s %d %d",tmp,&st[i].firstStage,&st[i].interview); getchar(); // 입력
		st[i].name = (char*)malloc(sizeof(char) * (strlen(tmp) + 1)); // 동적할당
		strcpy(st[i].name, tmp); // 할당 오류 확인
		st[i].sum = st[i].firstStage * 7 + st[i].interview * 3; // 더하기
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (st[i].sum < st[j].sum || (st[i].sum == st[j].sum && st[i].firstStage < st[j].firstStage) || (st[i].sum == st[j].sum && st[i].firstStage == st[j].firstStage && strcmp(st[i].name, st[j].name) > 0)) { // 조건확인
				tmpst = st[i];// 조건에 맞으면 바꾸기
				st[i] = st[j];
				st[j] = tmpst;
			}
		}
	}
	for (int i = 0; i < m; i++) {// m까지 출력하기
		printf("%s %d %d %.1f\n", st[i].name, st[i].firstStage, st[i].interview, st[i].sum/10);
		num++; // 마지막에 출력할 숫자 늘리기
		while (i<n-1 && st[i].sum == st[i + 1].sum && st[i].firstStage == st[i + 1].firstStage) {
			i++;// 여긴 합과 첫번째 시험이 같은 사람들 출력하는 곳
			printf("%s %d %d %.1f\n", st[i].name, st[i].firstStage, st[i].interview, st[i].sum / 10);
			num++;
		}
	}
	printf("%d", num);
	for (int i = 0; i < n; i++) {
		free(st[i].name);//이름 할당 해제
	}
	free(st); // 마지막 할당 해제
	return 0;
}