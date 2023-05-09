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
	srand(time(NULL)); // ������ ���� �ð���ȯ
	stack = (int*)malloc(sizeof(int) * 0);
	while (1) {
		scanf("%c", &command);
		if (command == 'p') {
			scanf("%d", &num);
			getchar();
			QueryPerformanceCounter(&start); // Ǫ�� ����
			tmp = (int*)malloc(sizeof(int) * (size + 2)); // ���� ������ �÷��ֱ� sizeof(int) * (size+1000000)
			for (int i = 0; i < size; i++) tmp[i] = stack[i]; // �ӽ� �����ϱ�
			free(stack); // ���� ���� �޸� �Ҵ� ����
			stack = tmp; // �ø� ������ ���ÿ� �ٽ� �ֱ�
			push(stack, num); // Ǫ�� ����
			QueryPerformanceCounter(&end); // Ǫ�� ���� ��
			diff.QuadPart = end.QuadPart - start.QuadPart; // �ð� ���
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("push %d (%d), cputime = %f\n", num, size, cputime);
		}
		else if (command == 'P') {
			getchar();
			QueryPerformanceCounter(&start); // Ǫ�� ����
			tmp = (int*)malloc(sizeof(int) * (size + 1000000)); // ���� ������ �鸸 �÷��ֱ�
			for (int i = 0; i < size; i++) tmp[i] = stack[i]; // �ӽ� �����ϱ�
			free(stack); // ���� ���� �޸� �Ҵ� ����
			stack = tmp; // �ø� ������ ���ÿ� �ٽ� �ֱ�
			pushMillion(stack);
			QueryPerformanceCounter(&end); // Ǫ�� ���� ��
			diff.QuadPart = end.QuadPart - start.QuadPart; // �ð� ���
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("pushMillion (%d), cputime = %f\n", size, cputime);
		}
		else if (command == 'o') {
			getchar();
			QueryPerformanceCounter(&start); // �� ����
			num = pop(stack);
			QueryPerformanceCounter(&end); // �� ���� ��
			diff.QuadPart = end.QuadPart - start.QuadPart; // �ð� ���
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("pop %d (%d), cputime = %f\n", num, size, cputime);
		}
		else if (command == 'O') {
			getchar();
			QueryPerformanceCounter(&start); // �� ����
			popMillion(stack);
			tmp = (int*)malloc(sizeof(int) * (size)); // ���� ������ �ٿ��ֱ�
			for (int i = 0; i < size; i++) tmp[i] = stack[i]; // �ӽ� �����ϱ�
			free(stack); // ū ���� �޸� �Ҵ� ����
			stack = tmp; // ���� ������ ���ÿ� �ٽ� �ֱ�
			QueryPerformanceCounter(&end); // �� ���� ��
			diff.QuadPart = end.QuadPart - start.QuadPart; // �ð� ���
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("popMillion (%d), cputime = %f\n", size, cputime);
		}
		else if (command == 'f') {
			getchar();
			QueryPerformanceCounter(&start); // ���� �� ã�� ����
			num = findMin(stack);
			QueryPerformanceCounter(&end); // ã�� ���� ��
			diff.QuadPart = end.QuadPart - start.QuadPart; // �ð� ���
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("min %d (%d), cputime = %f\n",num, size, cputime);
		}
		else if (command == 'q') { // ���α׷� ����
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
	min = stack[size - 1]; // ���� ó������ ���� ��� �ֱ�
	for (int i = 0; i < size - 1; i++) {
		if (stack[i] < min) min = stack[i]; // �ּҰ����� ��� ��ȯ�ϱ�
	}
	return min;
}
void pushMillion(int* stack) {

	
	
	for (int i = 0; i < 1000000; i++) push(stack, rand() % 9000 + 1000); // �����Լ� �̿��Ͽ� 1000 ~ 9999�� �־ push �鸸�� ����

}
void popMillion(int* stack) {
	for (int i = 0; i < 1000000; i++)pop(stack); // �� �鸸�� ����

}
