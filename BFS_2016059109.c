#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct Graph {
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
	int n; //vertex의 수
}Graph;

typedef struct Queue {
	int queue[MAX_SIZE + 1];
	int rear;
	int front;
}Queue;

void init(Graph *g) {
	int i, j;
	g->n = 0;
	for (i = 0; i < MAX_VERTICES; i++)
		for (j = 0; j < MAX_VERTICES; j++)
			g->adjMatrix[i][j] = 0;
}
void initQueue(Queue* q) {
	q->front = 0;
	q->rear = 0;
}

void insertVertex(Graph *g) {
	if (g->n == MAX_VERTICES) {
		printf("vertex가 너무 많습니다. 삽입 불가\n");
		return;
	}
	g->n++;
}

void insertEdges(Graph *g, int u, int v) {
	if (u >= g->n || v >= g->n) {
		printf("위치 잘못됨, (0~N-1)\n");
		return;
	}
	g->adjMatrix[u][v] = TRUE;
	g->adjMatrix[v][u] = TRUE;
}
//큐
int isFull(Queue* q) {
	if ((q->rear + 1) % MAX_SIZE == q->front)
		return 1;
	else
		return 0;
}

int isEmpty(Queue*q) {
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

void enqueue(Queue* q, int data) {
	if (isFull(q))
		printf("큐가 가득 참\n");
	else {
		q->queue[q->rear] = data;
		q->rear = (q->rear + 1) % MAX_SIZE;
	}
}

int dequeue(Queue* q) {
	int tmp = -1;
	if (isEmpty(q))
		printf("큐가 비어잇음\n");
	else {
		tmp = q->queue[q->front];
		q->front = (q->front + 1) % MAX_SIZE;
	}
	return tmp;
}

void bfs(Graph*g, int v) {
	int w, search_v;
	Queue q;
	initQueue(&q);
	visited[v] = TRUE;
	enqueue(&q, v);
	while (!isEmpty(&q)) {
		search_v = dequeue(&q);
		printf("%d->", search_v);

		for (w = 0; w < MAX_VERTICES; w++)
		{
			if (g->adjMatrix[search_v][w] == 1 && visited[w] == FALSE) {
				visited[w] = TRUE;
				enqueue(&q, w);

			}
		}
	}
}
int main() {
	int i = 0;
	Graph g;

	init(&g);

	for (i = 0; i < MAX_VERTICES; i++)visited[i] = FALSE;
	for (i = 0; i < 7; i++)insertVertex(&g);
	insertEdges(&g, 0, 4);
	insertEdges(&g, 0, 6);
	insertEdges(&g, 1, 3);
	insertEdges(&g, 3, 5);
	insertEdges(&g, 4, 1);
	insertEdges(&g, 4, 2);
	insertEdges(&g, 6, 2);
	bfs(&g, 0);
}