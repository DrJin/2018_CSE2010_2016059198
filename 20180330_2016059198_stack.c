#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct StackNode {
	int data;
	struct StackNode* next;
}cQueue;

void pushLinkedStack(StackNode** top, int data);
StackNode* popLinkedStack(StackNode** top);
void showLinkedStack(StackNode* top);
int isEmpty(StackNode* top);
StackNode* topLinkedStack(StackNode* top);
void deleteLinkedStack(StackNode** top);

int main() {
	StackNode *top = NULL;
	StackNode *pNode;
	printf("Push(10,20,30) called\n");
	pushLinkedStack(&top, 10);
	pushLinkedStack(&top, 20);
	pushLinkedStack(&top, 30);
	showLinkedStack(top);

	printf("Pop() called\n");
	pNode = popLinkedStack(&top);
	if (pNode) {
		free(pNode);
		showLinkedStack(top);
	}
	printf("Top() called\n");
	pNode = topLinkedStack(top);
	if (pNode) {
		printf("the top is %d\n", pNode->data);
	}
	else
		printf("it's empty\n");
	showLinkedStack(top);

	deleteLinkedStack(&top);
	return 0;
}
void pushLinkedStack(StackNode** top, int data) {
	StackNode *pNode = NULL;
	pNode = (StackNode *)malloc(sizeof(StackNode));
	pNode->data = data;
	pNode->next = NULL;

	if (isEmpty(*top)) 
		*top = pNode;	
	
	else{
		pNode->next = *top;
		*top = pNode;
	}
}
StackNode* popLinkedStack(StackNode** top) {
	StackNode *pNode = NULL;
	if (isEmpty(*top)) {
		printf("it's empty!!\n");
		return NULL;
	}
	
	pNode = *top;
	*top = pNode->next;
	return pNode;
	
}
void showLinkedStack(StackNode *top) {
	StackNode *pNode = NULL;
	int i;
	if (isEmpty(top)) {
		printf("it's empty!!\n");
		return;
	}
	i = 0;
	pNode = top;
	printf("==============start==============\n");
	while (pNode != NULL) {
		printf("(%d) : %d\n", i++, pNode->data);
		pNode = pNode->next;
	}
	printf("=================================\n");
	
}
int isEmpty(StackNode* top) {
	if (top == NULL)
		return TRUE;
	else
		return FALSE;

}

StackNode* topLinkedStack(StackNode* top) {
	StackNode *pNode = NULL;
	if(!isEmpty(top))
		pNode = top;
	return pNode;
}
void deleteLinkedStack(StackNode** top) {
	StackNode *pNode = NULL;
	StackNode *pDelNode = NULL;
	pNode = *top;
	while (pNode != NULL) {
		pDelNode = pNode;
		pNode = pNode->next;
		free(pDelNode);
	}
}