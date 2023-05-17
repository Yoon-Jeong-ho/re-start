//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//#include <string.h>
//int main_2023_11_01() {
//	int q, * que, n,rear = 0,front = 0,num;
//	char command;
//	scanf("%d", &q);
//	que = (int*)malloc(sizeof(int) * q);
//	memset(que, 0, sizeof(int) * q);
//	scanf("%d", &n);
//	getchar();
//	for (int i = 0; i < n; i++) {
//		scanf("%c", &command);
//		if (command == 'I') { // 추가
//			scanf("%d", &num);
//			getchar();
//			if (front == (rear + 1) % q) {
//				printf("overflow");
//				for (int j = 0; j < q; j++) printf(" %d", que[j]);
//				break;
//			}
//			if (rear + 1 == q)rear = 0;
//			else rear++;
//			que[rear] = num;
//			
//		}
//		else if (command == 'D') { // 삭제
//			getchar();
//			if (rear == front) {
//				printf("underflow");
//				break;
//			}
//			if (front == q - 1) front = 0;
//			else front++;
//			que[front] = 0;
//		}
//		else if (command == 'P') { // 프린트
//			getchar();
//			for (int j = 0; j < q; j++) printf(" %d", que[j]);
//			printf("\n");
//		}
//	}
//	return 0;
//}