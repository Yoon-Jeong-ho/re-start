//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int TopIndex, checkint;
//
//void push(char *Stack, char InputData);
//char pop(char *Stack);
//int ReturnCharType(char *Array1, int num);
//int main(void)
//{
//	int Input, count;
//	char Array1[101], Array2[101], Stack[101];
//
//	scanf("%d", &Input);
//	getchar();
//	for (int i = 0; i < Input; i++)
//	{
//		for (int j = 0; j < 100; j++) 
//		{
//			Array2[j] = '\0';
//			Stack[j] = '\0';
//		}
//		TopIndex = -1;
//		checkint = 0;
//		count = 0;
//		scanf("%s", Array1);
//		getchar();
//		for (int j = 0; j < strlen(Array1); j++)
//		{
//			if (Array1[j] == '(') 
//			{
//				push(Stack, Array1[j]);
//			}
//			else if (Array1[j] == ')') 
//			{
//				while (Stack[TopIndex] != '(') 
//				{
//					Array2[count] = pop(Stack);
//					count++;
//				}
//				pop(Stack);
//			}
//			else if (ReturnCharType(Array1, j) == 6)
//			{
//				push(Stack, Array1[j]);
//			}
//			else if (ReturnCharType(Array1, j) == 0)
//			{
//				Array2[count] = Array1[j];
//				count++;
//			}
//			else 
//			{
//				if (checkint == 1) 
//				{
//					Array2[count] = pop(Stack);
//					count++;
//				}
//				else 
//				{
//					while ((TopIndex != -1) && (ReturnCharType(Array1, j) <= ReturnCharType(Stack, TopIndex)))
//					{
//						Array2[count] = pop(Stack);
//						count++;
//					}
//				}
//				if ((ReturnCharType(Array1, j) == 1) || (ReturnCharType(Array1, j) == 2))
//				{
//					push(Stack, Array1[j++]);
//				}
//				push(Stack, Array1[j]);
//			}
//		}
//		while (TopIndex != -1) 
//		{
//			Array2[count] = pop(Stack);
//			count++;
//		}
//
//		printf("%s\n", Array2);
//	}
//}
//
//void push(char *Stack, char InputData)
//{
//	TopIndex++;
//	Stack[TopIndex] = InputData;
//}
//char pop(char *Stack)
//{
//	return Stack[TopIndex--];
//}
//int ReturnCharType(char *Array1, int num)
//{
//	if ((TopIndex != num) && (num == 0) && ((Array1[num] == '+') || (Array1[num] == '-'))) 
//	{
//		checkint = 1;
//		return 6;
//	}
//	else if ((TopIndex != -1) && ((Array1[num] == '+') || (Array1[num] == '-')) && ((Array1[num - 1] == '+') || (Array1[num - 1] == '-') || (Array1[num - 1] == '*') || (Array1[num - 1] == '/') || (Array1[num - 1] == '&') || (Array1[num - 1] == '|') || (Array1[num - 1] == '<') || (Array1[num - 1] == '>') || (Array1[num - 1] == '!')))
//	{
//		return 6;
//	}
//	else if (Array1[num] == '|') 
//	{
//		return 1;
//	}
//	else if (Array1[num] == '&') 
//	{
//		return 2;
//	}
//	else if (Array1[num] == '>' || Array1[num] == '<') 
//	{
//		return 3;
//	}
//	else if (Array1[num] == '+' || Array1[num] == '-') 
//	{
//		return 4;
//	}
//	else if (Array1[num] == '*' || Array1[num] == '/') 
//	{
//		return 5;
//	}
//	else if (Array1[num] == '!') 
//	{
//		return 6;
//	}
//	else 
//	{
//		return 0;
//	}
//}
