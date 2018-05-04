#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 50
typedef struct Heap {
	int nodes[MAX_NODES];
	int lastIndex;
}Heap;

void initHeap(Heap* h);
void insertData(Heap* h, int data);
void printHeap(Heap h);
void deleteData(Heap* h);

int main() {
	Heap h;
	initHeap(&h);
	
	insertData(&h, 1);
	insertData(&h, 3);
	insertData(&h, 8);
	insertData(&h, 13);
	insertData(&h, 4);
	insertData(&h, 10);
	insertData(&h, 6);

	printHeap(h);

	deleteData(&h);
	printHeap(h);

	deleteData(&h);
	printHeap(h);

	return 0;
}

void initHeap(Heap* h) {
	int i;
	for (i = 0; i < MAX_NODES; i++)
		h->nodes[i] = 0;
	h->lastIndex = 0;
}
void insertData(Heap* h, int data) {
	int index;
	if (h->lastIndex == MAX_NODES - 1) { //full 검사
		printf("Heap is FULL!!!\n");
		return;
	}

	index = ++h->lastIndex;
	h->nodes[index] = data; //끝에 데이터 추가

	while (index != 1 && h->nodes[index / 2] < h->nodes[index]) {
			 h->nodes[0] = h->nodes[index];
			h->nodes[index] = h->nodes[index / 2];
			h->nodes[index / 2] = h->nodes[0]; 
			//h->nodes[index/2] = h->nodes[index];
		index /= 2;
	}
	//h->nodes[index] = data;

}
void printHeap(Heap h) {
	int i, count, NLindex;//newLineIndex
	count = 1;
	NLindex = 0;
	for (i = 1; i <= h.lastIndex; i++) {
		printf("%d\t", h.nodes[i]);
		if (pow(2, NLindex) == count) {
			printf("\n");
			NLindex++;
			count = 0;
		}
		count++;
	}
	printf("\n\n");
}
void deleteData(Heap* h) {
	int temp, pIndex, cIndex;
	if(h->lastIndex == 0){
		printf("Heap is EMPTY!!!\n");
		return;
	}

	if (h->lastIndex == 1) {
		h->nodes[h->lastIndex] = 0;
		h->lastIndex = 0;
		return;
	}
	//마지막 노드 꺼내기
	temp = h->nodes[h->lastIndex];
	h->nodes[h->lastIndex] = 0;
	h->lastIndex--;


	pIndex = 1;
	cIndex = 2;

	while (cIndex <= h->lastIndex) {
		if (h->nodes[cIndex] < h->nodes[cIndex + 1])
			cIndex++;

		if (temp > h->nodes[cIndex]) // 부모노드가 더 크면
			break;

		h->nodes[pIndex] = h->nodes[cIndex];
		pIndex = cIndex;
		cIndex *= 2; //2자리 밑으로
	}
	h->nodes[pIndex] = temp;
}