#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct Node{
	int data;
	struct Node * Left;
	struct Node * Right;
}Node;

void intsertTree(Node ** BST, int value);
void printPreorder(Node *BST);
void printInorder(Node *BST);
void printPostorder(Node *BST);

Node* searchTree(Node * BST, int value);
Node* searchParent(Node * BST, int value);
void deleteTree(Node ** BST, int value);
void copyTree(Node*src, Node**dst);
int compareTree(Node* t1, Node* t2);

int main() {
	Node *pParentNode = NULL;
	Node *cParentNode = NULL;

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

	printf("\nSearch Data 3:\n");
	if (searchTree(pParentNode, 3) != NULL)
		printf("3 is exsisted\n");
	else
		printf("3 is not exsisted\n");
	/*
	printf("Delete data 3\n");
	deleteTree(&pParentNode, 3);
	printf("Delete data 2\n");
	deleteTree(&pParentNode, 2);
	*/
	printf("Delete data 4\n");
	printf("\nSearch Data 4:\n");
	deleteTree(&pParentNode, 4);
	if (searchTree(pParentNode, 4) != NULL)
		printf("3 is exsisted\n");
	else
		printf("4 is not exsisted\n");


	printf("Preorder : \n");
	printPreorder(pParentNode);
	printf("\nInorder : \n");
	printInorder(pParentNode);
	printf("\nPostorder : \n");
	printPostorder(pParentNode);

	printf("\n\n");

	copyTree(pParentNode, &cParentNode); //copy

	//copied print
	printf("Preorder : \n");
	printPreorder(cParentNode);
	printf("\nInorder : \n");
	printInorder(cParentNode);
	printf("\nPostorder : \n");
	printPostorder(cParentNode);

	printf("\n\n");

	if (compareTree(pParentNode, cParentNode)) //compare
		printf("Two trees are equal\n");
	else
		printf("Two trees are not equal\n");

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


Node* searchTree(Node * BST, int value) {
	while (BST != NULL && BST->data != value) {
		if (BST->data < value)
			BST = BST->Right;
		else
			BST = BST->Left;
	}
	return BST;
}


Node* searchParent(Node * BST, int value) {
	Node* pNode = NULL;
	while (BST != NULL && BST->data != value) {
		pNode = BST;
		if (BST->data < value)
			BST = BST->Right;
		else
			BST = BST->Left;
	}
	return pNode;
}
void deleteTree(Node ** BST, int value) {
	Node* pNode; //parentNode
	Node* delNode; //deleteNode
	Node* cNode; //childNode
	Node* succNode; //succesorNode

	pNode = searchParent(*BST, value);
	delNode = searchTree(*BST, value);
	if (delNode == NULL) {
		printf("no %d", value);
		return;
	}
	
	if (delNode->Left == NULL && delNode->Right == NULL) {//case 1 : no child
		if (pNode == NULL)//parentNode = NULL -> parentNode = rootNode
			*BST = NULL;
		else {
			if (pNode->Left == delNode)
				pNode->Left = NULL;
			else
				pNode->Right = NULL;
		}
		free(delNode);
	}
	else if (delNode->Left == NULL || delNode->Right == NULL) {//case 2 : one child
		cNode = delNode->Left == NULL ? delNode->Right : delNode->Left;//childNode
		if (pNode == NULL)
			*BST = cNode;
		else {
			if (pNode->Left == delNode)
				pNode->Left = cNode;
			else
				pNode->Right = cNode;
		}
		free(delNode);
	}





	/* 여기부터 과제!!!!!!!!!*/





	else { //case 3 : two child
		succNode = delNode->Right;
		while (succNode->Left != NULL)
			succNode = succNode->Left;
		//succNode = right의 가장 left node
		searchParent(*BST, succNode->data)->Left=NULL;//succNode 위치 삭제
		delNode->data = succNode->data; // data 갱신
		
		free(succNode);//succNode 할당 해제

		//while(cNode->
	}
}

void copyTree(Node*src, Node**dst) { //Preorder 사용
	if (!src)
		return;
	else {
		intsertTree(dst, src->data);
		if ((src->Left) != NULL) {
			copyTree(src->Left, dst);
		}		
		if ((src->Right) != NULL) {
			copyTree(src->Right, dst);
		}
	}

}
int compareTree(Node* t1, Node* t2) { //Preorder 사용
	if (t1 == NULL || t2 == NULL)
		return;
	return (t1->data == t2->data) && compareTree(t1->Left,t2->Left) && compareTree(t1->Right,t2->Right) ? TRUE : FALSE;
}