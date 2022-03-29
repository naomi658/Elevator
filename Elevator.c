#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Sleep �Լ� �������
#pragma warning(disable: 4996)

void check_weight(int sum_weight); //������ ���� �Լ�

typedef struct {
	int floor; //�Է¹��� ��
	int weight; // ������
}Elevator;

void check_weight(int sum_weight)
{
	if (sum_weight > 700)
	{
		printf("\a������ �ʰ�\a\n");
		Sleep(1000); // 1�� ����ϴ� �Լ�
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
	}; // ���������� ���

	srand((unsigned)time(NULL));

	int i, j; // �ݺ����� �� ����
	int human = 0; //�ο���
	int max_human = 10;   //�ִ� �ο���
	int weight; // �������� ������ ����
	int sum_weight = 0; //��ü �ο� �������� ��
	int live_floor = 1; 
	int x = 10, y = 1; //�ְ� ��, ���� ��
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
					printf("��");
				if (ele[i][j] == 0)
					printf("��");
				if (ele[i][j] == 2)
					printf("��");
			}
			printf("\n");
		}

		human = (rand() % 11) + 1; // ������ �߻����� �������� ��� �� ����

		if (human > max_human) // ž�� �ο��� ���� �ο������� ���� ��
		{
			printf("\a���� �ʰ� �Դϴ�.\a\n");
			Sleep(1000); // ���� ms�̹Ƿ� 1�� 1000
			system("cls"); // �ܼ�ȭ�� ������ �����ִ� �Լ� ( ��� ���� : stdlib.h )
			continue;
		}

		printf("%d���� �����ϴ�.\n", human);
		printf("���� �Է����ּ��� (1 ~ 10) : ");
		scanf("%d", &e.floor);

		if (e.floor > live_floor)
		{
			ele[x][y] = 0;
			f_x = e.floor - live_floor;
			x = x - f_x; // �� �̵�

			ele[x][y] = 2; // @�� �� ǥ��
			live_floor = e.floor;
			human = (rand() % human) + 1; // ���� ��� �������� ����
			printf("%d���� ���Ƚ��ϴ�.\n", human);
			Sleep(2000); //2�� ���
		}

		else if (e.floor < live_floor)
		{
			ele[x][y] = 0;
			f_x = live_floor - e.floor;
			x = x + f_x;

			ele[x][y] = 2;
			live_floor = e.floor;
			human = (rand() % human) + 1;
			printf("%d���� ���Ƚ��ϴ�.\n", human);
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


		//����ο� ����ϰ� ���� ��
		fp = fopen("elevator.txt", "r");
		for (i = 0; i < 10; i++) {
			fscanf(fp, "%d", &people[i]);
			printf("%d ", people[i]);
		}
		printf("\n");
		Sleep(2000);

		for (int i = 0; i < human; i++)
		{
			e.weight = (rand() % 101) + 30; //31���� 130����

			sum_weight += e.weight;

			check_weight(sum_weight);
		}

		sum_weight = 0; // �� ������ 0���� �ʱ�ȭ

		system("cls");
	}
	return 0;
}