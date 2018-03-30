#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5
#define TRUE 1
#define FALSE 0

typedef struct circularQueue {
	int data[CAPACITY];
	int front;
	int rear;
}cQueue;

cQueue* createCircularQueue();
void enqueue(cQueue* cq, int data);
int isFull(cQueue* cq);
void showQueue(cQueue* cq);
int isEmpty(cQueue* cq);
void dequeue(cQueue* cq);

int main() {
	cQueue* cq;
	cq = createCircularQueue();
	printf("front : %d , rear : %d\n",cq->front, cq->rear);

	printf("enqueue 10 and 20 and 30\n");
	enqueue(cq, 10);
	enqueue(cq, 20);
	enqueue(cq, 30);
	showQueue(cq);
	printf("front : %d , rear : %d\n",cq->front, cq->rear);

	printf("dequeue 2\n");
	dequeue(cq);
	dequeue(cq);
	printf("front : %d , rear : %d\n",cq->front, cq->rear);

	printf("enqueue 40\n");
	enqueue(cq, 40);
	printf("front : %d , rear : %d\n",cq->front, cq->rear);
	printf("enqueue 50\n");
	enqueue(cq, 50);
	printf("front : %d , rear : %d\n",cq->front, cq->rear);
	printf("enqueue 60\n");
	enqueue(cq, 60);
	showQueue(cq);
	printf("front : %d , rear : %d\n",cq->front, cq->rear);
	printf("enqueue 70\n");
	enqueue(cq, 70);
	printf("front : %d , rear : %d\n",cq->front, cq->rear);
	showQueue(cq);
		return 0;
}

cQueue* createCircularQueue() {
	cQueue* pcq = NULL;
	int i;
	pcq = (cQueue *)malloc(sizeof(cQueue));
	pcq->front = 0;
	pcq->rear = 0;
	return pcq;

}
void enqueue(cQueue* cq, int data) {
	if(isFull(cq))
	{
		printf("Circular Queue is Full!!!\n");
		return;
	}
	cq->rear = (cq->rear + 1) % CAPACITY;
	cq->data[cq->rear] = data;

}
int isFull(cQueue* cq) {
	if ((cq->rear + 1) % CAPACITY == cq->front)
		return TRUE;
	else 
		return FALSE;
}
void showQueue(cQueue* cq) {
	int i;
	if (isEmpty(cq)) {
		printf("Circular Queue is Empty!!!\n");
		return NULL;
	}
	printf("============show==========\n");
	for (i = cq->front + 1; i != cq->rear; i = (i + 1) % CAPACITY)
		printf("[%d]\n", cq->data[i]);
	printf("[%d]\n", cq->data[i]);
	printf("==========================\n");
}
int isEmpty(cQueue* cq) {
	if (cq->front == cq->rear)
		return TRUE;
	else
		return FALSE;
}
void dequeue(cQueue* cq) {

	if (isEmpty(cq)) {
		printf("Circular Queue is Empty!!!\n");
		return NULL;
	}
	cq->front = (cq->front + 1) % CAPACITY;
}