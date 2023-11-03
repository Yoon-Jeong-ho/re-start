#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct node {
    int elem;
    struct node* right; // 다음 노드 주소 저장
    struct node* left;
    struct node* parent;
    int height;
}node;

typedef struct {
    node* head;
    int lenlist;
}list;

node* root;

void expandExternal(node*);
int isInternal(node*);
int isExternal(node*);
int isRoot(node*);
node* sibling(node*);
node* inOrderSucc(node*);
node* reduceExternal(node*);
void InsertItem(int);
void searchAndFixAfterInsertion(node*);
int isAncestor(node*, node*);
int heightUpdateAndBalanceCheck(node*);
node* restructure(node*);
node* search(int, node*);
void print(node*);



int main() {
    int n, result;
    node* w,*tmp;
    w = (node*)malloc(sizeof(node));
    w->parent = NULL;
    w->elem = 0;
    w->left = NULL;
    w->right = NULL;
    w->height = 0;
    root = w;
    char c;
    while (1) {
        scanf("%c", &c);
        if (c == 'q') break;
        else if (c == 'i') {
            scanf("%d", &n); getchar();
            InsertItem(n);
        }
        //else if (c == 'd') {
        //    scanf("%d", &n); getchar();
        //    result = delet(n);
        //    if (result == n) printf("%d\n", n);
        //    else printf("X\n");
        //}
        else if (c == 's') {
            scanf("%d", &n); getchar();
            tmp = search(n,root);
            if (tmp != NULL &&tmp->elem == n) printf("%d\n", n);
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

int isInternal(node* w) {
    if (w->left == NULL && w->right == NULL) return 0;
    else return 1;
}
//int isExternal(node* w) {
//    if (w == NULL || (w->left == NULL && w->right == NULL)) return 1;
//    else return 0;
//}
int isExternal(node* a) {
    if (a->left == NULL && a->right == NULL)return 1;
    else return 0;
}
int isRoot(node* w) {
    if (w->parent == NULL) return 1;
    else return 0;
}
node* sibling(node*p) {
    if (p->parent->left == p)
        return p->parent->right;
    else
        return p->parent->left;
}
node* inOrderSucc(node* w) {
    w = w->right;
    if (isExternal(w)) return NULL;
    while (isInternal(w->left)) w = w->left;
    return w;
}
node* reduceExternal(node* z) {
    node* w = z->parent, *zs = sibling(z),*g;
    if (isRoot(w)) {
        root = zs;
        zs->parent = NULL;
    }
    else {
        g = w->parent;
        zs->parent = g;
        if (w == g->left) g->left = zs;
        else g->right = zs;
    }
    free(z);
    free(w);
    return zs;
}
void expandExternal(node* w) {
    node* l, * r;
    l = (node*)malloc(sizeof(node));
    r = (node*)malloc(sizeof(node));
    l->left = NULL;
    l->right = NULL;
    r->parent = w;
    l->parent = w;
    l->height = 0;
    r->height = 0;
    r->left = NULL;
    r->right = NULL;
    w->left = l;
    w->right = r;
    w->height = 1;
}
void InsertItem(int k) {
    node* w;
    w = search(k, root);
    if (isInternal(w))return;
    else {
        w->elem = k;
        expandExternal(w);
        searchAndFixAfterInsertion(w);
    }
}
void searchAndFixAfterInsertion(node* w) {
    node* z = w;
    node* y, *x;
    while (heightUpdateAndBalanceCheck(z)) {
        if (z == NULL) return;
        z = z->parent;
    }
    if (z->left->height > z->right->height) y = z->left;
    else y = z->right;
    if (y->left->height > y->right->height) x = y->left;
    else if (y->left->height < y->right->height) x = y->right;
    else {
        if (isAncestor(y->left, w))
            x = y->left;
        else
            x = y->right;
    }
    restructure(x);
}
int isAncestor(node* a, node* b) {
    node* p = b;
    while (a != b && p != root) p = p->parent;
    return a == p;
}
int heightUpdateAndBalanceCheck(node* w) {
    node* l, * r;
    int b;
    if (w == NULL) return 1;
    l = w->left;
    r = w->right;
    w->height = max(r->height, l->height) + 1;
    b = r->height - l->height;
    if (b * b < 2) return 1;
    else return 0;
}
node* restructure(node* x) {
    node* y = NULL, * z = NULL, * a = NULL, * b = NULL, * c = NULL, * t0 = NULL, * t1 = NULL, * t2 = NULL, * t3=NULL;
    y = x->parent;
    z = y->parent;
    if (z->elem < y->elem && y->elem < x->elem) {
        a = z;
        b = y;
        c = x;
        t0 = a->left;
        t1 = b->left;
        t2 = c->left;
        t3 = c->right;
    }
    else if (x->elem < y->elem && y->elem < z->elem) {
        a = x;
        b = y;
        c = z;
        t0 = a->left;
        t1 = a->right;
        t2 = b->right;
        t3 = c->right;
    }
    else if (z->elem < x->elem && x->elem < y->elem) {
        a = z;
        b = x;
        c = y;
        t0 = a->left;
        t1 = b->left;
        t2 = b->right;
        t3 = c->right;
    }

    if (z == root) {
        root = b;
        b->parent = NULL;
    }
    else if (z->parent->left == z) {
        z->parent->left = b;
        b->parent = z->parent;
    }
    else {
        z->parent->right = b;
        b->parent = z->parent;
    }
    a->left = t0;
    t0->parent = a;
    a->right = t1;
    t1->parent = a;
    a->height = max(t0->height, t1->height) + 1;
    c->left = t2;
    t2->parent = c;
    c->right = t3;
    t3->parent = c;
    c->height = max(t2->height, t3->height) + 1;
    b->left = a;
    a->parent = b;
    b->right = c;
    c->parent = b;
    b->height = max(a->height, c->height) + 1;
    return b;
}
node* search(int k , node* w) {
    if (isExternal(w)) return w;

    if (w->elem > k) return search(k,w->left);
    else if (w->elem < k) return search(k,w->right);
    else return w;
}

void print(node* w) {
    if (w == NULL||isExternal(w)) return;


    printf(" %d",w->elem);
    print(w->left);
    print(w->right);
}