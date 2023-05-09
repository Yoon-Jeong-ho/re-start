//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//int count = 0;
//void push(int* stack, char c);
//int pop(int* stack);
//int doOperator(char c, char  b, char  a);
//
//int main_10_02() {
//	int num, result, * stack;
//	char c,a,b;
//	stack = (int*)malloc(sizeof(int) * 100);
//	scanf("%d", &num);
//	getchar();
//	for (int i = 0; i < num; i++) {
//		result = 0;
//		count = 0;
//		while (1) {
//			scanf("%c", &c);
//			if (c == '\n') {
//				printf("%d\n",pop(stack));
//				break;
//			}
//			if (c >= '0' && c <= '9') {// 0Àº 48, 9 = 57
//				push(stack, c-48);
//			}
//			else {
//				a = pop(stack);
//				b = pop(stack); 
//				push(stack, doOperator(c, b, a));
//			}
//		}
//	}
//
//	return 0;
//}
//
//
//void push(int* stack, char c) {
//	stack[count] = c;
//	count = count + 1;
//}
//
//int pop(int* stack) {
//	if (count == 0) return 0;
//	count = count - 1;
//	return stack[count];
//}
//
//int doOperator(char c, char  b, char  a) {
//	int v;
//	if (c == '+') {
//		v = b + a;
//	}
//	else if (c == '-') {
//		v = b - a;
//	}
//	else if (c == '*') {
//		v = b * a;
//	}
//	else if (c == '/') {
//		v = b / a;
//	}
//	return v;
//}