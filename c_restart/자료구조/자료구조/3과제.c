#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
int size = 0;
void push(int* stack, int num);
int pop(int* stack);
int findMin(int* stack);
void pushMillion(int* stack);
void popMillion(int* stack);

int main() {
	int num,*stack;
	int* tmp;
	char command;
	double cputime;
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	QueryPerformanceFrequency(&ticksPerSec);
	srand(time(NULL)); // 랜덤을 위한 시간변환
	stack = (int*)malloc(sizeof(int) * 0);
	while (1) {
		scanf("%c", &command);
		if (command == 'p') {
			scanf("%d", &num);
			getchar();
			QueryPerformanceCounter(&start); // 푸쉬 시작
			tmp = (int*)malloc(sizeof(int) * (size + 2)); // 스택 사이즈 늘려주기 sizeof(int) * (size+1000000)
			for (int i = 0; i < size; i++) tmp[i] = stack[i]; // 임시 저장하기
			free(stack); // 작은 스택 메모리 할당 해제
			stack = tmp; // 늘린 사이즈 스택에 다시 넣기
			push(stack, num); // 푸시 진행
			QueryPerformanceCounter(&end); // 푸쉬 진행 끝
			diff.QuadPart = end.QuadPart - start.QuadPart; // 시간 계산
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("push %d (%d), cputime = %f\n", num, size, cputime);
		}
		else if (command == 'P') {
			getchar();
			QueryPerformanceCounter(&start); // 푸쉬 시작
			tmp = (int*)malloc(sizeof(int) * (size + 1000000)); // 스택 사이즈 백만 늘려주기
			for (int i = 0; i < size; i++) tmp[i] = stack[i]; // 임시 저장하기
			free(stack); // 작은 스택 메모리 할당 해제
			stack = tmp; // 늘린 사이즈 스택에 다시 넣기
			pushMillion(stack);
			QueryPerformanceCounter(&end); // 푸쉬 진행 끝
			diff.QuadPart = end.QuadPart - start.QuadPart; // 시간 계산
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("pushMillion (%d), cputime = %f\n", size, cputime);
		}
		else if (command == 'o') {
			getchar();
			QueryPerformanceCounter(&start); // 팝 시작
			num = pop(stack);
			QueryPerformanceCounter(&end); // 팝 진행 끝
			diff.QuadPart = end.QuadPart - start.QuadPart; // 시간 계산
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("pop %d (%d), cputime = %f\n", num, size, cputime);
		}
		else if (command == 'O') {
			getchar();
			QueryPerformanceCounter(&start); // 팝 시작
			popMillion(stack);
			tmp = (int*)malloc(sizeof(int) * (size)); // 스택 사이즈 줄여주기
			for (int i = 0; i < size; i++) tmp[i] = stack[i]; // 임시 저장하기
			free(stack); // 큰 스택 메모리 할당 해제
			stack = tmp; // 작은 사이즈 스택에 다시 넣기
			QueryPerformanceCounter(&end); // 팝 진행 끝
			diff.QuadPart = end.QuadPart - start.QuadPart; // 시간 계산
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("popMillion (%d), cputime = %f\n", size, cputime);
		}
		else if (command == 'f') {
			getchar();
			QueryPerformanceCounter(&start); // 작은 것 찾기 시작
			num = findMin(stack);
			QueryPerformanceCounter(&end); // 찾기 진행 끝
			diff.QuadPart = end.QuadPart - start.QuadPart; // 시간 계산
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("min %d (%d), cputime = %f\n",num, size, cputime);
		}
		else if (command == 'q') { // 프로그램 종료
			getchar();
			break;
		}
	}
	free(stack);
	return 0;
}

void push(int* stack, int num) {
	stack[size++] = num;

}
int pop(int* stack) {
	return stack[--size];
}
int findMin(int* stack) {
	int min;
	min = stack[size - 1]; // 제일 처음으로 비교할 대상 넣기
	for (int i = 0; i < size - 1; i++) {
		if (stack[i] < min) min = stack[i]; // 최소값으로 계속 교환하기
	}
	return min;
}
void pushMillion(int* stack) {

	
	
	for (int i = 0; i < 1000000; i++) push(stack, rand() % 9000 + 1000); // 랜덤함수 이용하여 1000 ~ 9999값 넣어서 push 백만번 진행

}
void popMillion(int* stack) {
	for (int i = 0; i < 1000000; i++)pop(stack); // 팝 백만번 진행

}
