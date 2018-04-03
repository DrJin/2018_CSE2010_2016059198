#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE -1

typedef struct polyNode {
	int coef;
	int expon;
	struct polyNode* next;
}polyNode;

void addPolynomial(polyNode** pHeadNode, int coef, int expon); // �� �߰�
void removePolynomial(polyNode** pHeadNode, int expon); // �� ����
polyNode* multiplication(polyNode* A, polyNode* B); // ���׽� ���ϱ�
void showPolynomial(polyNode* pHeadNode); //���׽� ���
void clearPolynomial(polyNode** pHeadNode); // ���׽� ��ü ����
int findPolynomial(polyNode* pHeadNode, int expon); // �� ã��

int main()
{
	int mode, coef, expon;
	char poly;

	polyNode *A, *B, *C;
	A = B = C = NULL;

	do
	{
		printf("\nSelect the mode\n");
		printf("=================\n");
		printf("1: add polynomial\n");
		printf("2: remove polynomial\n");
		printf("3: Multiplication\n");
		printf("4: show polynomial\n");
		printf("5: clear polynomial\n");
		printf("-1: exit the program\n");
		printf("==================\n");
		printf("mode: ");
			scanf_s("%d", &mode);

		switch (mode)
		{
		case 1:
			printf("\nChoose the polynomial to add ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf_s(" %c", &poly);
			if (poly != 'A' && poly != 'B')
				printf("Please choose right polynomial (A or B)\n");
			else
			{
				//����� ������ �Է� �޾Ƽ� polynomial�� �߰��ϴ� �Լ� ����
				//�̹� �����ϴ� ������ �Է� ���� ��� �߰��� �� ����
				printf("input the coef: ");
				scanf_s("%d", &coef);
				printf("input the expon: ");
				scanf_s("%d", &expon);

				if (poly == 'A')
					addPolynomial(&A, coef, expon);
				else
					addPolynomial(&B, coef, expon);
			}
			break;
		case 2:
			printf("\nChoose the polynomial to remove ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf_s(" %c", &poly);
			if (poly != 'A' && poly != 'B')
				printf("Please choose right polynomial (A or B)\n");
			else
			{
				printf("input the expon: ");
				scanf_s("%d", &expon);
				//������ �Է� �޾Ƽ� polynomial���� �����ϴ� �Լ� ����
				if (poly == 'A')
					removePolynomial(&A, expon);
				else
					removePolynomial(&B, expon);
			}
			break;
		case 3:
			printf("\nMultiplication with A and B\n");
			//C = A * B ������ ����
			C = multiplication(A, B);
			printf("C: ");
			//C�� ����� ���
			showPolynomial(C);
			break;
		case 4:
			//A,B polynomial ���� ���
			printf("A: ");
			showPolynomial(A);
			printf("B: ");
			showPolynomial(B);
			break;
		case 5:
			printf("\nChoose the polynomial to clear ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf_s(" %c", &poly);
			if (poly != 'A' && poly != 'B')
				printf("Please choose right polynomial (A or B)\n");
			else
				//�ش� polynomial�� �ʱ�ȭ ��Ű�� �Լ� ����
			{
				if (poly == 'A')
					clearPolynomial(&A);
				else
					clearPolynomial(&B);
			}
			break;
		default:
			mode = -1;
			break;
		}
	} while (mode != -1);
	return 0;
}


void addPolynomial(polyNode** pHeadNode, int coef, int expon) {
	int i, count = 0;
	polyNode *tmp = *pHeadNode;
	count = findPolynomial(*pHeadNode, expon);
	if ( count != FALSE) { // �̹� ���� ���
		printf("ss");
		for (i = 0; i < count; i++) 
			tmp = tmp->next; // �ش� ���������̵�
		tmp->coef += coef; // ��� �հ�
	}
	else { // ���� ���
		polyNode *newNode; // ���� ����
		newNode = (polyNode *)malloc(sizeof(polyNode));
		newNode->expon = expon;
		newNode->coef = coef; 
		newNode->next = NULL; // �ʱ�ȭ
		if (tmp == NULL) { // ó�� ������ ��
			*pHeadNode = newNode;
			return;
		}
		int num = 0;
		while (tmp != NULL) { // �󸶳� �ָ� �������ִ��� ã��
			if (tmp->expon < expon)
				num++;
			tmp = tmp->next;
		}
		tmp = *pHeadNode;
		if (num == 0) { // ���� ���� �� ���ʿ� �߰�

			newNode->next = tmp;
			*pHeadNode = newNode;
		}
		else { //Ŭ �� ���ʿ� �߰�
			for (i = 0; i < num-1; i++) {
				tmp = tmp->next;
			}
			newNode->next = tmp->next; // �� ���� ���� ����� ���� ��带 ����Ŵ
			tmp->next = newNode; //���� ���� �� ��带 ����Ŵ
		}
	}
	
}
void removePolynomial(polyNode** pHeadNode, int expon) {
	int i, count = 0;
	polyNode* prevNode = *pHeadNode;
	polyNode* tmp = NULL;
	count = findPolynomial(*pHeadNode, expon);
	if (count == -1 || prevNode == NULL) {//������ ���� ���ų� ������� ���
		printf("Remove Error!!!\n");
		return;
	}

	for (i = 0; i < count-1; i++) {
		prevNode = prevNode->next;
	}
	if ((*pHeadNode)->next != NULL) {
		tmp = prevNode->next->next;
		free(prevNode->next);
		prevNode->next = tmp;
	}
	else { // ���� �ϳ��� ������ ���
		free((*pHeadNode));
		(*pHeadNode) = NULL;
	}
}
polyNode* multiplication(polyNode* A, polyNode* B) {
	polyNode *newPoly = NULL;
	polyNode *tmp1 = A;
	polyNode *tmp2 = B;
	if (A == NULL || B == NULL) {
		printf("A or B is empty!!\n");
		return NULL;
	}
	
	while (tmp1 != NULL) { // A�� �÷����鼭
		while (tmp2 != NULL) { //B�� �÷����鼭
			addPolynomial(&newPoly, tmp1->coef*tmp2->coef , tmp1->expon+tmp2->expon); // coef�� ����, expon�� ����
			tmp2 = tmp2->next;
		}
		tmp2 = B; //ó������
		tmp1 = tmp1->next;
	}
	return newPoly;
}
void showPolynomial(polyNode* pHeadNode) {
	polyNode *tmp = pHeadNode;
	if (tmp == NULL) { // ó�� ������ ��
		printf("It's EMPTY!!!!");
		return;
	}
	while (1) {
		if (tmp->expon == 0)
			printf("%d", tmp->coef); // �����
		else if (tmp->expon == 1)
			printf("%dx", tmp->coef); // x ��
		else
			printf("%dx^%d", tmp->coef, tmp->expon);
		tmp = tmp->next;
		if (tmp == NULL) {
			printf("\n");
			break;
		}
		else 
			printf(" + ");
		
	}
}
void clearPolynomial(polyNode** pHeadNode) {
	if (*pHeadNode == NULL) { // ó�� ������ ��
		printf("It's EMPTY!!!!\n");
		return;
	}
	while (*pHeadNode != NULL) {
		removePolynomial(pHeadNode, (*pHeadNode)->expon);
	}
}
int findPolynomial(polyNode* pHeadNode, int expon) {
	int i = 0;
	polyNode *tmp = pHeadNode; // ���۳�����
		while (tmp != NULL) {
		if (tmp->expon == expon) { //������ ����������
			return i;
		}
		tmp = tmp->next;
		i++;
	}
	return FALSE; //������ -1 ��ȯ
}