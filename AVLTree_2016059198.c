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

	printf("\n�˻� : %d\n", avlSearch(root, 4)->data);
	printf("\n");
	InorderTraveling(root);
	return 0;
}

AvlNode* rotateLL(AvlNode* p) {
	AvlNode* c = p->left;
	p->left = c->right; //������ parent�� left�� ���� child�� right sub tree�� �ִ´�
	c->right = p; //child�� right�� p�� �ִ´�.
	p->Height = Max(height(p->left), height(p->right)) + 1; //�ٲ� child�� ���̸� �� ����
	c->Height = Max(height(c->left), height(c->right))+1; 
	return c;
}

AvlNode* rotateRR(AvlNode* p) {
	AvlNode* c = p->right;
	p->right = c->left; //������ parent�� right�� ���� child�� left sub tree�� �ִ´�
	c->left = p; //child�� left�� p�� �ִ´�.
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
	if (r == NULL) { //������� ��
		r = (AvlNode *)malloc(sizeof(AvlNode));
		r->data = data;
		r->left = NULL;
		r->right = NULL;
		r->Height = 0;
	}
	else if (r->data < data) { // �Է°��� �� ũ��
		r->right = avlAdd(r->right, data); //�����ʿ� �߰�
		if (height(r->right) - height(r->left) == 2) { //RR RL
			if (r->right->data < data) //�������� ���������� ������ RR
				r = rotateRR(r);
			else //�������� ���ʿ� ������ RL
				r = rotateRL(r);
		}
	}

	else if (r->data > data) { // �Է°��� ������
		r->left = avlAdd(r->left, data); //���ʿ� �߰�
		if (height(r->right) - height(r->left) == -2) { //LL, LR
			if (r->left->data < data) //������ ���������� ������ LR
				r = rotateLR(r);
			else //������ ���ʿ� ������ :L
				r = rotateLL(r);
		}
	}
	else {
		printf("\n�ߺ� �Է°� \n");
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