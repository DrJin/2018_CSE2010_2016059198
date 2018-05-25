#include <stdio.h>
#include <stdlib.h>

#define M_WAY 3

typedef struct BTNode {
	int n;
	int isLeaf; //leaf?
	int isRoot; //root?
	int keys[M_WAY];//key ��

	struct BTNode* childs[M_WAY + 1];
}BTNode;


BTNode* initBTNode();
BTNode* BTInsert(BTNode* r, int key);
BTNode* splitChild(BTNode* r);
void InorderTraversal(BTNode* r);


int main() {
	BTNode *root = initBTNode();
	int i, n, t;

	root->isRoot = 1;
	
	printf("���� ������ ���� : ");
	scanf_s("%d", &n);
	for (i = 0; i < n; i++) {
		printf("�����͸� �Է��ϼ��� : ");
		scanf_s("%d", &t);
		root = BTInsert(root, t);
	}
	printf("Ʈ�� ���. \n");
	InorderTraversal(root);
	

	return 0;
}

BTNode* initBTNode() {
	int i;
	BTNode* newBTNode;
	newBTNode = (BTNode*)malloc(sizeof(BTNode));
	newBTNode->n = 0;
	newBTNode->isLeaf = 1; //�ʱ� ���� leaf���
	newBTNode->isRoot = 0;

	for (i = 0; i < M_WAY + 1; i++)
		newBTNode->childs[i] = NULL;

	return newBTNode;
}

BTNode* BTInsert(BTNode* root, int key) {
	int i, pos, mid;
	BTNode* split;

	//leaf����� ��
	if (root->isLeaf) {
		//�־��� ��ġ Ž��
		for (pos = 0; pos < root->n; pos++) {
			if (root->keys[pos] > key)
				break;
		}
		for (i = root->n; i > pos; i--)  //key�� �ڷ� �о���
			root->keys[i] = root->keys[i-1];
		root->keys[pos] = key;
		root->n++;
		if (root->n == M_WAY && root->isRoot)
			return splitChild(root);
		return root;
	}
	else { //root��� �� ��
		for (pos = 0; pos < root->n; pos++)
			if (root->keys[pos] > key)
				break;
		root->childs[pos] = BTInsert(root->childs[pos], key); //�ڽ� ���� �� Ž��

		if ((root->childs[pos])->n == M_WAY) {
			split = splitChild(root->childs[pos]);
			for (i = root->n; i > pos; i--) {
				root->keys[i] = root->keys[i - 1];//key��
				root->childs[i + 1] = root->childs[i];//child�� ���� �о���(1 ����)
			}
			root->keys[pos] = split->keys[0];
			root->n++;
			root->childs[pos] = split->childs[0];
			root->childs[pos + 1] = split->childs[1];
		}
	}
	if(root->isRoot && root->n == M_WAY)
		return splitChild(root);
	return root;

}
BTNode* splitChild(BTNode* root) {
	int i, mid;
	//   newParent
	//root  newSibling
	BTNode* newParent;
	BTNode* newSibling;

	newParent = initBTNode();
	newParent->isLeaf = 0; //�ʱ� ��尡 �ƴϹǷ� not leaf
	if (root->isRoot) //root�� root��� newParent�� root
		newParent->isRoot = 1;
	root->isRoot = 0;

	newSibling = initBTNode();
	newSibling->isLeaf = root->isLeaf;

	//r�� �߰������� ���ϰ� ������ key���� newSibling����
	mid = (M_WAY - 1) / 2;
	for (i = mid + 1; i < M_WAY; i++) {
		newSibling->childs[i - (mid + 1)] = root->childs[i];
		newSibling->keys[i - (mid+1)] = root->keys[i];
		newSibling->n++;

		root->childs[i] = NULL;
		root->keys[i] = 0;
		root->n--;
	}
	//child node pointer�� key���� 1ũ�Ƿ� �ѹ���
	newSibling->childs[i - (mid + 1)] = root->childs[i];
	root->childs[i] = NULL;

	//r �߰��� key�� newParent��
	newParent->keys[0] = root->keys[mid];
	newParent->n++;
	root->keys[mid] = 0;
	root->n--;

	//newParent ����� child�� r, newSibling ����
	newParent->childs[0] = root;
	newParent->childs[1] = newSibling;
	return newParent;
}

void InorderTraversal(BTNode* r) {
	int i;
	printf("\n");
	for (i = 0; i < r->n; i++) {
		//leaf ��尡 �ƴ϶�� ������ Ž��
		if (!(r->isLeaf)) {
			InorderTraversal(r->childs[i]);
			printf("    ");
		}
		//������ ���
		printf("%d", r->keys[i]);
	}
	//key ������ child��尡 �����Ƿ� �ѹ���
	if (!(r->isLeaf))
		InorderTraversal(r->childs[i]);
	printf("\n");
}