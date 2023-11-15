#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
typedef struct Edge {
	int fresh;
	int vertex1, verxtex2;
}Edge;
typedef struct Vertex {
	int num;
	int fresh;
}Vertex;

typedef struct Graph {
	Vertex* v;
	Edge* e;
	int** adfacencyMatrix;
}Graph;

void insert(Graph*, int, int,int );
void initGraph(Graph*, int, int);
void BFS(Graph*, int, int, int);
int main() {
	Graph grp;
	char c;
	int ver1, ver2, weight;
	int n, m, s, a, b;
	scanf("%d %d %d", &n, &m, &s);
	grp.e = (Edge*)malloc(sizeof(Edge) * (m + 1));
	grp.v = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
	initGraph(&grp, n, m);

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		insert(&grp, a, b, i);
	}
	BFS(&grp, n,m,s);
	return 0;
}
void insert(Graph* g, int n, int m, int w) {
	g->e[w].vertex1 = n;
	g->e[w].verxtex2 = m;
	g->e[w].fresh = 0;
	g->adfacencyMatrix[n - 1][m - 1] = 0;
	g->adfacencyMatrix[m - 1][n - 1] = 0;

}

void initGraph(Graph* g, int n, int m) {
	for (int i = 0; i < n; i++) {
		g->v[i].num = i + 1;
		g->v[i].fresh = 0;
	}
	for (int i = 0; i < m; i++) g->e[i].fresh = 0;
	g->adfacencyMatrix = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) {
		g->adfacencyMatrix[i] = (int*)malloc(sizeof(int) * n);
		for (int j = 0; j < n; j++) {
			g->adfacencyMatrix[i][j] = -1;
		}

	}
}
void BFS(Graph* g, int n, int m, int s) {
	int* temp;
	temp = (int*)malloc(sizeof(int) * n);
	int cnt = 0;
	int currentCnt = 0;
	memset(temp, 0, sizeof(int) * n);
	temp[cnt] = s;
	cnt++;
	g->v[s - 1].fresh = 1;
	printf("%d\n", s);
	while (currentCnt < n) {
		for (int i = 0; i < n; i++) {
			if(temp[currentCnt]!= 0)
				if (g->adfacencyMatrix[temp[currentCnt]-1][i] != -1) {
					if (g->v[i].fresh == 0) {
						g->v[i].fresh = 1;
						temp[cnt] = i + 1;
						cnt++;
						printf("%d\n", g->v[i].num);
					}
			}
		}
		currentCnt++;
	}
}