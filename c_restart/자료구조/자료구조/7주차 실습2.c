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
	node* unionhead;
	node* intersecthead;
}list;	

void addfirstnode(list* L);
void addsecondnode(list* L);
void union1(list* L);
void intersect(list *L);

int main() {
	list* L;
	L = (list*)malloc(sizeof(list));
	node* ahead, * bhead, * unhead, * inhead;
	ahead = (node*)malloc(sizeof(node));
	bhead = (node*)malloc(sizeof(node));
	unhead = (node*)malloc(sizeof(node));
	inhead = (node*)malloc(sizeof(node));
	L->firsthead = ahead;
	L->secondhead = bhead;
	L->unionhead = unhead;
	L->intersecthead = inhead;
	ahead->next = NULL;
	bhead->next = NULL;
	inhead->next = NULL;
	unhead->next = NULL;
	int num;
	scanf("%d", &num);
	for (int i = 0; i < num; i++) addfirstnode(L); // �������� Ƚ����ŭ �Լ� ����
	scanf("%d", &num);
	for (int i = 0; i < num ;i++) addsecondnode(L); // ���� ����.
	union1(L); // ������ �����
	printf("\n");
	intersect(L); // ������ �����
	free(ahead);
	free(bhead);
	free(inhead);
	free(unhead);
	free(L);
	return 0;
}

void addfirstnode(list* L) {
	int num;
	scanf("%d", &num);	
	node* newnode, * anode;
	anode = L->firsthead;
	newnode = (node*)malloc(sizeof(node));
	newnode->elem = num;
	while (anode->next != NULL) anode = anode->next; // ���ڵ� ������������ �����ϱ� �״�� ���� ���� ���� ������ �ȴ�.
	anode->next = newnode;
	newnode->next = NULL;
}

void addsecondnode(list* L) {			
	int num;
	scanf("%d", &num);
	node* newnode, * bnode;
	bnode = L->secondhead;
	newnode = (node*)malloc(sizeof(node));
	newnode->elem = num;
	while (bnode->next != NULL) bnode = bnode->next; // �̰͵� ���� �Լ��� ���� ����̴�.
	bnode->next = newnode;
	newnode->next = NULL;
}

