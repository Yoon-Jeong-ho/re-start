#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct node {
    int elem;
    struct node* right; // ���� ��� �ּ� ����
    struct node* left;
    struct node* parent;
    //int height;
}node;

node* root= NULL;

typedef struct {
    node* head;
    int lenlist;
}list;

void insert(int n);
int delet(int n);
node* serch(int n, node*);
void print(node *);

int main() {
    int n, result;
    node* w;
    char c;
    while (1) {
        scanf("%c", &c);
        if (c == 'q') break;
        else if (c == 'i') {
            scanf("%d", &n); getchar();
            insert(n);
        }
        else if (c == 'd') {
            scanf("%d", &n); getchar();
            result = delet(n);
            if (result == n) printf("%d\n", n);
            else printf("X\n");
        }
        else if (c == 's') {
            scanf("%d", &n); getchar();
            w = serch(n,root);
            if (w->elem == n) printf("%d\n", n);
            else printf("X\n");
        }
        else if (c == 'p') {
            getchar();
            print(root);
            printf("\n");
        }
    }


    return 0;
}


void insert(int n) {
    node* newnode,*prevnode;
    if (root == NULL) {
        newnode = (node*)malloc(sizeof(node));
        root = newnode;
        newnode->parent = NULL;

    }
    else {
        prevnode = serch(n,root);
        newnode = (node*)malloc(sizeof(node));
        if (prevnode -> elem < n)prevnode->right = newnode;
        else prevnode->left = newnode;
        newnode->parent = prevnode;
    }
    newnode->elem = n;
    newnode->right = NULL;
    newnode->left = NULL;
}
int delet(int n) {
    node* delnode,*prevnode , *w,* nextnode;
    delnode = serch(n, root);
    int result;
    if (delnode == NULL) return 0;
    result = delnode->elem; 
    if (n != result) return result;
    if (delnode->right == NULL && delnode->left == NULL) {// �Ѵ� ���� ���
        if (delnode == root) {
            root = NULL;
            free(delnode);
        }
        else {
            w = delnode->parent;
            if (w->left == delnode) w->left = NULL;
            else  w->right = NULL;
            free(delnode);
        }
    }
    else if (delnode->right == NULL) { // ���� �ڽĸ� �ִ� ���

        if (delnode == root) {
            root = delnode->left;
            root->parent = NULL;
            free(delnode);
        }
        else { // ��Ʈ�� �ƴѰ��
            prevnode = delnode->parent;
            if (prevnode->left == delnode) { // �θ��� ���� �ڽ��� ���
                w = delnode->left;
                w->parent = prevnode;
                prevnode->left = w;
                free(delnode);
            }
            else { // ������ �ڽ��� ���
                w = delnode->left;
                w->parent = prevnode;
                prevnode->right = w;
                free(delnode);
            }
        }
    }
    else if (delnode->left == NULL) { // ���� �� �ڽĸ� �ִ� ���

        if (delnode == root) {
            root = delnode->right;
            root->parent = NULL;
            free(delnode);
        }
        else {
            prevnode = delnode->parent;
            if (prevnode->left == delnode) { // �θ��� ���� �ڽ��� ���
                w = delnode->right;
                w->parent = prevnode;
                prevnode->left = w;
                free(delnode);
            }
            else { // ������ �ڽ��� ���
                w = delnode->right;
                w->parent = prevnode;
                prevnode->right = w;
                free(delnode);
            }
        }
    }
    else { // �ΰ� �� �������
        w = delnode->right;
        while (w->left != NULL) {
            w = w->left;
        }
        if (w->parent == root) { // �ٷ� �����ʿ��� �������
            delnode->elem = w->elem;
            delnode->right = NULL;
            free(w);
        }
        else if (w->right == NULL) { //���� ��� �������� ���� ���
            prevnode = w->parent;
            delnode->elem = w->elem;
            prevnode->left = NULL;
            free(w);
        }
        else { // �Ϻ��ϰ� �ű�� �Ǵ� ���
            prevnode = w->parent;
            nextnode = w->right;
            prevnode->left = nextnode;
            nextnode->parent = prevnode;
            delnode->elem = w->elem;
            free(w);
        }
    }
    return result;
}
node* serch(int n, node* w) {
    if (w == NULL) return NULL;
    if (w->elem == n) return w;
    
    else if (w->elem > n && w->left != NULL) return serch(n, w->left);

    else if (w->elem < n && w->right != NULL) return serch(n, w->right);
    
    else return w;
}
void print(node * w) {
    if (w == NULL) return;
    printf(" %d", w->elem);

    if (w->left != NULL)print(w->left);
    if (w->right != NULL)print(w->right);   

}