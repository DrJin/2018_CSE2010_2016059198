#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct Graph {
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
	int n; //vertex의 수
}Graph;

void init(Graph *g) {
	int i, j;
	g->n = 0;
	for (i = 0; i < MAX_VERTICES; i++)
		for (j = 0; j < MAX_VERTICES; j++)
			g->adjMatrix[i][j] = 0;
}

void insertVertex(Graph *g) {
	if (g->n == MAX_VERTICES) {
		printf("vertex가 너무 많습니다. 삽입 불가\n");
		return;
	}
	g->n++;
}

void insertEdge(Graph *g, int u, int v) {
	if (u >= g->n || v >= g->n) {
		printf("위치 잘못됨, (0~N-1)\n");
		return;
	}
	g->adjMatrix[u][v] = TRUE;
	g->adjMatrix[v][u] = TRUE;
}

void dfs(Graph *g, int v) {
	int i;
	visited[v] = TRUE;
	printf("%d ->", v);
	for (i = 0; i < MAX_VERTICES; i++) {
		//인접 행렬의 값이 1이면 연결된 노드가 있음, visited가 FALSE이면 탐색하지 않았으므로 탐색
		if (g->adjMatrix[v][i] == TRUE && visited[i] == FALSE)
			dfs(g, i);
	}

}

int main() {
	int i = 0;
	Graph g;

	init(&g);
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = FALSE;
	for (i = 0; i < 7; i++) insertVertex(&g);

	insertEdge(&g, 0, 4);
	insertEdge(&g, 0, 6);
	insertEdge(&g, 1, 3);
	insertEdge(&g, 3, 5);
	insertEdge(&g, 4, 1);
	insertEdge(&g, 4, 2);
	insertEdge(&g, 6, 2);

	dfs(&g, 0);
	return 0;
}