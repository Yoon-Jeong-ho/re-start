////#define _CRT_SECURE_NO_WARNINGS 
////
////#include<stdio.h>
////#include<stdlib.h>
////
////int size = 0;
////
////typedef struct node {
////	struct node* next;
////	int elem;
////	struct node* prev;
////}node;
////
////typedef struct list {
////	node* front;
////	node* rear;
////}list;	
////
////void add_front(list* L, int x);
////void add_rear(list* L, int x);
////int delete_front(list* L);
////int delete_rear(list* L);
////void print(list *L);
////
////int main() {
////	list* L;
////	L = (list*)malloc(sizeof(list));
////	L->front = NULL;
////	L->rear = NULL;
////	int n,x;
////	char command, c;
////	scanf("%d", &n);
////	getchar();
////	for (int i = 0; i < n; i++) {
////		scanf("%c", &command);
////		if (command == 'A') {
////			scanf("%c", &command);
////			scanf("%d", &x);
////			getchar();
////			if (command == 'F') {
////				add_front(L,x);
////			}
////			else if (command == 'R') {
////				add_rear(L, x);
////			}
////		}
////		else if (command == 'D') {
////			scanf("%c", &command);
////			getchar();
////			if (command == 'F') {
////				if (delete_front(L) == 0) {
////					printf("underflow\n");
////					break;
////				}
////			}
////			else if (command == 'R') {
////				if (delete_rear(L) == 0) {
////					printf("underflow\n");
////					break;
////				}
////			}
////		}
////		else if (command == 'P') {
////			getchar();
////			print(L);
////		}
////	}
////}
////
////
////
////void add_front(list* L, int x) {
////	if (size == 0) {
////		node* a;
////		a = (node*)malloc(sizeof(node));
////		L->front = a;
////		L->rear = a;
////		a->prev = NULL;
////		a->next = NULL;
////		a->elem = x;
////		size++;
////		return;
////	}
////	node* a,*b;
////	a = (node*)malloc(sizeof(node));
////	b = L->front;
////	L->front = a;
////	a->next = b;
////	b->prev = a;
////	a->prev = NULL;
////	a->elem = x;
////	size++;
////	return;
////}
////void add_rear(list* L, int x) {
////	if (size == 0) {
////		node* a;
////		a = (node*)malloc(sizeof(node));
////		L->front = a;
////		L->rear = a;
////		a->prev = NULL;
////		a->next = NULL;
////		a->elem = x;
////		size++;
////		return;
////	}
////	node* a, * b;
////	a = (node*)malloc(sizeof(node));
////	b = L->rear;
////	L->rear = a;
////	b->next = a;
////	a->prev = b;
////	a->next = NULL;
////	a->elem = x;
////	size++;
////	return;
////}
////int delete_front(list* L) {
////	if (size == 0) return 0;
////	node* a;
////	size--;
////	a = L->front;
////	L->front = a->next;
////	free(a);
////	if (size == 0)return 1;
////	a = L->front;
////	a->prev = NULL;
////	
////	if (size == 0) L->rear = NULL;
////	return 1;
////}
////int delete_rear(list* L) {
////	if (size == 0) return 0;
////	node* a;
////	size--;
////	a = L->rear;
////	L->rear = a->prev;
////	free(a);
////	if (size == 0)return 1;
////	a = L->rear;
////	a->next = NULL;
////	
////	if (size == 0) L->front = NULL;
////	return 1;
////}
////void print(list* L) {
////	node* a;
////	a = L->front;
////	for (int i = 0; i < size - 1; i++) {
////		printf(" %d", a->elem);
////		a = a->next;
////	}
////	printf(" %d\n", a->elem);
////	return;
////}