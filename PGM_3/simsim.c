#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 8
int use_scale(int *B, int*L_num, int *R_num);
int answer(int *B);
void scale_out(int num, int L, int R);

int main()
{
	int i, left_num, right_num;
	int num;
	int ball[SIZE];
	srand((long)time(NULL));
	for (i = 0; i<SIZE; i++) //���� ���� �ʱ�ȭ
		ball[i] = 2;
	ball[rand() % SIZE] = 1;

	printf("%d���� �� �߿��� 1���� ���� ���԰� ����.\n\n", SIZE);
	for (i = 0; i<SIZE; i++)
		printf(" O ");
	printf("\n");
	for (i = 0; i<SIZE; i++)
		printf("%2d ", i + 1);
	printf("\n");
	//for(i=0;i<SIZE;i++) //���� ���� �ʱ�ȭ
	// printf("ball[%d]=%d ",i,ball[i]);
	printf("\n\n");
	printf("������ϱ�? ������ �󸶵��� ��� �����մϴ�.\n");

	while (1)
	{
		printf("\n _________________\n");
		printf(" |       |       |\n");
		printf(" |       |       |\n");
		printf("===      |      ===\n");
		printf("         |\n");
		printf("         |\n");
		printf("     ---------\n");
	A:
		printf("������ = 1, ���� = 2, ���� = 0\n");
		printf("��ȣ�� �Է��Ͽ� �ּ��� : ");
		scanf("%d", &num);
		if (num != 0 && num != 1 && num != 2)
			goto A;
		if (num == 1)
		{
			i = use_scale(ball, &left_num, &right_num);
			scale_out(i, left_num, right_num);
		}
		else if (num == 2)
		{
			i = answer(ball);
			switch (i)
			{
			case 1:
				printf("�����մϴ� �����Դϴ�\n\n");
				return 0;
			case 2:
				printf("������ �ƴմϴ�\n\n");
				break;
			}
		}
		else if (num == 0)
			return 0;
	}

}

int use_scale(int *B, int*L_num, int *R_num)
{
	int i, L, R;
	int left[SIZE] = { 0 };
	int right[SIZE] = { 0 };
ONE:
	printf("\n���� ���￡ �ø� ��: ");
	scanf("%d", L_num);
	//printf("\n%d",*L_num);
	for (i = 0, L = 0; i<*L_num; i++)
	{
		printf("���� ���￡ %d��° �ø� ���� ��ȣ�� �Է��Ͻÿ�(�����Է½� �������ٽ� �Է�) : ", i + 1);
		scanf("%d", &left[i]);
		if (left[i]<0)
			goto ONE;
		else
			L += B[left[i] - 1];
	}
	printf("\n");
O:
	printf("������ ���￡ �ø� ��: ");
	scanf("%d", R_num);
	for (i = 0, R = 0; i< *R_num; i++)
	{
		printf("������ ���￡ %d��°�ø� ���� ��ȣ�� �Է��Ͻÿ�(�����Է½� �������ٽ� �Է�) : ", i + 1);
		scanf("%d", &right[i]);
		if (left[i]<0)
			goto O;
		else
			R += B[right[i] - 1];
	}
	printf("L=%d, R=%d\n", L, R);
	if (L>R)
		return 1;
	else if (L<R)
		return 2;
	else if (L == R)
		return 3;
	return 0;
}
void scale_out(int num, int L, int R)
{
	int i;
	switch (num)
	{
	case 1:
		printf("            ______\n");
		printf("       _____     |\n");
		printf(" ______  |    ");
		for (i = 0; i<R; i++)
			printf("O");
		printf("\n");
		printf("               ===\n");
		printf(" |       |       \n");
		for (i = 0; i<L; i++)
			printf("O");
		printf("\n");
		printf("===      |\n");
		printf("     ---------\n");
		break;
	case 2:
		printf(" ______\n");
		printf(" |     _____     \n");
		printf("         |   ______\n");
		for (i = 0; i<L; i++)
			printf("O");
		printf("\t |      ��\n");
		printf("===      |      \n");
		printf("              ");
		for (i = 0; i<R; i++)
			printf("O");
		printf("\n");
		printf("               ===\n");
		printf("     ---------\n");
		break;
	case 3:
		printf(" _________________\n");
		printf(" |       |       |\n");
		printf(" |       |       |\n");
		for (i = 0; i<L; i++)
			printf("O");
		printf("\t\t");
		for (i = 0; i<R; i++)
			printf("O");
		printf("\n");
		printf("===      |      ===\n");
		printf("         |\n");
		printf("         |\n");
		printf("     ---------\n");
		break;
	}
}
int answer(int *B)
{
	int a;
	printf("������ �Է��Ͻÿ�(����ȣ) : ");
	scanf("%d", &a);
	printf("%d\n", a);
	if (B[a - 1] == 1)
		return 1;
	else
		return 2;
}