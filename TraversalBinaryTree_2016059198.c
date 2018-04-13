#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node * Left;
	struct Node * Right;
}Node;

void intsertTree(Node ** BST, int value);
void printPreorder(Node *BST);
void printInorder(Node *BST);
void printPostorder(Node *BST);

int main() {
	Node *pParentNode = NULL;

	intsertTree(&pParentNode, 4);
	intsertTree(&pParentNode, 2);
	intsertTree(&pParentNode, 6);
	intsertTree(&pParentNode, 1);
	intsertTree(&pParentNode, 3);
	intsertTree(&pParentNode, 5);
	intsertTree(&pParentNode, 7);

	printf("Preorder : \n");
	printPreorder(pParentNode);
	printf("\nInorder : \n");
	printInorder(pParentNode);
	printf("\nPostorder : \n");
	printPostorder(pParentNode);
	return 0;
}

void intsertTree(Node ** BST, int value) {
	if ((*BST) == NULL) { //비어있을 때
		(*BST) = (Node *)malloc(sizeof(Node));
		(*BST)->data = value;
		(*BST)->Left = NULL;
		(*BST)->Right = NULL;
	}
	else if ((*BST)->data < value) // 입력값이 더 크면
		intsertTree(&(*BST)->Right, value);
	
	else
		intsertTree(&(*BST)->Left, value);
}

void printPreorder(Node *BST) {
	if (BST == NULL)
		return;
	else {
		printf("[%d] ", BST->data);
		if ((BST->Left) != NULL)
			printPreorder(BST->Left);
		if ((BST->Right) != NULL)
			printPreorder(BST->Right);
	}
}

void printInorder(Node *BST) {
	if (!BST)
		return;
	else {
		if ((BST->Left) != NULL)
			printInorder(BST->Left);
		printf("[%d] ", BST->data);
		if ((BST->Right) != NULL)
			printInorder(BST->Right);
	}
}

void printPostorder(Node *BST) {
	if (!BST)
		return;
	else {
		if ((BST->Left) != NULL)
			printPostorder(BST->Left);
		if ((BST->Right) != NULL)
			printPostorder(BST->Right);
		printf("[%d] ", BST->data);
	}
}
