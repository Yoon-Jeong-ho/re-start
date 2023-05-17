//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//
//int size = 0;
//
//typedef struct node {
//	struct node* left;
//	int elem;
//	struct node* right;
//}node;
//
//int main() {
//	node* left, * right, * node2, * node3, * node6, * node7, * node8, * node1,*head,*head1;
//	left = (node*)malloc(sizeof(node));
//	right = (node*)malloc(sizeof(node));
//	node2 = (node*)malloc(sizeof(node));
//	node3 = (node*)malloc(sizeof(node));
//	node6 = (node*)malloc(sizeof(node));
//	node7 = (node*)malloc(sizeof(node));
//	node8 = (node*)malloc(sizeof(node));
//	node1 = (node*)malloc(sizeof(node));
//	left->left = NULL;
//	left->right = NULL;
//	right->left = NULL;
//	left->left = NULL;
//	left->elem = 70;
//	right->elem = 90;
//	node2->left = left;
//	node2->right = right;
//	node2->elem = 30;
//	node7->left = NULL;
//	node7->right = NULL;
//	node8->left = NULL;
//	node8->left = NULL;
//	node7->elem = 130;
//	node8->elem = 80;
//	node6->left = node7;
//	node6->right = node8;
//	node6->elem = 120;
//	node3->left = NULL;
//	node3->right = node6;
//	node3->elem = 50;
//	node1->left = node2;
//	node1->right = node3;
//	node1->elem = 20;
//	int n;
//	scanf("%d", &n);
//	head = node1;
//	if (n == 1) head = node1;
//	else if (n == 2) head = node2;
//	else if (n == 3) head = node3;
//	else if (n == 4) head = left;
//	else if (n == 5) head = right;
//	else if (n == 6) head = node6;
//	else if (n == 7) head = node7;
//	else if (n == 8) head = node8;
//	else {
//		printf("-1");
//		return 1;
//	}
//	head1 = head;
//	printf("%d ", head->elem);
//	if (head->left != NULL) {
//		head=head->left;
//		printf("%d ",head->elem);
//	}
//	if (head1->right != NULL) {
//		head1 = head1->right;
//		printf("%d ", head1->elem);
//	}
//	return 0;
//}
//
