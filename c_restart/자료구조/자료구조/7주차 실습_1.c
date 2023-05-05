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
//	L = (list*)malloc(sizeof(list)); // ����Ʈ �����Ҵ�
//	node* A, * B;
//	A = (node*)malloc(sizeof(node)); // ��� �����Ҵ�
//	B = (node*)malloc(sizeof(node)); // �ι�° ��嵵 ���� �Ҵ�
//	L->firstnode= A;
//	L->secondnode = B;
//	A->next = NULL; // ������ �ּҰ� ���ٰ� �Ͽ���
//	B->next = NULL; // �������� �־���
//	int num, firstelem;
//	scanf("%d", &num); // �ݺ��� Ƚ��
//	
//	if (num != 0) {
//		scanf("%d", &firstelem); // ù��° ���� �Է¹޴´�.
//		A->elem = firstelem; //����ֱ�
//	}
//	else A->elem = 0;
//	for (int i = 0; i < num-1; i++) {
//		addfirstnode(L);
//	}
//	A = L->firstnode;// ���� ������ ����Ǹ鼭 ����Ʈ�� �۽�Ʈ ��� ���� ����Ǳ⵵ �ؼ� �ѹ� �� ����
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
//	B = L->secondnode;// ���� ������ ����Ǹ鼭 ����Ʈ�� �۽�Ʈ ��� ���� ����Ǳ⵵ �ؼ� �ѹ� �� ����
//	
//	printf("%d",subset(A, B));
//	return 0;
//}
//
//int subset(node* A, node *B) {
//	int num=0;
//	while (1) {
//		while (B->elem > A->elem && B->next != NULL)B = B->next; // B���Ұ� ū ��� �׳� ���� ����
//		while (B->elem < A->elem && A->next != NULL) {  // A���Ұ� ū ��� num�ٲٰ� ����
//			num = A->elem;
//			A = A->next;
//		}
//		while (B->elem == A->elem && A->next != NULL && B->next != NULL) { // ���� ���� ������ ���� ������ ��� �Ѵ� �������� ����
//			A = A->next;
//			B = B->next;
//		}
//		if (A->next == NULL) { // A������ ���°��
//			while (B->next != NULL) { // B������ ����������
//				if (A->elem == B->elem) break; // A�� B�� ������ ������.(�� ���Ĵ� B�� ���� �۾����鼭 ������ �����)
//				else if (A->elem > B->elem)num = A->elem; // A�� num��A�̴�.
//				B = B->next;
//			}
//			if (A->elem > B->elem)num = A->elem;
//			break;
//		}
//		if (B->next == NULL) { // b�� �������ϰ�� ������ A���̶��� ���ϸ� �ּڰ��� �� �� �ֵ�.
//			while (A->next != NULL) {
//				A = A->next;
//			}
//			if (A->elem != B->elem) num = A->elem; // ���� �ʴٸ� �ּڰ��� A�� ���̴�.
//		}
//		if (A->next == NULL && B->next == NULL) { // �������ϰ��
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
//	newnode = (node*)malloc(sizeof(node)); // ���� ����� ���
//	newnode->elem = num;
//	while (A->next != NULL && A->elem > num) {
//		A = A->next;
//		count++; // Ƚ���� ���� �������� ����.
//	}
//	for (int i = 0; i < count - 1; i++) {
//		prevnode = prevnode->next; // �������� ���� ���ο� ���� ���� �̾��ش�.
//	}
//	if (count == 0 && A->elem < num) {// ���ο� ��尡 ���� ū ���
//		newnode->next = A;
//		L->firstnode = newnode;
//	}
//	else if (count == 0 && A->elem > num) A->next = newnode, newnode->next = NULL; // ���ο� ��尡 A���� ������ �ι�° ����� ���
//	else if (A->next == NULL && A->elem > num) { // �� ���� ���Ϲ����� and������ NULL�������� ��������̴�. �� A ���� �� ��尡 �;ߵȴ�.
//		A->next = newnode;
//		newnode->next = NULL;
//	}
//	else {// ������� -> ���ο� ��� -> A�ΰ��
//		newnode->next = prevnode->next;
//		prevnode->next = newnode;
//	} 
//}
//void addsecondnode(list* L) { // �ռ� ù ���� �˰����� ����.
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
//	if (count == 0 && B->elem < num) {// ���ο� ��尡 ���� ū ���
//		newnode->next = B;
//		L->secondnode = newnode;
//	}
//	else if (count == 0 && B->elem > num) B->next = newnode, newnode->next = NULL; // ���ο� ��尡 A���� ������ �ι�° ����� ���
//	else if (B->next == NULL && B->elem > num) { // �� ���� ���Ϲ����� and������ NULL�������� ��������̴�. �� B ���� �� ��尡 �;ߵȴ�.
//		B->next = newnode;
//		newnode->next = NULL;
//	}
//	else {// ������� -> ���ο� ��� -> B�ΰ��
//		newnode->next = prevnode->next;
//		prevnode->next = newnode;
//	}
//}