#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
typedef struct node {
	struct node* next;
	struct node* prev;
	int elem;
}node;

typedef struct {
	node* head1;
	node* tail1;
	node* head2;
	node* tail2;
}list;
int size1 = 0;

int isEmpty(list* l);
void push(list*l, int num);
int pop(list* l);
int top(list* l);
void pushMillion(list* l);



int main() {
	int num;
	list *L;
	L = (list*)malloc(sizeof(list)); // ����Ʈ �����Ҵ�
	char command;
	double cputime;
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	QueryPerformanceFrequency(&ticksPerSec);
	srand(time(NULL)); // ������ ���� �ð���ȯ
	scanf("%c", &command);
	getchar();
	while (command != 'q') {
		if (command == 'S') { // isempty ����
			QueryPerformanceCounter(&start);
			num=isEmpty(L);
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			if (num == 1) {
				printf("Empty (%d), cputime = %f\n", size1, cputime); // �ʱ�ȭ �� ���
			}
			else {
				printf("Noempty (%d), cputime = %f\n", size1, cputime); // �̹� �ִ� ���
			}
		}
		else if (command == 't') {
			QueryPerformanceCounter(&start);
			num=top(L); // ž ���� ��ȯ
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("%d (%d), cputime = %f\n",num, size1, cputime); // ���
		}
		else if (command == 'p') {
			QueryPerformanceCounter(&start);
			while (command != '\n') {
				scanf("%d%c", &num, &command); // c�� ���� �������� Ȯ��
				push(L, num); // �Ѹ� Ǫ��
				size1++; // ������ ��
			}
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("OK (%d), cputime = %f\n", size1, cputime);
		}
		else if (command == 'P') {
			QueryPerformanceCounter(&start);
			pushMillion(L);
			size1 += 1000000; // �鸸�� �ݺ�
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("OK (%d), cputime = %f\n", size1, cputime);
		}
		else if (command == 'o') {
			QueryPerformanceCounter(&start);
			num = pop(L); 
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			if(num == 0) printf("Empty Stack Exception!! (%d), cputime = %f\n", size1, cputime); // �� ���� ���н�
			else printf("%d (%d), cputime = %f\n", num , --size1, cputime); // �� ���� ������
		}
		scanf("%c", &command);
	}

	return 0;
}
int isEmpty(list* L) {
	int result;
	if (size1 == 0) {

		node* head1, * head2, * tail1, * tail2;
		tail1 = (node*)malloc(sizeof(node));
		tail2 = (node*)malloc(sizeof(node));
		head1 = (node*)malloc(sizeof(node));
		head2 = (node*)malloc(sizeof(node));
		L->head1 = head1;
		L->head2 = head2;
		L->tail1 = tail1;
		L->tail2 = tail2;
		head1->next = tail1;
		head2->next = tail2;
		tail1->next = NULL;
		tail2->next = NULL;
		tail1->prev = head1;
		tail2->prev = head2;
		head1->prev = NULL;
		head2->prev = NULL;
		head1->elem = NULL;
		head2->elem = NULL;
		tail1->elem = NULL;
		tail2->elem = NULL;
		result = 1;
	}
	else result = 0;
	return result;
}
void push(list* L, int num) {
	node* newnode, * head1;
	newnode = (node*)malloc(sizeof(node)); // ���ο� ��� ���� �¿� ���� �̾��ֱ�
	head1 = L->head1;
	newnode->prev = head1;
	newnode->next = head1->next;
	head1->next = newnode;
	head1 = newnode->next;
	head1->prev = newnode;
	newnode->elem = num;
}
int pop(list* L) {
	int result;
	if (size1 == 0) result = 0;
	else {
		node* head1, * head2, * tail1, * tail2,*movenode,*prevnode,*nextnode;
		head1 = L->head1;
		head2 = L->head2;
		tail1 = L->tail1;
		tail2 = L->tail2;
		while (head1->next != tail1->prev) { // pop�� ��� ���� ����.
			movenode = tail1->prev;
			prevnode = movenode->prev;
			prevnode->next = tail1;
			tail1->prev = prevnode; // ť1���� ������ ��� ���Դ�.
			nextnode = head2->next;
			head2->next = movenode;
			movenode->prev = head2;
			movenode->next = nextnode;
			nextnode->prev = movenode; // ť2�� ���� �Ϸ�
		}
		movenode = head1->next;
		result = movenode->elem;
		free(movenode);
		head1->next = tail1;
		tail1->prev = head1;
		while (head2->next != tail2) {
			movenode = tail2->prev;
			prevnode = movenode->prev;
			prevnode->next = tail2;
			tail2->prev = prevnode; // ť2���� ��� ���Դ�.
			nextnode = head1->next;
			head1->next = movenode;
			movenode->prev = head1;
			movenode->next = nextnode;
			nextnode->prev = movenode; // ť1�� ����Ϸ�
		}
	}
	return result;
}
int top(list* L) {
	node* topnum;
	topnum = L->head1;
	topnum = topnum->next;
	return topnum->elem; // top�� ���� �ֱ� �Էµ� ���̹Ƿ� �Ӹ����� ã�ư���.
}
void pushMillion(list* L) {
	for (int i = 0; i < 1000000; i++) push(L, rand() % 90 + 10); // �����Լ� �̿��Ͽ� 10 ~ 99�� �־ push �鸸�� ����
}
