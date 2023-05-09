//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//int count = 0;
//void push(char* stack, char c);
//char pop(char* stack);
//
//int main_876e6789e8q76() {
//	char P[150], * stack, command,z=0;
//	int num,t=0,q=0;
//	stack = (char*)malloc(sizeof(char) * 100);
//	P['|'] = 1;
//	P['&'] = 2;
//	P['<'] = 3;
//	P['>'] = 3;
//	P['+'] = 4;
//	P['-'] = 4;
//	P['/'] = 5;
//	P['*'] = 5;
//	P['!'] = 6;
//	scanf("%d", &num);
//	getchar();
//	for (int i = 0; i < num; i++) {
//		count = 0;
//		q = 1;
//		while (1) {	
//			scanf("%c", &command);
//			if (q==1&& command == '-') {
//				z = 1;
//				continue;
//			}
//			if (t == 1 && (command == '&' || command == '|')) {
//				t = 0;
//				q = 1;
//				continue;
//			}
//			if (command == '\n') break;
//			if (command >= 'A' && command <= 'Z') { // 숫자인 경우
//				printf("%c", command);
//				q = 0;
//			}
//			else if (command == '(') {
//				push(stack, command);
//				q = 1;
//			}
//			else if (command == ')') {
//				while (stack[count -1] != '(') {
//					printf("%c", pop(stack));
//				}
//				pop(stack);
//				q = 0;
//			}
//			else {// 부호인 경우	
//				while (count != 0 && (P[command] <= P[stack[count -1]])) {
//					if (stack[count - 1] == '&' || stack[count - 1] == '|')printf("%c", pop(stack));;
//					printf("%c", pop(stack));
//				}
//				if (t == 0 && (command == '&' || command == '|')) {
//					push(stack, command);
//					push(stack, command);
//					t = 1;
//					q = 1;
//					continue;
//				}
//				else t = 0;
//				push(stack, command);
//				q = 1;
//			}
//			if (z == 1) {
//				printf("-");
//				z = 0;
//			}
//		}
//		while (count != 0) {
//			printf("%c", pop(stack));
//		}
//		printf("\n");
//	}
//
//	return 0;
//}
//
//void push(char* stack, char c) {
//	stack[count] = c;
//	count = count + 1;
//}
//
//char pop(char* stack) {
//	if (count == 0) return 0;
//	count = count - 1;
//	return stack[count];
//}
