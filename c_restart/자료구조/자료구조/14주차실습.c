//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct node {
//	struct node* left;
//	int elem;
//	struct node* right;
//}node;
//
//node* findnode(node* node1,int m);
//void maketree(node* node1, int m1, int m2, int m3);
//int main() {
//	int n,m[3];
//	char c[100];
//	scanf("%d", &n);
//	scanf("%d %d %d", &m[0], &m[1], &m[2]);
//	node* node1, * node2, * node3,*a;
//	node1 = (node*)malloc(sizeof(node));
//	node2 = (node*)malloc(sizeof(node));
//	node3 = (node*)malloc(sizeof(node));
//	node1->left = node2;
//	node1->right = node3;
//	node1->elem = m[0];
//	node2->elem = m[1];
//	node3->elem = m[2];
//	node2->left = NULL;
//	node2->right = NULL;
//	node3->left = NULL;
//	node3->right = NULL;
//	for (int i = 0; i < n - 1; i++) {
//		scanf("%d %d %d", &m[0], &m[1], &m[2]);
//		a = findnode(node1,m[0]);
//		maketree(a, m[0], m[1], m[2]);
//	}
//	scanf("%d", &n);
//	for (int i = 0; i < n; i++) {
//		scanf("%s", &c);
//		printf(" %d", node1->elem);
//		a = node1;
//		for (int j = 0; j < strlen(c); j++) {
//			if (c[j] == 'R') a = a->right;
//			else a=a->left;
//			printf(" %d", a->elem);
//		}
//		printf("\n");
//	}
//	return 0;
//}
//
////node* findnode(node* node1,int m) {
////	node* right, * left;
////	if (node1->elem == m) return node1;
////	if (node1->left != NULL) {
////		left = findnode(node1->left, m);		
////		if (left->elem == m) return left;
////	}
////	if (node1->right != NULL) {
////		right = findnode(node1->right, m);
////		if (right->elem == m) return right;
////	}
////	return NULL;
////}
//node* findnode(node* node1, int m) {
//	if (node1 == NULL)
//		return NULL;
//
//	if (node1->elem == m)
//		return node1;
//
//	node* leftResult = findnode(node1->left, m);
//	if (leftResult != NULL)
//		return leftResult;
//
//	node* rightResult = findnode(node1->right, m);
//	if (rightResult != NULL)
//		return rightResult;
//
//	return NULL;
//}
//void maketree(node* a, int m1, int m2, int m3) {
//	if (m2 != 0) {
//		node* leftnode = (node*)malloc(sizeof(node));
//		leftnode->left = NULL;
//		leftnode->right = NULL;
//		leftnode->elem = m2;
//		a->left = leftnode;
//	}
//	if (m3 != 0) {
//		node* rightnode = (node*)malloc(sizeof(node));
//		rightnode->left = NULL;
//		rightnode->right = NULL;
//		rightnode->elem = m3;
//		a->right = rightnode;
//	}
//}