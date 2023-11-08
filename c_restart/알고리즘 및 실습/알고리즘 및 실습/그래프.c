#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct vertices {
	int num;
	struct edgelist* list;

}vertices;

typedef struct edgelist {

	struct edgelist* next;
	int edge_num;
	int ver_num;
}edgelist;

typedef struct edge {
	int weight;
	int ver1, ver2;
}edge;
typedef struct graph {
	vertices vertex[7];
	edge edg[1000];
	int edgnum;
}graph;
void grpinit(graph*);
void printver(graph*, int);
void insert(graph*, int, int, int);
void delet(graph*, int, int);
int main() {
	graph grp;
	grpinit(&grp);
	char c;
	int ver1,ver2,weight;
	edgelist* list ;
	while (1) {
		scanf("%c", &c);
		if (c == 'q') break;
		else if (c == 'a') {
			scanf("%d",&ver1); getchar();
			if (ver1 > 6 || ver1 < 1) { printf("-1\n"); continue; }
			printver(&grp, ver1);
		}
		else if (c == 'm') {
			scanf("%d %d %d",&ver1,&ver2,&weight); getchar();
			if (ver1 > 6 || ver1 < 1 || ver2>6 || ver2 < 1) { printf("-1\n"); continue; }
			list = grp.vertex[ver1].list;
			while (1) {
				if (list->ver_num == ver2) break;
				else if (list->next != NULL)list = list->next;
				else break;
			}
			if (list->ver_num == ver2) {
				grp.edg[list->edge_num].weight = weight;
				if (weight == 0) {
					delet(&grp, ver1, ver2);
				}
			}
			else insert(&grp, ver1, ver2, weight);
		}
	}

	return 0;
}

void grpinit(graph* g) {
	for (int i = 1; i <= 6; i++) {
		g->vertex[i].num = i;
		g->vertex[i].list = (edgelist*)malloc(sizeof(edgelist));
		g->vertex[i].list->next = NULL;
		g->vertex[i].list->edge_num = 0;
		g->vertex[i].list->ver_num = 0;

	}
	g->edgnum = 0;
	insert(g, 1, 2, 1);
	insert(g, 1, 3, 1);
	insert(g, 1, 4, 1);
	insert(g, 1, 6, 2);
	insert(g, 2, 3, 1);
	insert(g, 3, 5, 4);
	insert(g, 5, 5, 4);
	insert(g, 5, 6, 3);
}

void printver(graph* grp, int st) {
	vertices *v = &(grp->vertex[st]);
	edgelist* list = v->list;
	if (list->next == NULL) {
		printf(-1);
		return;
	}

	while (list->next != NULL) {
		list = list->next;
		edge e = grp->edg[list->edge_num];
		if (e.ver1 == st) printf(" %d", e.ver2);
		else printf(" %d", e.ver1);
		printf(" %d", e.weight);
	}
	printf("\n");
}

void delet(graph* grp, int st, int en) {
	vertices* v1 = &(grp->vertex[st]), * v2 = &(grp->vertex[en]);
	edgelist* list1 = v1->list, * list2 = v2->list, * tmp;
	while ((list1->ver_num == 0 || list1->ver_num < en) && list1->next != NULL) {
		list1 = list1->next;
	}
	while ((list2->ver_num == 0 || list2->ver_num < st) && list2->next != NULL) {
		list2 = list2->next;
	}
	tmp = v1->list;
	while (tmp->next != list1) tmp = tmp->next;
	tmp->next = list1->next;
	free(list1);
	if (st != en) {
		tmp = v2->list;
		while (tmp->next != list2) tmp = tmp->next;
		tmp->next = list2->next;
		free(list2);
	}
}

void insert(graph* grp, int st, int en, int we) {
	vertices* v1 = &(grp->vertex[st]), *v2 = &(grp->vertex[en]);
	edgelist* list1 = v1->list, * list2 = v2->list, * tmp = NULL, * prev = NULL;
	while ((list1->ver_num == 0 || list1->ver_num < en) && list1->next != NULL) {
		prev = list1;
		list1 = list1->next;
	}
	if (list1->next == NULL && (list1->ver_num != 0 && list1->ver_num < en)) {
		tmp = (edgelist*)malloc(sizeof(edgelist));
		tmp->next = NULL;
		list1->next = tmp;
	}
	else if (list1->next == NULL && (list1->ver_num != 0 && list1->ver_num > en)) {
		list1 = prev;
		tmp = (edgelist*)malloc(sizeof(edgelist));
		tmp->next = list1->next;
		list1->next = tmp;
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
		if (list2->next == NULL && (list2->ver_num != 0 && list2->ver_num < st)) {
			tmp = (edgelist*)malloc(sizeof(edgelist));
			tmp->next = NULL;
			list2->next = tmp;
		}
		else if (list2->next == NULL && (list2->ver_num != 0 && list2->ver_num > st)) {
			list2 = prev;
			tmp = (edgelist*)malloc(sizeof(edgelist));
			tmp->next = list2->next;
			list2->next = tmp;
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
	grp->edg[grp->edgnum].weight = we;

	grp->edgnum = grp->edgnum + 1;

}