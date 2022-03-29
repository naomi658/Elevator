#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Sleep 함수 헤더파일
#pragma warning(disable: 4996)

void check_weight(int sum_weight); //몸무게 제한 함수

typedef struct {
	int floor; //입력받을 층
	int weight; // 몸무게
}Elevator;

void check_weight(int sum_weight)
{
	if (sum_weight > 700)
	{
		printf("\a몸무게 초과\a\n");
		Sleep(1000); // 1초 대기하는 함수
		system("cls");
	}
}

int main()
{

	int ele[12][3] = {
	   { 1,1,1 },
	   { 1,0,1 },
	   { 1,0,1 },
	   { 1,0,1 },
	   { 1,0,1 },
	   { 1,0,1 },
	   { 1,0,1 },
	   { 1,0,1 },
	   { 1,0,1 },
	   { 1,0,1 },
	   { 1,2,1 },
	   { 1,1,1 }
	}; // 엘레베이터 모양

	srand((unsigned)time(NULL));

	int i, j; // 반복문에 쓸 변수
	int human = 0; //인원수
	int max_human = 10;   //최대 인원수
	int weight; // 랜덤으로 몸무게 설정
	int sum_weight = 0; //전체 인원 몸무게의 합
	int live_floor = 1; 
	int x = 10, y = 1; //최고 층, 최저 층
	int f_x = 0;

	Elevator e;

	FILE *fp;
	fp = fopen("elevator.txt", "w");
	fputs("0 0 0 0 0 0 0 0 0 0", fp);
	fclose(fp);

	while (1)
	{
		for (i = 0; i < 12; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (ele[i][j] == 1)
					printf("■");
				if (ele[i][j] == 0)
					printf("□");
				if (ele[i][j] == 2)
					printf("＠");
			}
			printf("\n");
		}

		human = (rand() % 11) + 1; // 난수를 발생시켜 랜덤으로 사람 수 설정

		if (human > max_human) // 탑승 인원이 제한 인원수보다 많을 때
		{
			printf("\a정원 초과 입니다.\a\n");
			Sleep(1000); // 단위 ms이므로 1초 1000
			system("cls"); // 콘솔화면 깨끗이 지워주는 함수 ( 헤더 파일 : stdlib.h )
			continue;
		}

		printf("%d명이 탔습니다.\n", human);
		printf("층을 입력해주세요 (1 ~ 10) : ");
		scanf("%d", &e.floor);

		if (e.floor > live_floor)
		{
			ele[x][y] = 0;
			f_x = e.floor - live_floor;
			x = x - f_x; // 층 이동

			ele[x][y] = 2; // @로 층 표시
			live_floor = e.floor;
			human = (rand() % human) + 1; // 내릴 사람 랜덤으로 지정
			printf("%d명이 내렸습니다.\n", human);
			Sleep(2000); //2초 대기
		}

		else if (e.floor < live_floor)
		{
			ele[x][y] = 0;
			f_x = live_floor - e.floor;
			x = x + f_x;

			ele[x][y] = 2;
			live_floor = e.floor;
			human = (rand() % human) + 1;
			printf("%d명이 내렸습니다.\n", human);
			Sleep(2000);
		}

		fp = fopen("elevator.txt", "r"); 
		int people[10] = { 0 };
		for (i = 0; i < 10; i++) {
			fscanf(fp, "%d", &people[i]);

			if (i == e.floor - 1)
			{
				people[i] += human;
			}
		}
		fclose(fp);
		fp = fopen("elevator.txt", "w");

		for (i = 0; i < 10; i++)
			fprintf(fp, "%d ", people[i]);
		fclose(fp);


		//사용인원 출력하고 싶을 때
		fp = fopen("elevator.txt", "r");
		for (i = 0; i < 10; i++) {
			fscanf(fp, "%d", &people[i]);
			printf("%d ", people[i]);
		}
		printf("\n");
		Sleep(2000);

		for (int i = 0; i < human; i++)
		{
			e.weight = (rand() % 101) + 30; //31부터 130까지

			sum_weight += e.weight;

			check_weight(sum_weight);
		}

		sum_weight = 0; // 총 몸무게 0으로 초기화

		system("cls");
	}
	return 0;
}