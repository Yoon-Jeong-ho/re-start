////#pragma warning(disable:4996)
////#include <stdio.h>
////#include <stdlib.h>
////int *Queue, QueueSize, front, rear;
////
////void InputQueue(int InputData);
////int DeleteQueue(void);
////
////int main(void)
////{
////	int InputSize, InputData;
////	char Input;
////	scanf("%d", &QueueSize);
////	Queue = (int*)malloc(sizeof(int) * QueueSize);
////
////	for (int i = 0; i < QueueSize; i++)
////	{
////		Queue[i] = 0;
////	}
////	scanf("%d", &InputSize);
////	for (int i = 0; i < InputSize; i++)
////	{
////		getchar();
////		scanf("%c", &Input);
////		if (Input == 'I')
////		{
////			scanf("%d", &InputData);
////			InputQueue(InputData);
////		}
////		else if (Input == 'D')
////		{
////			DeleteQueue();
////		}
////		else if (Input == 'P')
////		{
////			for (int i = 0; i < QueueSize; i++)
////			{
////				printf(" %d", Queue[i]);
////			}
////			printf("\n");
////		}
////	}
////	free(Queue);
////}
////
////void InputQueue(int InputData)
////{
////	if ((rear + 1) % QueueSize == front % QueueSize)
////	{
////		printf("overflow");
////		for (int i = 0; i < QueueSize; i++)
////		{
////			printf(" %d", Queue[i]);
////		}
////		printf("\n");
////		free(Queue);
////		exit(1);
////	}
////	rear++;
////	rear = rear % QueueSize;
////	Queue[rear] = InputData;
////}
////
////int DeleteQueue()
////{
////	int Data;
////	if (rear % QueueSize == front % QueueSize)
////	{
////		printf("underflow");
////		free(Queue);
////		exit(1);
////	}
////	else
////	{
////		front++;
////		front = front % QueueSize;
////		Data = Queue[front - 1];
////		Queue[front] = 0;
////		return Data;
////	}
////}
////
//
//
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct node
//{
//	int elem;
//	struct node *next;
//	struct node *prev;
//}NODE;
//
//NODE *DeQueue, *front, *rear;
//int DeQueueNum;
//
//void InputFront(int InputData);
//void InputRear(int InputData);
//void DeleteFront();
//void DeleteRear();
//void PrintAll();
//void FreeDeQueue();
//
//int main(void)
//{
//	int InputSize, InputData;
//	char Input[10];
//	DeQueueNum = 0;
//
//	scanf("%d", &InputSize);
//	getchar();
//
//	for (int i = 0; i < InputSize; i++)
//	{
//		scanf("%s", Input);
//		getchar();
//		if (strcmp(Input, "AF") == 0)
//		{
//			scanf("%d", &InputData);
//			getchar();
//			if (DeQueueNum == 0)
//			{
//				DeQueue = (NODE*)malloc(sizeof(NODE));
//				DeQueue->elem = InputData;
//				DeQueue->next = NULL;
//				DeQueue->prev = NULL;
//				front = DeQueue;
//				rear = DeQueue;
//				DeQueueNum++;
//			}
//			else
//			{
//				InputFront(InputData);
//				DeQueueNum++;
//			}
//		}
//		else if (strcmp(Input, "AR") == 0)
//		{
//			scanf("%d", &InputData);
//			getchar();
//			if (DeQueueNum == 0)
//			{
//				DeQueue = (NODE*)malloc(sizeof(NODE));
//				DeQueue->elem = InputData;
//				DeQueue->next = NULL;
//				DeQueue->prev = NULL;
//				front = DeQueue;
//				rear = DeQueue;
//				DeQueueNum++;
//			}
//			else
//			{
//				InputRear(InputData);
//				DeQueueNum++;
//			}
//		}
//		else if (strcmp(Input, "DF") == 0)
//		{
//			DeleteFront();
//			DeQueueNum--;
//		}
//		else if (strcmp(Input, "DR") == 0)
//		{
//			DeleteRear();
//			DeQueueNum--;
//		}
//		else if (strcmp(Input, "P") == 0)
//		{
//			PrintAll();
//		}
//	}
//	free(DeQueue);
//}
//
//void InputFront(int InputData)
//{
//	NODE *newnode;
//	newnode = (NODE*)malloc(sizeof(NODE));
//	newnode->elem = InputData;
//	newnode->prev = NULL;
//	newnode->next = front;
//	newnode->next->prev = newnode;
//	front = newnode;
//}
//
//void InputRear(int InputData)
//{
//	NODE *newnode;
//	newnode = (NODE*)malloc(sizeof(NODE));
//	newnode->elem = InputData;
//	newnode->prev = rear;
//	newnode->next = NULL;
//	newnode->prev->next = newnode;
//	rear = newnode;
//}
//
//void DeleteFront()
//{
//	NODE *p;
//	if (DeQueueNum == 0)
//	{
//		printf("underflow\n");
//		exit(1);
//	}
//	else
//	{
//		p = front;
//		if(DeQueueNum != 1)
//		{
//			front = front->next;
//			front->prev = NULL;
//		}
//		free(p);
//	}
//}
//
//void DeleteRear()
//{
//	NODE *p;
//	if (DeQueueNum == 0)
//	{
//		printf("underflow\n");
//		exit(1);
//	}
//	else
//	{
//		p = rear;
//		if (DeQueueNum != 1)
//		{
//			rear = rear->prev;
//			rear->next = NULL;
//		}
//		free(p);
//	}
//}
//
//void PrintAll()
//{
//	NODE *p;
//	p = front;
//	while (p != NULL)
//	{
//		printf(" %d", p->elem);
//		p = p->next;
//	}
//	printf("\n");
//}
//
//void FreeDeQueue()
//{
//	NODE *p;
//	p = front;
//	while (p != NULL)
//	{
//		front = front->next;
//		free(p);
//		p = front;
//	}
//}