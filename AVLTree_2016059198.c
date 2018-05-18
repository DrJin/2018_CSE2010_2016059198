#include <stdio.h>
#include <stdlib.h>
#define Max(x,y) ((x)>(y))?(x):(y)

typedef struct AvlNode {
	int data;
	struct AvlNode *left, *right;
	int Height;
}AvlNode;

int height(AvlNode *n) {
	if (n == NULL)
		return -1;
	else
		return n->Height;
}

AvlNode* avlAdd(AvlNode* r, int data);
AvlNode* rotateLL(AvlNode* p);
AvlNode* rotateLR(AvlNode* p);
AvlNode* rotateRR(AvlNode* p);
AvlNode* rotateRL(AvlNode* p);
AvlNode* avlSearch(AvlNode* n, int key);
void InorderTraveling(AvlNode* r);


int main() {
	AvlNode *root = NULL;

	root = avlAdd(root, 7);
	root = avlAdd(root, 8);
	root = avlAdd(root, 9);
	root = avlAdd(root, 2);
	root = avlAdd(root, 1);
	root = avlAdd(root, 5);
	root = avlAdd(root, 3);
	root = avlAdd(root, 6);
	root = avlAdd(root, 4);

	printf("\n검색 : %d\n", avlSearch(root, 4)->data);
	printf("\n");
	InorderTraveling(root);
	return 0;
}

AvlNode* rotateLL(AvlNode* p) {
	AvlNode* c = p->left;
	p->left = c->right; //원래의 parent의 left에 원래 child의 right sub tree를 넣는다
	c->right = p; //child의 right에 p를 넣는다.
	p->Height = Max(height(p->left), height(p->right)) + 1; //바뀐 child의 높이를 비교 수정
	c->Height = Max(height(c->left), height(c->right))+1; 
	return c;
}

AvlNode* rotateRR(AvlNode* p) {
	AvlNode* c = p->right;
	p->right = c->left; //원래의 parent의 right에 원래 child의 left sub tree를 넣는다
	c->left = p; //child의 left에 p를 넣는다.
	p->Height = Max(height(p->left), height(p->right)) + 1;  
	c->Height = Max(height(c->left), height(c->right)) + 1;
	return c;
}

AvlNode* rotateLR(AvlNode* p) {
	AvlNode* c = p->left;
	p->left = rotateRR(c);
	p = rotateLL(p);
	return p;
}

AvlNode* rotateRL(AvlNode* p) {
	AvlNode* c = p->right;
	p->right = rotateLL(c);
	p = rotateRR(p);
	return p;
}

AvlNode* avlAdd(AvlNode* r, int data) {
	if (r == NULL) { //비어있을 때
		r = (AvlNode *)malloc(sizeof(AvlNode));
		r->data = data;
		r->left = NULL;
		r->right = NULL;
		r->Height = 0;
	}
	else if (r->data < data) { // 입력값이 더 크면
		r->right = avlAdd(r->right, data); //오른쪽에 추가
		if (height(r->right) - height(r->left) == 2) { //RR RL
			if (r->right->data < data) //오른쪽의 오른쪽으로 들어갔으니 RR
				r = rotateRR(r);
			else //오른쪽의 왼쪽에 들어갔으니 RL
				r = rotateRL(r);
		}
	}

	else if (r->data > data) { // 입력값이 작으면
		r->left = avlAdd(r->left, data); //왼쪽에 추가
		if (height(r->right) - height(r->left) == -2) { //LL, LR
			if (r->left->data < data) //왼쪽의 오른쪽으로 들어갔으니 LR
				r = rotateLR(r);
			else //왼쪽의 왼쪽에 들어갔으니 :L
				r = rotateLL(r);
		}
	}
	else {
		printf("\n중복 입력값 \n");
		return;
	}
	if (height(r->right) > height(r->left))
		r->Height = height(r->right) + 1;
	else
		r->Height = height(r->left) + 1;
	return r;
}


AvlNode* avlSearch(AvlNode* n, int key) {
	while (n != NULL && n->data != key) {
		if (n->data < key)
			n = n->right;
		else
			n = n->left;
	}
	return n;
}

void InorderTraveling(AvlNode* r) {
	if (!r)
		return;
	else {
		InorderTraveling(r->left);
		printf("[%d] ", r->data);
		InorderTraveling(r->right);
	}
}