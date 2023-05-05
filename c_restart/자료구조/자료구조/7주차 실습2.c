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
	for (int i = 0; i < num; i++) addfirstnode(L); // 지정해준 횟수만큼 함수 실행
	scanf("%d", &num);
	for (int i = 0; i < num ;i++) addsecondnode(L); // 위와 같다.
	union1(L); // 합집합 만들기
	printf("\n");
	intersect(L); // 교집합 만들기
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
	while (anode->next != NULL) anode = anode->next; // 숫자도 오름차순으로 받으니까 그대로 제일 끝에 가서 넣으면 된다.
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
	while (bnode->next != NULL) bnode = bnode->next; // 이것도 위의 함수와 같은 방식이다.
	bnode->next = newnode;
	newnode->next = NULL;
}

void union1(list* L) {
	node* anode, * bnode, * unode, * newnode;
	anode = L->firsthead;
	bnode = L->secondhead;
	unode = L->unionhead;
	unode->next = NULL;
	if (anode->next == NULL && bnode->next == NULL) { // 둘다 0인경우 합집합 없음
		printf(" 0");
		return 0;
	}
	else if (anode->next == NULL) { // a만 0인경우 합집합은 b이다
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
	else if (bnode->next == NULL) { // b만 0인경우 합집합은 a이다
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
		if (anode->elem > bnode->elem) { // a가 b보다 큰 경우 b의 원소를 합집합에 집어 넣고 b를 다음 단계로
			newnode = (node*)malloc(sizeof(node));
			newnode->elem = bnode->elem;
			printf(" %d", bnode->elem);
			unode->next = newnode;
			newnode->next = NULL;
			unode = unode->next;
			if (bnode->next != NULL) bnode = bnode->next;
			else { // 다음 단계가 없을경우 a를 계속 진행시키다가 끝나면 break
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
		if (anode->elem < bnode->elem) { // b가 더 큰 경우 a의 원소를 집어넣고 a를 다음단계로 
			newnode = (node*)malloc(sizeof(node));
			newnode->elem = anode->elem;
			printf(" %d", anode->elem);
			unode->next = newnode;
			newnode->next = NULL;
			unode = unode->next;
			if (anode->next != NULL) anode = anode->next;
			else { // 만약 a가 더이상 진행할 수 없다면 b의 모든 원소를 합집합에 집어넣고 끝
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
		if (anode->elem == bnode->elem) { // 같을 경우 a의 원소를 집어넣고 둘다 다음단계로
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
			else if (anode->next == NULL) { // a가 끝인경우
				while (bnode->next != NULL) { // b를 끝날때 까지 집어넣고 끝낸다.
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
			else if (bnode->next == NULL) {//b가 끝인경우
				while (anode->next != NULL) { // a를 끌날때 까지 집어넣고 끝낸다.
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
	if (anode->next == NULL || bnode->next == NULL) { // 둘중 하나라도 0이라면 교집합은 성립될 수 없다.
		printf(" 0");
		return 0;
	}
	anode = anode->next;
	bnode = bnode->next;
	while (1) {
		if (anode->elem > bnode->elem) { // a가 더 큰 경우 b를 한칸 진행시키고 진행 시키지 못할경우 더 이상 같은 값은 없으니까 break
			if (bnode->next != NULL) bnode = bnode->next;
			else break;
		}
		if (anode->elem < bnode->elem) { // b가 더 큰 경우 a를 한칸 진행시키고 진행 시키지 못할경우 더 이상 같은 값은 없으니까 break
			if (anode->next != NULL) anode = anode->next;
			else break;
		}
		if (anode->elem == bnode->elem){ // 같은경우이므로 교집합에 집어넣는다.
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
			else break;// 둘중하나라도 다음 공간이 없다면 같은것이 없으므로 break이다.
		}
	}
}