//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int TopIndex;
//
//void push(char *Stack, int InputData, int StackSize);
//char pop(char *Stack);
//void print(char *Stack);
////void upRotate(char *Stack, int RotateNumber);
//void upRotate(char *Stack, int RotateNumber, int StackSize);
////void downRotate(char *Stack, int RotateNumber);
//void downRotate(char *Stack, int RotateNumber, int StackSize);
//void peek(char *Stack);
//void duplicate(char *Stack, int StackSize);
//
//int main(void)
//{
//	int StackSize, InputValue, RotateNumber;
//	char *Stack, InputOrder[10], InputData;
//	TopIndex = -1;
//	scanf("%d", &StackSize);
//	Stack = (char*)malloc(sizeof(char) * StackSize);
//
//	scanf("%d", &InputValue);
//	getchar();
//
//	for (int i = 0; i < InputValue; i++)
//	{
//		scanf("%s", InputOrder);
//		getchar();
//		if (strcmp(InputOrder, "PUSH") == 0)
//		{
//			scanf("%c", &InputData);
//			getchar();
//			push(Stack, InputData, StackSize);
//		}
//		else if (strcmp(InputOrder, "POP") == 0)
//		{
//			pop(Stack);
//		}
//		else if (strcmp(InputOrder, "PRINT") == 0)
//		{
//			print(Stack);
//		}
//		else if (strcmp(InputOrder, "UpR") == 0)
//		{
//			scanf("%d", &RotateNumber);
//			getchar();
//			upRotate(Stack, RotateNumber, StackSize);
//		}
//		else if (strcmp(InputOrder, "DownR") == 0)
//		{
//			scanf("%d", &RotateNumber);
//			getchar();
//			downRotate(Stack, RotateNumber, StackSize);
//		}
//		else if (strcmp(InputOrder, "DUP") == 0)
//		{
//			duplicate(Stack, StackSize);
//		}
//		else if (strcmp(InputOrder, "PEEK") == 0)
//		{
//			peek(Stack);
//		}
//	}
//
//	free(Stack);
//}
//
//void push(char *Stack, int InputData, int StackSize)
//{
//	if (TopIndex >= StackSize - 1)
//	{
//		printf("Stack FULL\n");
//		return;
//	}
//	TopIndex++;
//	Stack[TopIndex] = InputData;
//}
//
//char pop(char *Stack)
//{
//	if (TopIndex <= -1)
//	{
//		printf("Stack Empty\n");
//		return;
//	}
//	return Stack[TopIndex--];
//}
//
//void print(char *Stack)
//{
//	for (int i = TopIndex; i > -1; i--)
//	{
//		printf("%c", Stack[i]);
//	}
//	printf("\n");
//}
////아래 함수는 upRotate를 배열 값 이동으로 짠 코드입니다.
////void upRotate(char *Stack, int RotateNumber)
////{
////	char tmp;
////	if (RotateNumber > TopIndex + 1)
////	{
////		return;
////	}
////	tmp = Stack[TopIndex];
////	for (int i = TopIndex; i > TopIndex - RotateNumber + 1; i--)
////	{
////		Stack[i] = Stack[i - 1];
////	}
////	Stack[TopIndex - RotateNumber + 1] = tmp;
////	
////}
//
////아래 함수는 upRotate를 push와 pop을 이용해서 짠 코드입니다.
//void upRotate(char *Stack, int RotateNumber, int StackSize)
//{
//	char *tmp;
//	if (RotateNumber > TopIndex + 1)
//	{
//		return;
//	}
//	tmp = (char*)malloc(sizeof(char) * RotateNumber);
//	for (int i = 0; i < RotateNumber; i++)
//	{
//		tmp[i] = pop(Stack);
//	}
//	push(Stack, tmp[0], StackSize);
//	for (int i = RotateNumber - 1; i > 0; i--)
//	{
//		push(Stack, tmp[i], StackSize);
//	}
//	free(tmp);
//}
////아래 함수는 downRotate를 배열 값 이동으로 짠 코드입니다.
////void downRotate(char *Stack, int RotateNumber)
////{
////	if (RotateNumber > TopIndex + 1)
////	{
////		return;
////	}
////	char tmp;
////	tmp = Stack[TopIndex - RotateNumber + 1];
////	for (int i = TopIndex - RotateNumber + 2; i <= TopIndex; i++)
////	{
////		Stack[i - 1] = Stack[i];
////	}
////	Stack[TopIndex] = tmp;
////}
//
////아래 함수는 downRotate를 push와 pop을 이용해서 짠 코드입니다.
//void downRotate(char *Stack, int RotateNumber, int StackSize)
//{
//	char *tmp;
//	if (RotateNumber > TopIndex + 1)
//	{
//		return;
//	}
//	tmp = (char*)malloc(sizeof(char) * RotateNumber);
//	for (int i = 0; i < RotateNumber; i++)
//	{
//		tmp[i] = pop(Stack);
//	}
//	for (int i = RotateNumber - 2; i > -1; i--)
//	{
//		push(Stack, tmp[i], StackSize);
//	}
//	push(Stack, tmp[RotateNumber - 1], StackSize);
//	free(tmp);
//}
//
//void peek(char *Stack)
//{
//	if (TopIndex <= -1)
//	{
//		printf("Stack Empty\n");
//		return;
//	}
//	printf("%c\n", Stack[TopIndex]);
//}
//
//void duplicate(char *Stack, int StackSize)
//{
//	if (TopIndex >= StackSize)
//	{
//		printf("Stack FULL\n");
//		return;
//	}
//	int PopIndex;
//	PopIndex = pop(Stack);
//	push(Stack, PopIndex, StackSize);
//	push(Stack, PopIndex, StackSize);
//}