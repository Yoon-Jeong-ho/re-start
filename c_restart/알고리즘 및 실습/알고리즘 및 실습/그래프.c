#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct vertices {
	int num;
	struct edgelist* list;
	int fresh;
	char name;
	int out;
}vertices;

typedef struct edgelist {

	struct edgelist* next;
	int edge_num;
	int ver_num;
}edgelist;

typedef struct edge {
	int fresh;
	int ver1, ver2;
}edge;
typedef struct graph {
	vertices* vertex;
	edge* edg;
	int edgnum;
}graph;
void grpinit(graph*, int, int,char*);
void insert(graph*, char, char, int);


int main() {
	graph grp;
	char tmp[1000],st,ed;
	int ver1, ver2, weight, count = 0,c = 0;
	edgelist* list = NULL;
	int n, m, s, a, b;
	scanf("%d", &n); getchar();
	for (int i = 0; i < n; i++) {
		scanf("%c", &tmp[i]); getchar();
	}
	scanf("%d", &m); getchar();
	grp.vertex = (vertices*)malloc(sizeof(vertices) * (n + 1));
	grp.edg = (edge*)malloc(sizeof(edge) * (m + 1));
	grpinit(&grp, n, m,tmp);

	for (int i = 0; i < m; i++) {
		scanf("%c %c", &st,&ed); getchar();
		insert(&grp, st, ed , n);
	}
	for (int i = 1; i <= n; i++) {
		if (grp.vertex[i].num == 0) break;
		if (i == n) {
			printf("0\n"); return 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (grp.vertex[i].num == 0) {
			tmp[count++] = i;
		}
	}
	while (c < n) {
		list = grp.vertex[tmp[c]].list;
		for (int i = 0; i < grp.vertex[tmp[c]].out; i++) {
			//printf("지우는 중\n");
			list = list->next;
			grp.vertex[list->ver_num].num = grp.vertex[list->ver_num].num -1;
			//printf("%d %d\n", list->ver_num,grp.vertex[list->ver_num].num);
			if (grp.vertex[list->ver_num].num == 0) tmp[count++] = list->ver_num;
			else if (grp.vertex[list->ver_num].num < 0) {
				printf("0\n"); return 0;
			}
		}
		c++;
	}
	if (count != n) { printf("0\n"); return 0; }
	for (int i = 0; i < n; i++)printf("%c ", grp.vertex[tmp[i]].name);
	return 0;
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

void insert(graph* grp, char st, char en, int we) {
	vertices* v1= NULL, * v2 = NULL;
	int a = 0;
	for (int i = 1; i <= we; i++) {
		if (grp->vertex[i].name == st) {
			v1 = &(grp->vertex[i]);
		}
		if (grp->vertex[i].name == en) {
			v2 = &(grp->vertex[i]);
			a = i;
		}
	}
	edgelist* list1 = v1->list, * list2 = v2->list, * tmp = NULL, * prev = NULL;
	prev = list1;
	list1 = list1->next;
	v1->out = v1->out +1;
	tmp = (edgelist*)malloc(sizeof(edgelist));
	tmp->next = list1;
	prev->next = tmp;

	tmp->ver_num = a;
	tmp->edge_num = grp->edgnum;
	v2->num= v2->num +1;

	grp->edg[grp->edgnum].ver1 = st;
	grp->edg[grp->edgnum].ver2 = en;
	grp->edg[grp->edgnum].fresh = 0;

	grp->edgnum = grp->edgnum + 1;

}