#include<stdio.h>

int main()
{
	int n=0, cnt=0;
	printf("������ ������ �Է��Ͻÿ� : ");
	scanf_s("%d", &n);

	cnt = hanoi(n, 'A', 'B', 'C');
	printf("�� �̵� Ƚ�� : %d", cnt);
}
int hanoi(int n, char from, char mid, char to) {
	int cnt=0; // ���� �̵� Ƚ��
	if (n == 1) { // ������ ���� 1�� ����
		cnt++;
		printf("%d�� ������ %c���� %c�� �̵�\n",n,from,to);
	}
	else
	{
		cnt+=hanoi(n - 1, from, to, mid); // mid�� n-1���� �ϳ���ž�� ����� ����
		cnt++; //n�� ������ �̵�
		printf("%d�� ������ %c���� %c�� �̵�\n", n, from, to); // ��� ������ �߰��� ���� ���� n�� ������ ������ ��ġ�� ���� ��
		cnt+=hanoi(n - 1, mid, from, to); // mid�� ���� n-1���� �ϳ���ž�� to�� �ű�� ����
	}
	return cnt; // �̵� Ƚ���� (2^n)-1 �� �ɰŴ�
}