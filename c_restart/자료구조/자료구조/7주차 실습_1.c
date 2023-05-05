//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct node {
//	int elem;	
//	struct node* next;
//}node;
//
//typedef struct list {
//	node* firstnode;
//	node* secondnode;
//}list;
//
//int subset(node *A, node *B);
//void addfirstnode(list *L);
//void addsecondnode(list* L);
//int main() {
//	list* L;
//	L = (list*)malloc(sizeof(list)); // 리스트 동적할당
//	node* A, * B;
//	A = (node*)malloc(sizeof(node)); // 노드 동적할당
//	B = (node*)malloc(sizeof(node)); // 두번째 노드도 동적 할당
//	L->firstnode= A;
//	L->secondnode = B;
//	A->next = NULL; // 다음은 주소가 없다고 하였따
//	B->next = NULL; // 문제에서 주어짐
//	int num, firstelem;
//	scanf("%d", &num); // 반복할 횟수
//	
//	if (num != 0) {
//		scanf("%d", &firstelem); // 첫번째 원소 입력받는다.
//		A->elem = firstelem; //집어넣기
//	}
//	else A->elem = 0;
//	for (int i = 0; i < num-1; i++) {
//		addfirstnode(L);
//	}
//	A = L->firstnode;// 위의 과정이 실행되면서 리스트의 퍼스트 노드 값이 변경되기도 해서 한번 더 정의
//
//	scanf("%d", &num);
//
//	if (num != 0) {
//		scanf("%d", &firstelem);
//		B->elem = firstelem;
//	}
//	else B->elem = 0;
//	for (int i = 0; i < num - 1; i++) {
//		addsecondnode(L);
//	}
//	
//	B = L->secondnode;// 위의 과정이 실행되면서 리스트의 퍼스트 노드 값이 변경되기도 해서 한번 더 정의
//	
//	printf("%d",subset(A, B));
//	return 0;
//}
//
//int subset(node* A, node *B) {
//	int num=0;
//	while (1) {
//		while (B->elem > A->elem && B->next != NULL)B = B->next; // B원소가 큰 경우 그냥 다음 진행
//		while (B->elem < A->elem && A->next != NULL) {  // A원소가 큰 경우 num바꾸고 진행
//			num = A->elem;
//			A = A->next;
//		}
//		while (B->elem == A->elem && A->next != NULL && B->next != NULL) { // 둘이 같고 다음이 진행 가능할 경우 둘다 다음으로 진행
//			A = A->next;
//			B = B->next;
//		}
//		if (A->next == NULL) { // A다음이 없는경우
//			while (B->next != NULL) { // B다음이 없을때까지
//				if (A->elem == B->elem) break; // A와 B가 같으면 끝난다.(그 이후는 B는 점점 작아지면서 오류가 생긴다)
//				else if (A->elem > B->elem)num = A->elem; // A가 num은A이다.
//				B = B->next;
//			}
//			if (A->elem > B->elem)num = A->elem;
//			break;
//		}
//		if (B->next == NULL) { // b가 마지막일경우 마지막 A값이랑만 비교하면 최솟값을 알 수 있따.
//			while (A->next != NULL) {
//				A = A->next;
//			}
//			if (A->elem != B->elem) num = A->elem; // 같지 않다면 최솟값인 A가 답이다.
//		}
//		if (A->next == NULL && B->next == NULL) { // 마지막일경우
//			if (A->elem > B->elem) num = A->elem;
//			break;
//		}
//	}
//
//	return num;
//}
//void addfirstnode(list *L) {
//	int num,count =0;
//	scanf("%d", &num);
//	node* newnode, * prevnode, *A;
//	A = L->firstnode;
//	prevnode = A;
//	newnode = (node*)malloc(sizeof(node)); // 새로 만드는 노드
//	newnode->elem = num;
//	while (A->next != NULL && A->elem > num) {
//		A = A->next;
//		count++; // 횟수를 세서 직전까지 간다.
//	}
//	for (int i = 0; i < count - 1; i++) {
//		prevnode = prevnode->next; // 직전으로 가서 새로운 노드랑 노드랑 이어준다.
//	}
//	if (count == 0 && A->elem < num) {// 새로운 노드가 가장 큰 경우
//		newnode->next = A;
//		L->firstnode = newnode;
//	}
//	else if (count == 0 && A->elem > num) A->next = newnode, newnode->next = NULL; // 새로운 노드가 A보단 작지만 두번째 노드인 경우
//	else if (A->next == NULL && A->elem > num) { // 이 경우는 와일문에서 and문에서 NULL값때문에 끝난경우이다. 즉 A 다음 뉴 노드가 와야된다.
//		A->next = newnode;
//		newnode->next = NULL;
//	}
//	else {// 이전노드 -> 새로운 노드 -> A인경우
//		newnode->next = prevnode->next;
//		prevnode->next = newnode;
//	} 
//}
//void addsecondnode(list* L) { // 앞선 첫 노드랑 알고리즘이 같다.
//	int num, count = 0;
//	scanf("%d", &num);
//	node* newnode, * prevnode, * B;
//	B = L->secondnode;
//	prevnode = B;
//	newnode = (node*)malloc(sizeof(node));
//	newnode->elem = num;
//	while (B->next != NULL && B->elem > num) {
//		B = B->next;
//		count++;
//	}
//	for (int i = 0; i < count - 1; i++) {
//		prevnode = prevnode->next;
//	}
//	if (count == 0 && B->elem < num) {// 새로운 노드가 가장 큰 경우
//		newnode->next = B;
//		L->secondnode = newnode;
//	}
//	else if (count == 0 && B->elem > num) B->next = newnode, newnode->next = NULL; // 새로운 노드가 A보단 작지만 두번째 노드인 경우
//	else if (B->next == NULL && B->elem > num) { // 이 경우는 와일문에서 and문에서 NULL값때문에 끝난경우이다. 즉 B 다음 뉴 노드가 와야된다.
//		B->next = newnode;
//		newnode->next = NULL;
//	}
//	else {// 이전노드 -> 새로운 노드 -> B인경우
//		newnode->next = prevnode->next;
//		prevnode->next = newnode;
//	}
//}