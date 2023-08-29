//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct node {
//	struct node* left;
//	int elem;
//	int id;
//	struct node* right;
//}node;
//
//typedef struct {
//	node* head1;
//}list;
//
//int preorder(node* a);
//
//int main() {
//	node* node1, * node2, * node3, * node4, * node5, * node6, * node7, * node8, * a;
//	node4 = (node*)malloc(sizeof(node));
//	node5 = (node*)malloc(sizeof(node));
//	node2 = (node*)malloc(sizeof(node));
//	node3 = (node*)malloc(sizeof(node));
//	node6 = (node*)malloc(sizeof(node));
//	node7 = (node*)malloc(sizeof(node));
//	node8 = (node*)malloc(sizeof(node));
//	node1 = (node*)malloc(sizeof(node));
//	list* L;
//	L = (list*)malloc(sizeof(list));
//	node1->id = 1;
//	node1->left = node2;
//	node1->right = node3;
//	node1->elem = 20;
//	node2->id = 2;
//	node2->left = node4;
//	node2->right = node5;
//	node2->elem = 30;
//	node3->id = 3;
//	node3->left = NULL;
//	node3->right = node6;
//	node3->elem = 50;
//	node4->id = 4;
//	node4->left = NULL;
//	node4->right = NULL;
//	node4->elem = 70;
//	node5->id = 5;
//	node5->left = NULL;
//	node5->right = NULL;
//	node5->elem = 90;
//	node6->id = 6;
//	node6->left = node7;
//	node6->right = node8;
//	node6->elem = 120;
//	node7->id = 7;
//	node7->left = NULL;
//	node7->right = NULL;
//	node7->elem = 130;
//	node8->id = 8;
//	node8->left = NULL;
//	node8->right = NULL;
//	node8->elem = 80;
//	L->head1 = node1;
//	int m,result=0;
//	scanf("%d", &m);
//	if (m == 1) a = node1;
//	else if (m == 2) a = node2;
//	else if (m == 3) a = node3;
//	else if (m == 4) a = node4;
//	else if (m == 5) a = node5;
//	else if (m == 6) a = node6;
//	else if (m == 7) a = node7;
//	else a = node8;
//
//	if (m < 1 || m > 8) printf("-1");
//	else {
//		printf("%d",preorder(a));
//	}
//
//	return 0;
//}
//
//
//int preorder(node* a) {
//	if (a->left == NULL && a->right == NULL) return a->elem;
//	else if (a->left == NULL) return a->elem + preorder(a->right);
//	else if (a->right == NULL) return a->elem + preorder(a->left);
//	else return a->elem + preorder(a->right) + preorder(a->left);
//}
