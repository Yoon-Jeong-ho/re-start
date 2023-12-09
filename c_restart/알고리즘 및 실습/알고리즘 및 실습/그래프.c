#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
int  INF = 1000;

int Graph[1000][1000] = { {0} };
int p[1000] = { -1 }, adj_top = 0, d[1000] = { -1 };
int adj[1000] = { -1 }, minWeight = 0;


typedef struct vertices {
	int num;
	struct edgelist* list;
	int fresh;
	char name;
	int out;
}vertices;
typedef struct QNode {
	int element;
	struct QNode* next, * prev;
}QNode;
typedef struct Queue {
	struct QNode* head, * tail;
}Queue;
typedef struct edgelist {

	struct edgelist* next;
	int edge_num;
	int ver_num;
}edgelist;

typedef struct edge {
	int fresh, weight;
	int ver1, ver2;
}edge;
typedef struct graph {
	vertices* vertex;
	edge* edg;
	int edgnum;
}graph;
void grpinit(graph*, int, int,char*);
void insert(graph*, int, int, int, int);
int removeMin(Queue** q_ptr, int N);
void find_adj(int u, int N);
void PrimJarnikMST(int N, int M);
void inQueue(Queue* q,int i);
Queue* initQ();
int main() {
	graph grp;
	char tmp[1000];
	int ver1, ver2, weight, count = 0,c = 0,st,ed,wt;
	edgelist* list = NULL;
	int n, m, s, a, b;
	scanf("%d %d", &n, &m);
	grp.vertex = (vertices*)malloc(sizeof(vertices) * (n + 1));
	grp.edg = (edge*)malloc(sizeof(edge) * (m + 1));
	grpinit(&grp, n, m,tmp);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &st, &ed, &wt);
		insert(&grp, st, ed , wt,n);
	}
	
	return 0;
}



void PrimJarnikMST(int N, int M) {
	int u, z, i;
	Queue* q = initQ();
	for (i = 0; i <= N; i++) {
		d[i] = INF;
		p[i] = NULL;
	}
	d[1] = 0;
	for (i = 1; i <= N; i++) inQueue(q, i);
	while (!isEmpty(q)) {
		u = removeMin(&q, N);
		printf(" %d", u);
		minWeight += d[u];
		find_adj(u, N);
		for (i = 0; i < adj_top; i++) {
			z = adj[i];
			if (inQ(q, z) && Graph[u][z] < d[z])
			{
				p[z] = u;
				d[z] = Graph[u][z];
			}
			adj_top = 0;
		}
		printf("\n");
		freeQ(&q);
	}
}

void find_adj(int u, int N) {
	int i;
	for (i = 1; i <= N; i++) {
		if (Graph[u][i] != 0) {
			adj[adj_top++] = i;
		}
	}
}

void inQueue(Queue* q, int i) {
	QNode* head = q->head, * tmp = NULL, *nextq =NULL;
	tmp= (QNode*)malloc(sizeof(QNode));
	nextq = head->next;
	head->next = tmp;
}


Queue* initQ() {
	Queue* q = NULL;
	QNode* head = NULL, * tail = NULL;
	head = (QNode*)malloc(sizeof(QNode));
	tail = (QNode*)malloc(sizeof(QNode));
	q = (Queue*)malloc(sizeof(Queue));
	head->prev = NULL;
	head->next = tail;
	tail->next = NULL;
	tail->prev = head;
	q->head = head;
	q->tail = tail;
	return q;
}

int removeMin(Queue** q_ptr, int N) {
	Queue* q = *q_ptr;
	QNode* q_inst = q->head,*q_temp = NULL;
	int i;
	int minValue = INF, min_head;
	while (q_inst != NULL) {
		i = q_inst->element;
		if (d[i] < minValue) {
			minValue = d[i];
			min_head = i;
			q_temp = q_inst;
		}
		q_inst = q_inst->next;
	}
	if (q_temp == q->head && q_temp == q->tail) {
		q->head = NULL;
		q->tail = NULL;
		free(q_temp);
	}
	else if (q_temp == q->head && q_temp != NULL) {
		if (q_temp->next)
			q_temp->next->prev = NULL;
		(*q_ptr)->head = q_temp->next;
		free(q_temp);
	}
	else if (q_temp == q->tail && q_temp != NULL) {
		if (q_temp->prev)
			q_temp->prev->next = NULL;
		(*q_ptr)->tail = q_temp->prev;
		free(q_temp);
	}
	else {
		q_temp->prev->next = q_temp->next;
		q_temp->next->prev = q_temp->prev;
		free(q_temp);
	}
	return min_head;
}

void grpinit(graph* g, int n, int m, char* name) {
	for (int i = 1; i <= n; i++) {
		g->vertex[i].num = 0;
		g->vertex[i].list = (edgelist*)malloc(sizeof(edgelist));
		g->vertex[i].list->next = NULL;
		g->vertex[i].list->edge_num = 0;
		g->vertex[i].list->ver_num = 0;
		g->vertex[i].fresh = 0;
		g->vertex[i].name = name[i - 1];
		g->vertex[i].out = 0;
	}
	g->edgnum = 1;
}

void insert(graph* grp, int st, int en, int we, int n) {
	vertices* v1 = &(grp->vertex[st]), * v2 = &(grp->vertex[en]);
	edgelist* list1 = v1->list, * list2 = v2->list, * tmp = NULL, * prev = NULL;
	while (list1->ver_num < en && list1->next != NULL) {
		prev = list1;
		list1 = list1->next;
	}
	if (list1->ver_num > en) {
		tmp = (edgelist*)malloc(sizeof(edgelist));
		tmp->next = list1;
		prev->next = tmp;
	}
	else {
		tmp = (edgelist*)malloc(sizeof(edgelist));
		tmp->next = list1->next;
		list1->next = tmp;
	}
	tmp->ver_num = en;
	tmp->edge_num = grp->edgnum;


	while ((list2->ver_num == 0 || list2->ver_num < st) && list2->next != NULL) {
		prev = list2;
		list2 = list2->next;
	}

	if (st != en) {
		if (list2->ver_num > st) {
			tmp = (edgelist*)malloc(sizeof(edgelist));
			tmp->next = list2;
			prev->next = tmp;
		}
		else {
			tmp = (edgelist*)malloc(sizeof(edgelist));
			tmp->next = list2->next;
			list2->next = tmp;
		}
		tmp->ver_num = st;
		tmp->edge_num = grp->edgnum;

	}
	grp->edg[grp->edgnum].ver1 = st;
	grp->edg[grp->edgnum].ver2 = en;
	grp->edg[grp->edgnum].fresh = 0;
	grp->edg[grp->edgnum].weight = we;

	grp->edgnum = grp->edgnum + 1;
	v1->out = v1->out +1;
	v1->num = v1->num + 1;
	v2->num= v2->num +1;
	v2->out = v2->out + 1;

}