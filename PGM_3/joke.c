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
		printf("┌─ LetpleBot  ──────────────────────────────────┐\n");
		if (strcmp(truth, answer) == 0)
		{
			printf(" 정답입니다! 8888");
		}
		else
		{
			printf(" 틀렸습니다..");
		}
		printf("\n");
		printf("└─────────────────────────────────────────┘\n\n");
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
			random = rand() % 13;         //질문의 답중 출력할 답을 랜덤으로 설정
			joke_question(jk, random);               //출력할 대답으로 이동
			nfgets(buf, SIZE, jk);               //퀴즈를 buf에 저장
			fclose(jk);
			printf("┌─ LetpleBot  ──────────────────────────────────┐\n");
			printf(" %s\n", buf);
			printf("└─────────────────────────────────────────┘\n");       
			printf(" /exit를 입력하면 종료합니다.\n\n");

			FILE *jk = fopen("joke.txt", "r");
			joke_question(jk, random+13);
			nfgets(truth, SIZE, jk);
			fclose(jk);

			return 0;
		}
		rewind(jk);                              //파일탐색 위치를 처음으로 돌림
	}

	fclose(jk);
	return "";
}

char *allocate(int len)
{  //메모리동적할당
	return (char*)malloc(sizeof(char)*len);
}	

char *nfgets(char *buf, int max, FILE *file) 
{
	fgets(buf, max, file);                        //한줄불러옴
	buf[strlen(buf) - 1] = '\0';                  //개행문자(엔터)를 제거해줌
	return buf;                                 //개행문자 제거한걸 리턴
}
