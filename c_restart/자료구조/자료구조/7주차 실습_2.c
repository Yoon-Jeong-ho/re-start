#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	struct node* next;
	int elem;
}node;

typedef struct list {
	node* firsthead;
	node* secondhead;
}list;

void addfirstnode(list *L);

int main() {
	list* L;
	L = (list*)malloc(sizeof(list));
	node* ahead, * bhead;
	ahead = (node*)malloc(sizeof(node));
	bhead = (node*)malloc(sizeof(node));
	L->firsthead = ahead;
	L->secondhead = bhead;
	ahead->next = NULL;
	bhead->next = NULL;
	int num;
	scanf("%d", &num);
	for (int i = 0; i < num; i++) addfirstnode(L);
	for (int i = 0; i < num; i++) {
		printf("%d", ahead->elem);
		ahead = ahead->next;
	}
	return 0;
}

void addfirstnode(list* L) {
	int num,count =0;
	scanf("%d", &num);
	node* newnode, * prevnode, * anode;
	anode = L->firsthead;
	prevnode = L->firsthead;
	newnode = (node*)malloc(sizeof(node));
	newnode->elem = num;
	while (anode->next != NULL&& anode->elem>num) {
		anode = anode->next;
		count++;
	}
	for (int i = 0; i < count - 1; i++) prevnode = prevnode->next;
	if ((count == 0 && anode->elem == NULL)|| anode->elem > num) {//ó���ΰ��� a��尡 �� ũ���� �ڿ� ��尡 ��� ���Ϲ��� ������
		anode->next = newnode;
		newnode->next = NULL;
	}
	else { // ���������
		newnode->next = anode;
		prevnode->next = newnode;
	}
}