void union1(list* L) {
	node* anode, * bnode, * unode, * newnode;
	anode = L->firsthead;
	bnode = L->secondhead;
	unode = L->unionhead;
	unode->next = NULL;
	if (anode->next == NULL && bnode->next == NULL) { // �Ѵ� 0�ΰ�� ������ ����
		printf(" 0");
		return 0;
	}
	else if (anode->next == NULL) { // a�� 0�ΰ�� �������� b�̴�
		while (1) {
			bnode = bnode->next;
			newnode = (node*)malloc(sizeof(node));
			newnode->elem = bnode->elem;
			printf(" %d", bnode->elem);
			unode->next = newnode;
			newnode->next = NULL;
			unode = unode->next;
			if (bnode->next == NULL) break;
		}
		return 0;
	}
	else if (bnode->next == NULL) { // b�� 0�ΰ�� �������� a�̴�
		while (1) {
			anode = anode->next; 
			newnode = (node*)malloc(sizeof(node));
			newnode->elem = anode->elem;
			printf(" %d", anode->elem);
			unode->next = newnode;
			newnode->next = NULL;
			unode = unode->next;
			if (anode->next == NULL) break;
		}
		return 0;
	}
	anode = anode->next;
	bnode = bnode->next;
	while (1) {
		if (anode->elem > bnode->elem) { // a�� b���� ū ��� b�� ���Ҹ� �����տ� ���� �ְ� b�� ���� �ܰ��
			newnode = (node*)malloc(sizeof(node));
			newnode->elem = bnode->elem;
			printf(" %d", bnode->elem);
			unode->next = newnode;
			newnode->next = NULL;
			unode = unode->next;
			if (bnode->next != NULL) bnode = bnode->next;
			else { // ���� �ܰ谡 ������� a�� ��� �����Ű�ٰ� ������ break
				newnode = (node*)malloc(sizeof(node));
				newnode->elem = anode->elem;
				printf(" %d", anode->elem);
				unode->next = newnode;
				newnode->next = NULL;
				unode = unode->next;
				while (anode->next != NULL) {
					anode = anode->next;
					newnode = (node*)malloc(sizeof(node));
					newnode->elem = anode->elem;
					printf(" %d", anode->elem);
					unode->next = newnode;
					newnode->next = NULL;
					unode = unode->next;
				}
				break;
			}
		}
		if (anode->elem < bnode->elem) { // b�� �� ū ��� a�� ���Ҹ� ����ְ� a�� �����ܰ�� 
			newnode = (node*)malloc(sizeof(node));
			newnode->elem = anode->elem;
			printf(" %d", anode->elem);
			unode->next = newnode;
			newnode->next = NULL;
			unode = unode->next;
			if (anode->next != NULL) anode = anode->next;
			else { // ���� a�� ���̻� ������ �� ���ٸ� b�� ��� ���Ҹ� �����տ� ����ְ� ��
				newnode = (node*)malloc(sizeof(node));
				newnode->elem = bnode->elem;
				printf(" %d", bnode->elem);
				unode->next = newnode;
				newnode->next = NULL;
				unode = unode->next;
				while (bnode->next != NULL) {
					bnode = bnode->next;
					newnode = (node*)malloc(sizeof(node));
					newnode->elem = bnode->elem;
					printf(" %d", bnode->elem);
					unode->next = newnode;
					newnode->next = NULL;
					unode = unode->next;
				}
				break;
			}
		}
		if (anode->elem == bnode->elem) { // ���� ��� a�� ���Ҹ� ����ְ� �Ѵ� �����ܰ��
			newnode = (node*)malloc(sizeof(node));
			newnode->elem = bnode->elem;
			printf(" %d", bnode->elem);
			unode->next = newnode;
			newnode->next = NULL;
			unode = unode->next;
			if (anode->next != NULL && bnode->next != NULL) {
				anode = anode->next;
				bnode = bnode->next;
			}
			else if (anode->next == NULL) { // a�� ���ΰ��
				while (bnode->next != NULL) { // b�� ������ ���� ����ְ� ������.
					bnode = bnode->next;
					newnode = (node*)malloc(sizeof(node));
					newnode->elem = bnode->elem;
					printf(" %d", bnode->elem);
					unode->next = newnode;
					newnode->next = NULL;
					unode = unode->next;
				}
				break;
			}
			else if (bnode->next == NULL) {//b�� ���ΰ��
				while (anode->next != NULL) { // a�� ������ ���� ����ְ� ������.
					anode = anode->next;
					newnode = (node*)malloc(sizeof(node));
					newnode->elem = anode->elem;
					printf(" %d", anode->elem);
					unode->next = newnode;
					newnode->next = NULL;
					unode = unode->next;
				}
				break;
			}
		}
	}

}

void intersect(list* L) {
	node* anode, * bnode, * inode, * newnode;
	anode = L->firsthead;
	bnode = L->secondhead;
	inode = L->intersecthead;
	inode->next = NULL;
	if (anode->next == NULL || bnode->next == NULL) { // ���� �ϳ��� 0�̶�� �������� ������ �� ����.
		printf(" 0");
		return 0;
	}
	anode = anode->next;
	bnode = bnode->next;
	while (1) {
		if (anode->elem > bnode->elem) { // a�� �� ū ��� b�� ��ĭ �����Ű�� ���� ��Ű�� ���Ұ�� �� �̻� ���� ���� �����ϱ� break
			if (bnode->next != NULL) bnode = bnode->next;
			else break;
		}
		if (anode->elem < bnode->elem) { // b�� �� ū ��� a�� ��ĭ �����Ű�� ���� ��Ű�� ���Ұ�� �� �̻� ���� ���� �����ϱ� break
			if (anode->next != NULL) anode = anode->next;
			else break;
		}
		if (anode->elem == bnode->elem){ // ��������̹Ƿ� �����տ� ����ִ´�.
			newnode = (node*)malloc(sizeof(node));
			newnode->elem = anode->elem;
			printf(" %d", anode->elem);
			inode->next = newnode;
			newnode->next = NULL;
			inode = inode->next;
			if (anode->next != NULL && bnode->next != NULL) { 
				anode = anode->next;
				bnode = bnode->next;
			}
			else break;// �����ϳ��� ���� ������ ���ٸ� �������� �����Ƿ� break�̴�.
		}
	}
}