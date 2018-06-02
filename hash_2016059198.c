#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 10
#define TABLE_SIZE 13
#define empty(e) (strlen(e.key) == 0)
#define equal(e1, e2) (!strcmp(e1.key,e2.key))

typedef struct Element {
	char key[KEY_SIZE];
}Element;


Element hashTable[TABLE_SIZE];

void initTable(Element ht[]) {
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
		ht[i].key[0] = NULL;
}

//문자열을 받아서 각 문자열의 ASKII Code를 더해서 반납하는 함수
int transform(char *key) {
	int i;
	int number = 0;
	int size = strlen(key);
	for (i = 0; i < size; i++)
		number += key[i];
	return number;
}

//해시 함수
int hashFunction(char *key) {
	return transform(key) % TABLE_SIZE;
}

void addHashTable(Element item, Element ht[]) {
	int i, hashValue;
	i =  hashValue = hashFunction(item.key);
	

	while (!empty(ht[i])) { //비어있지 않으면
		if (equal(ht[i], item)) { //key값이 같으면
			printf("중복!!!!!!\n");
			return;
		}
		else {//key값이 다르면
			if (i == hashValue - 1) {//i가 Buckets를 한바퀴를 다 돌았으면
				printf("꽉 찼어요\n");
				return;
			}
			else if (i != TABLE_SIZE - 1) //i가 끝이 아니면
				i++; //다음 위치와 비교
			else
				i = 0;
		}
	}
	ht[i] = item; // elemeent 삽입
	
}

void hashSearch(Element item, Element ht[]) {
	int i, hashValue;
	i = hashValue = hashFunction(item.key);

	while (!(empty(ht[i]))) {
		if (ht[i].key[0] != NULL && equal(ht[i],item)) { // 비어있지 않고 key가 같으면
			printf("탐색 성공! 존재함!\n");
			return;
		}
		if (i == hashValue - 1) //i가 Buckets를 한바퀴를 다 돌았으면
			break;
		else if (i != TABLE_SIZE - 1) //i가 끝이 아니면
			i++; //다음 위치와 비교
		else
			i = 0;
	}
	
	printf("탐색실패\n");
}

void printHashTable(Element ht[]) {
	int i = 0;
	for (i = 0; i < TABLE_SIZE; i++) {
		printf("[%d] : %s\n", i,ht[i].key);
	}
}

int main() {
	Element tmp;
	int op = 0;

	while (1) {
		printf("원하는 작업을 선택(0 : 추가, 1 : 탐색, 2 : 종료) === ");
		scanf_s("%d", &op);
		if (op == 2)
			break;
		switch (op) {
		case 0:
			printf("키 입력 : ");
			scanf("%s", tmp.key);
			addHashTable(tmp, hashTable);
			printHashTable(hashTable);
			break;
		case 1:
			printf("키 입력 : ");
			scanf("%s", tmp.key);
			hashSearch(tmp, hashTable);
			printHashTable(hashTable);
			break;
		default:
			printf("잘못 입력했어요 ㅠㅠ\n");
			continue;
		}
	}
	return 0;
}