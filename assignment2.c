#include<stdio.h>

int main()
{
	int n=0, cnt=0;
	printf("원판의 갯수를 입력하시오 : ");
	scanf_s("%d", &n);

	cnt = hanoi(n, 'A', 'B', 'C');
	printf("총 이동 횟수 : %d", cnt);
}
int hanoi(int n, char from, char mid, char to) {
	int cnt=0; // 원판 이동 횟수
	if (n == 1) { // 마지막 남은 1번 원판
		cnt++;
		printf("%d번 원판을 %c에서 %c로 이동\n",n,from,to);
	}
	else
	{
		cnt+=hanoi(n - 1, from, to, mid); // mid로 n-1개의 하노이탑을 옯기는 과정
		cnt++; //n번 원판의 이동
		printf("%d번 원판을 %c에서 %c로 이동\n", n, from, to); // 모든 과정의 중간에 오는 것은 n번 원판을 마지막 위치에 놓는 것
		cnt+=hanoi(n - 1, mid, from, to); // mid에 생긴 n-1개의 하노이탑을 to로 옮기는 과정
	}
	return cnt; // 이동 횟수는 (2^n)-1 이 될거다
}