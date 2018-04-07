#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct Node {
	int data;
	struct Node *nextN;
}Node;

typedef struct LinkedList {
	int current;
	Node HeadNode;
}LinkedList;

typedef struct StackNode {
	int data;
	struct StackNode* next;
}StackNode;

void pushLinkedStack(StackNode** top, int data);
StackNode* popLinkedStack(StackNode** top);


int addNode(LinkedList* ll, int pos, int data);
int removeNode(LinkedList* ll, int pos);
void showList(LinkedList* ll);
int FindNode(LinkedList * ll, int data);

void reverseList(LinkedList *ll);


int main() {
	LinkedList* linkedlist = (LinkedList *)malloc(sizeof(LinkedList));
	linkedlist->current = 0;
	linkedlist->HeadNode.nextN = NULL;
	addNode(linkedlist, 0, 1);
	addNode(linkedlist, 1, 2);
	addNode(linkedlist, 2, 9);
	addNode(linkedlist, 3, 7);
	addNode(linkedlist, 4, 3);
	showList(linkedlist);
	reverseList(linkedlist);
	showList(linkedlist);
	return 0;
}



void pushLinkedStack(StackNode** top, int data) {
	StackNode *pNode = NULL;
	pNode = (StackNode *)malloc(sizeof(StackNode));
	pNode->data = data;
	pNode->next = NULL;

	if ((*top) == NULL)
		*top = pNode;

	else {
		pNode->next = *top;
		*top = pNode;
	}
}
StackNode* popLinkedStack(StackNode** top) {
	StackNode *pNode = NULL;
	if ((*top) == NULL) {
		printf("it's empty!!\n");
		return NULL;
	}

	pNode = *top;
	*top = pNode->next;
	return pNode;

}

int addNode(LinkedList* ll, int pos, int data) {
	//while(ll->HeadNode.
	int i;
	Node* newNode = NULL;
	Node* prevNode = NULL;
	newNode = (Node*)malloc(sizeof(Node));

	if (ll == NULL || pos < 0 || pos > ll->current || !newNode) {
		printf("Error!!!\n");
		free(newNode);
		return FALSE; //error
	}
	newNode->data = data;
	newNode->nextN = NULL;
	prevNode = &(ll->HeadNode);
	for (i = 0; i < pos; i++) {
		prevNode = prevNode->nextN;
	}
	newNode->nextN = prevNode->nextN;
	prevNode->nextN = newNode;
	ll->current++;
	return TRUE;
}
int removeNode(LinkedList* ll, int pos) {
	int i;
	Node* prevNode = NULL;
	Node* tmpNode = NULL;
	if (ll == NULL || pos < 0 || pos > ll->current) {
		printf("Error!!!\n");
		return FALSE; //error
	}
	prevNode = &(ll->HeadNode);
	for (i = 0; i < pos - 1; i++) {
		prevNode = prevNode->nextN;
	}
	//printf("%d번째 데이터 %d를 제거합니다.\n", pos, prevNode->nextN->data);
	tmpNode = prevNode->nextN->nextN;
	free(prevNode->nextN);
	prevNode->nextN = tmpNode;
	ll->current--;
	return TRUE;
}
void showList(LinkedList *ll) {
	int i = 1;
	Node *tmp = ll->HeadNode.nextN;
	if (ll == NULL)
		return;
	if (ll->current == 0) {
		printf("비어있습니다.");
		return;
	}
	while (tmp != NULL) {
		printf("%d 번쨰 데이터 : %d\n", i++, tmp->data);
		tmp = tmp->nextN;
	}
}

int FindNode(LinkedList * ll, int data) {
	int i = 1;
	Node *tmp = ll->HeadNode.nextN;
	if (ll == NULL) {
		printf("Error!!!\n");
		return FALSE; //error
	}
	if (ll->current == 0) {
		printf("비어있습니다.");
		return;
	}
	while (tmp != NULL) {
		tmp = tmp->nextN;
		if (tmp->data == data) {
			return i;
		}
		i++;
	}
	return FALSE;
}



void reverseList(LinkedList *ll) {
	//Node *pNode = NULL;
	StackNode *sNode = NULL;
	int i;
	int count = ll->current;
	printf("Reverse Linked List \n");

	for (i = 0; i < count; i++) {
		pushLinkedStack(&sNode, ll->HeadNode.nextN->data); //헤드 노드 다음 노드의 데이터 저장
		removeNode(ll, 0);//첫번째 노드 제거
	}
	for (i = 0; i < count; i++) {
		addNode(ll, ll->current, popLinkedStack(&sNode)->data); //끝 자리에 다시 저장
	}

}