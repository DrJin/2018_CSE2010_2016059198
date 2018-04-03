#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE -1

typedef struct polyNode {
	int coef;
	int expon;
	struct polyNode* next;
}polyNode;

void addPolynomial(polyNode** pHeadNode, int coef, int expon); // 항 추가
void removePolynomial(polyNode** pHeadNode, int expon); // 항 제거
polyNode* multiplication(polyNode* A, polyNode* B); // 다항식 곱하기
void showPolynomial(polyNode* pHeadNode); //다항식 출력
void clearPolynomial(polyNode** pHeadNode); // 다항식 전체 제거
int findPolynomial(polyNode* pHeadNode, int expon); // 항 찾기

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
				//계수와 차수를 입력 받아서 polynomial에 추가하는 함수 실행
				//이미 존재하는 차수를 입력 받을 경우 추가할 수 없음
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
				//차수를 입력 받아서 polynomial에서 제거하는 함수 실행
				if (poly == 'A')
					removePolynomial(&A, expon);
				else
					removePolynomial(&B, expon);
			}
			break;
		case 3:
			printf("\nMultiplication with A and B\n");
			//C = A * B 연산을 수행
			C = multiplication(A, B);
			printf("C: ");
			//C의 결과를 출력
			showPolynomial(C);
			break;
		case 4:
			//A,B polynomial 각각 출력
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
				//해당 polynomial를 초기화 시키는 함수 실행
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
	if ( count != FALSE) { // 이미 있을 경우
		printf("ss");
		for (i = 0; i < count; i++) 
			tmp = tmp->next; // 해당 차수까지이동
		tmp->coef += coef; // 계수 합계
	}
	else { // 없을 경우
		polyNode *newNode; // 새로 생성
		newNode = (polyNode *)malloc(sizeof(polyNode));
		newNode->expon = expon;
		newNode->coef = coef; 
		newNode->next = NULL; // 초기화
		if (tmp == NULL) { // 처음 생성될 때
			*pHeadNode = newNode;
			return;
		}
		int num = 0;
		while (tmp != NULL) { // 얼마나 멀리 떨어져있는지 찾기
			if (tmp->expon < expon)
				num++;
			tmp = tmp->next;
		}
		tmp = *pHeadNode;
		if (num == 0) { // 가장 작을 때 앞쪽에 추가

			newNode->next = tmp;
			*pHeadNode = newNode;
		}
		else { //클 때 뒤쪽에 추가
			for (i = 0; i < num-1; i++) {
				tmp = tmp->next;
			}
			newNode->next = tmp->next; // 새 노드는 현재 노드의 다음 노드를 가리킴
			tmp->next = newNode; //현재 노드는 새 노드를 가리킴
		}
	}
	
}
void removePolynomial(polyNode** pHeadNode, int expon) {
	int i, count = 0;
	polyNode* prevNode = *pHeadNode;
	polyNode* tmp = NULL;
	count = findPolynomial(*pHeadNode, expon);
	if (count == -1 || prevNode == NULL) {//제거할 항이 없거나 비어있을 경우
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
	else { // 항이 하나만 남았을 경우
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
	
	while (tmp1 != NULL) { // A를 늘려가면서
		while (tmp2 != NULL) { //B를 늘려가면서
			addPolynomial(&newPoly, tmp1->coef*tmp2->coef , tmp1->expon+tmp2->expon); // coef는 곱셈, expon은 덧셈
			tmp2 = tmp2->next;
		}
		tmp2 = B; //처음으로
		tmp1 = tmp1->next;
	}
	return newPoly;
}
void showPolynomial(polyNode* pHeadNode) {
	polyNode *tmp = pHeadNode;
	if (tmp == NULL) { // 처음 생성될 때
		printf("It's EMPTY!!!!");
		return;
	}
	while (1) {
		if (tmp->expon == 0)
			printf("%d", tmp->coef); // 상수항
		else if (tmp->expon == 1)
			printf("%dx", tmp->coef); // x 항
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
	if (*pHeadNode == NULL) { // 처음 생성될 때
		printf("It's EMPTY!!!!\n");
		return;
	}
	while (*pHeadNode != NULL) {
		removePolynomial(pHeadNode, (*pHeadNode)->expon);
	}
}
int findPolynomial(polyNode* pHeadNode, int expon) {
	int i = 0;
	polyNode *tmp = pHeadNode; // 시작노드부터
		while (tmp != NULL) {
		if (tmp->expon == expon) { //차수가 같을때까지
			return i;
		}
		tmp = tmp->next;
		i++;
	}
	return FALSE; //없으면 -1 반환
}