#include<stdio.h>
#include<math.h>
#include<windows.h>
void joke_question(FILE *jk, int random);
char *nfgets(char *buf, int max, FILE *file);
char *allocate(int len);
char* search_joke();
#define SIZE 200

char truth[100];
int random = 0;

int main()
{
	while (1)
	{
		srand((unsigned)time(NULL));
		char joke[100];
		char answer[100];
		FILE *jk = fopen("joke.txt", "r");
		search_joke(jk, random);
		printf("user: ");
		gets(answer);
		if (strcmp(answer, "/exit") == 0)
		{
			break;
		}
		printf("���� LetpleBot  ����������������������������������������������������������������������\n");
		if (strcmp(truth, answer) == 0)
		{
			printf(" �����Դϴ�! 8888");
		}
		else
		{
			printf(" Ʋ�Ƚ��ϴ�..");
		}
		printf("\n");
		printf("��������������������������������������������������������������������������������������\n\n");
		Sleep(1000);
		system("cls");
	}
	return 0;
}

void joke_question(FILE *jk, int random) 
{
	for (int i = 0; i < random; i++) {
		while (!feof(jk))
		{
			if (fgetc(jk) == '\n') 
				break;
		}
	}
}

char* search_joke()
{
	FILE *jk = fopen("joke.txt", "r");
	char *buf;
	buf = allocate(SIZE);

	for (int i = 0; i < 2; i++) 
	{
		while (!feof(jk))
		{                  
			random = rand() % 13;         //������ ���� ����� ���� �������� ����
			joke_question(jk, random);               //����� ������� �̵�
			nfgets(buf, SIZE, jk);               //��� buf�� ����
			fclose(jk);
			printf("���� LetpleBot  ����������������������������������������������������������������������\n");
			printf(" %s\n", buf);
			printf("��������������������������������������������������������������������������������������\n");       
			printf(" /exit�� �Է��ϸ� �����մϴ�.\n\n");

			FILE *jk = fopen("joke.txt", "r");
			joke_question(jk, random+13);
			nfgets(truth, SIZE, jk);
			fclose(jk);

			return 0;
		}
		rewind(jk);                              //����Ž�� ��ġ�� ó������ ����
	}

	fclose(jk);
	return "";
}

char *allocate(int len)
{  //�޸𸮵����Ҵ�
	return (char*)malloc(sizeof(char)*len);
}	

char *nfgets(char *buf, int max, FILE *file) 
{
	fgets(buf, max, file);                        //���ٺҷ���
	buf[strlen(buf) - 1] = '\0';                  //���๮��(����)�� ��������
	return buf;                                 //���๮�� �����Ѱ� ����
}
