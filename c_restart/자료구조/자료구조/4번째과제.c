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
	L = (list*)malloc(sizeof(list)); // 리스트 동적할당
	char command;
	double cputime;
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	QueryPerformanceFrequency(&ticksPerSec);
	srand(time(NULL)); // 랜덤을 위한 시간변환
	scanf("%c", &command);
	getchar();
	while (command != 'q') {
		if (command == 'S') { // isempty 실행
			QueryPerformanceCounter(&start);
			num=isEmpty(L);
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			if (num == 1) {
				printf("Empty (%d), cputime = %f\n", size1, cputime); // 초기화 된 경우
			}
			else {
				printf("Noempty (%d), cputime = %f\n", size1, cputime); // 이미 있는 경우
			}
		}
		else if (command == 't') {
			QueryPerformanceCounter(&start);
			num=top(L); // 탑 원소 반환
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("%d (%d), cputime = %f\n",num, size1, cputime); // 출력
		}
		else if (command == 'p') {
			QueryPerformanceCounter(&start);
			while (command != '\n') {
				scanf("%d%c", &num, &command); // c를 통해 엔터인지 확인
				push(L, num); // 넘만 푸쉬
				size1++; // 사이즈 업
			}
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("OK (%d), cputime = %f\n", size1, cputime);
		}
		else if (command == 'P') {
			QueryPerformanceCounter(&start);
			pushMillion(L);
			size1 += 1000000; // 백만번 반복
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
			if(num == 0) printf("Empty Stack Exception!! (%d), cputime = %f\n", size1, cputime); // 팝 진행 실패시
			else printf("%d (%d), cputime = %f\n", num , --size1, cputime); // 팝 진행 성공시
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
	newnode = (node*)malloc(sizeof(node)); // 새로운 노드 만들어서 좌우 노드랑 이어주기
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
		while (head1->next != tail1->prev) { // pop할 노드 까지 뺀다.
			movenode = tail1->prev;
			prevnode = movenode->prev;
			prevnode->next = tail1;
			tail1->prev = prevnode; // 큐1에서 움직일 노드 빼왔다.
			nextnode = head2->next;
			head2->next = movenode;
			movenode->prev = head2;
			movenode->next = nextnode;
			nextnode->prev = movenode; // 큐2에 적재 완료
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
			tail2->prev = prevnode; // 큐2에서 노드 빼왔다.
			nextnode = head1->next;
			head1->next = movenode;
			movenode->prev = head1;
			movenode->next = nextnode;
			nextnode->prev = movenode; // 큐1에 적재완료
		}
	}
	return result;
}
int top(list* L) {
	node* topnum;
	topnum = L->head1;
	topnum = topnum->next;
	return topnum->elem; // top은 가장 최근 입력된 값이므로 머리에서 찾아간다.
}
void pushMillion(list* L) {
	for (int i = 0; i < 1000000; i++) push(L, rand() % 90 + 10); // 랜덤함수 이용하여 10 ~ 99값 넣어서 push 백만번 진행
}
