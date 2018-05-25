#include <stdio.h>
#include <stdlib.h>

#define M_WAY 3

typedef struct BTNode {
	int n;
	int isLeaf; //leaf?
	int isRoot; //root?
	int keys[M_WAY];//key 값

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
	
	printf("넣을 데이터 개수 : ");
	scanf_s("%d", &n);
	for (i = 0; i < n; i++) {
		printf("데이터를 입력하세요 : ");
		scanf_s("%d", &t);
		root = BTInsert(root, t);
	}
	printf("트리 출력. \n");
	InorderTraversal(root);
	

	return 0;
}

BTNode* initBTNode() {
	int i;
	BTNode* newBTNode;
	newBTNode = (BTNode*)malloc(sizeof(BTNode));
	newBTNode->n = 0;
	newBTNode->isLeaf = 1; //초기 노드는 leaf노드
	newBTNode->isRoot = 0;

	for (i = 0; i < M_WAY + 1; i++)
		newBTNode->childs[i] = NULL;

	return newBTNode;
}

BTNode* BTInsert(BTNode* root, int key) {
	int i, pos, mid;
	BTNode* split;

	//leaf노드일 때
	if (root->isLeaf) {
		//넣어줄 위치 탐색
		for (pos = 0; pos < root->n; pos++) {
			if (root->keys[pos] > key)
				break;
		}
		for (i = root->n; i > pos; i--)  //key를 뒤로 밀어줌
			root->keys[i] = root->keys[i-1];
		root->keys[pos] = key;
		root->n++;
		if (root->n == M_WAY && root->isRoot)
			return splitChild(root);
		return root;
	}
	else { //root노드 일 때
		for (pos = 0; pos < root->n; pos++)
			if (root->keys[pos] > key)
				break;
		root->childs[pos] = BTInsert(root->childs[pos], key); //자식 노드로 들어가 탐색

		if ((root->childs[pos])->n == M_WAY) {
			split = splitChild(root->childs[pos]);
			for (i = root->n; i > pos; i--) {
				root->keys[i] = root->keys[i - 1];//key와
				root->childs[i + 1] = root->childs[i];//child를 같이 밀어줌(1 차이)
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
	newParent->isLeaf = 0; //초기 노드가 아니므로 not leaf
	if (root->isRoot) //root가 root라면 newParent도 root
		newParent->isRoot = 1;
	root->isRoot = 0;

	newSibling = initBTNode();
	newSibling->isLeaf = root->isLeaf;

	//r의 중간지점을 정하고 오른쪽 key값을 newSibling으로
	mid = (M_WAY - 1) / 2;
	for (i = mid + 1; i < M_WAY; i++) {
		newSibling->childs[i - (mid + 1)] = root->childs[i];
		newSibling->keys[i - (mid+1)] = root->keys[i];
		newSibling->n++;

		root->childs[i] = NULL;
		root->keys[i] = 0;
		root->n--;
	}
	//child node pointer는 key보다 1크므로 한번더
	newSibling->childs[i - (mid + 1)] = root->childs[i];
	root->childs[i] = NULL;

	//r 중간의 key를 newParent로
	newParent->keys[0] = root->keys[mid];
	newParent->n++;
	root->keys[mid] = 0;
	root->n--;

	//newParent 노드의 child로 r, newSibling 연결
	newParent->childs[0] = root;
	newParent->childs[1] = newSibling;
	return newParent;
}

void InorderTraversal(BTNode* r) {
	int i;
	printf("\n");
	for (i = 0; i < r->n; i++) {
		//leaf 노드가 아니라면 밑으로 탐색
		if (!(r->isLeaf)) {
			InorderTraversal(r->childs[i]);
			printf("    ");
		}
		//데이터 출력
		printf("%d", r->keys[i]);
	}
	//key 값보다 child노드가 많으므로 한번더
	if (!(r->isLeaf))
		InorderTraversal(r->childs[i]);
	printf("\n");
}