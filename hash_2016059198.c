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

//���ڿ��� �޾Ƽ� �� ���ڿ��� ASKII Code�� ���ؼ� �ݳ��ϴ� �Լ�
int transform(char *key) {
	int i;
	int number = 0;
	int size = strlen(key);
	for (i = 0; i < size; i++)
		number += key[i];
	return number;
}

//�ؽ� �Լ�
int hashFunction(char *key) {
	return transform(key) % TABLE_SIZE;
}

void addHashTable(Element item, Element ht[]) {
	int i, hashValue;
	i =  hashValue = hashFunction(item.key);
	

	while (!empty(ht[i])) { //������� ������
		if (equal(ht[i], item)) { //key���� ������
			printf("�ߺ�!!!!!!\n");
			return;
		}
		else {//key���� �ٸ���
			if (i == hashValue - 1) {//i�� Buckets�� �ѹ����� �� ��������
				printf("�� á���\n");
				return;
			}
			else if (i != TABLE_SIZE - 1) //i�� ���� �ƴϸ�
				i++; //���� ��ġ�� ��
			else
				i = 0;
		}
	}
	ht[i] = item; // elemeent ����
	
}

void hashSearch(Element item, Element ht[]) {
	int i, hashValue;
	i = hashValue = hashFunction(item.key);

	while (!(empty(ht[i]))) {
		if (ht[i].key[0] != NULL && equal(ht[i],item)) { // ������� �ʰ� key�� ������
			printf("Ž�� ����! ������!\n");
			return;
		}
		if (i == hashValue - 1) //i�� Buckets�� �ѹ����� �� ��������
			break;
		else if (i != TABLE_SIZE - 1) //i�� ���� �ƴϸ�
			i++; //���� ��ġ�� ��
		else
			i = 0;
	}
	
	printf("Ž������\n");
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
		printf("���ϴ� �۾��� ����(0 : �߰�, 1 : Ž��, 2 : ����) === ");
		scanf_s("%d", &op);
		if (op == 2)
			break;
		switch (op) {
		case 0:
			printf("Ű �Է� : ");
			scanf("%s", tmp.key);
			addHashTable(tmp, hashTable);
			printHashTable(hashTable);
			break;
		case 1:
			printf("Ű �Է� : ");
			scanf("%s", tmp.key);
			hashSearch(tmp, hashTable);
			printHashTable(hashTable);
			break;
		default:
			printf("�߸� �Է��߾�� �Ф�\n");
			continue;
		}
	}
	return 0;
}