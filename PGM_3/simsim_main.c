#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#define SIZE 200
#pragma warning(disable:4996);

void clearBuffer(void)                                      //잔상 제거
{
	while (getchar() != '\n');
}
char *allocate(int len);                           //문자열 동적할당
void input_data(char *buf, char *who);                  //문자열을 입력받음
char *search_question(char *input, int teach);            //질문에 대한 대답을 찾아서 표시
void print_answer(char *output);                     //대답을 출력해주는 부분
void teach_answer(char *buf);                        //대답을 파일에 입력하게함 
void next_line(FILE *file, int line);                  //키워드에 적합한 대답을 찾는 함수
char *nfgets(char *buf, int max, FILE *file);            //'\0' 빼고 파일입력
void log_save(char* input, char* output, char* user_name);   //Log파일 생성
int filtering(char *input);                           //욕 필터링
void textcolor(int color_number);                     //글씨 색변경
char answer = 0;
void setrgb(char *s);                              //배경 설정

void main() {
	system("title Let's Play! -렛플봇-");
	system("color f0");
	MessageBox(NULL, "사용방법 : 자신의 이름을 정한 후 하고싶은 말을 마음껏 쳐주세요! \n렛플봇을 가르치고 싶다면 \"/t 질문\" 형식으로 써주세요. \n+)대화를 종료하고 싶다면 \"/exit\"를 입력해 주세요\n제작자 : 정상현, 정훈, 최연진", "렛플봇 설명서", MB_OK | MB_ICONINFORMATION);
	MessageBox(NULL, "특정 명령어가 궁금할 경우 /help를 치시기 바랍니다!\n", "렛플봇 설명서", MB_OK | MB_ICONINFORMATION);
	int i, j, k;
	char *buf;
	int teach;
	char *input;
	char *output = 0;
	char user_name[50];
	int flag = 0;
	buf = allocate(SIZE);
	FILE *fp;
	char answer = 0;
	srand((unsigned)time(NULL));

	if (flag == 0) {
		input_data(user_name, "당신의 이름");
		//textcolor(14);
		printf("┌─ LetpleBot  ──────────────────────────────────┐\n");
		printf(" 안녕하세요! %s님!\n", user_name);
		printf("└─────────────────────────────────────────┘\n\n");
		//textcolor(7);

		while (1) {
			teach = 0;

			//입력
			input_data(buf, user_name);                   //buf에 입력받음
			input = allocate(strlen(buf) + 1);             //input을 buf크기만큼 동적할당(널문자 포함)
			strcpy(input, buf);                         //input에 buf를 넣음

														//입력한 내용이 욕설인지 아닌지 검사
			if (filtering(input) == 1) {                  //욕검출시 intput free하고 continue()
				free(input);
				continue;
			}
			if (!strcmp("/exit", input)) {             //"잘가" 입력시 심심이 종료
				MessageBox(NULL, "다음에 보자~~", "렛플봇의 작별인사", MB_OK | MB_ICONINFORMATION);
				break;
			}
			if (!strncmp(input, "/t ", 3)) {            //if 심심이 가르치기 /t 질문 형식 일때
				input = input + 3;    //앞에 '/t '를 input에서 지움
				teach_answer(input);
				input = input - 3;
				free(input);
				continue;
			}

			if (!strcmp("/game", input)) {
				MessageBox(NULL, "게임을 시작하겠습니다!", "렛플봇", MB_OK | MB_ICONINFORMATION);
				WinExec("C:\\Users\\jshga\\source\\repos\\Let's Play!\\Debug\\Game.exe", SW_SHOW);
				flag = 1;
				break;
			}

			if (!strcmp("/help", input)) {
				MessageBox(NULL, "☆도움말☆\n/help: 도움말 항목을 봅니다.\n/game: 내장되어있는 게임을 실행시킵니다.\n/exit: 렛플봇을 종료합니다.\n/clean: 챗 내용을 정리합니다.\n/reset: 렛플봇에게 가르친 모든 걸 초기화 시킵니다.\n/joke: 렛플봇이 농담을 해줍니다.\n/color: 콘솔의 폰트와 배경을 변경합니다.\n(+/help color: /color의 도움말을 봅니다.)", "렛플봇 사용설명서", MB_OK | MB_ICONINFORMATION);
				continue;
			}

			if (!strcmp("/clean", input)) {
				MessageBox(NULL, "화면 청소가 완료 되었습니다!", "렛플봇", MB_OK | MB_ICONINFORMATION);
				system("cls");
				continue;
			}

			if (!strcmp("/joke", input)) {
				MessageBox(NULL, "화면 청소가 완료 되었습니다!", "렛플봇", MB_OK | MB_ICONINFORMATION);

				system("cls");
				continue;
			}

			if (!strcmp("/reset", input)) {
				if (MessageBox(NULL, "정말 데이터를 초기화 시키겠습니까?", "질문", MB_YESNO | MB_ICONINFORMATION) == IDYES)
				{
					fp = fopen("question.txt", "w");
					fprintf(fp, "");
					fclose(fp);
					MessageBox(NULL, "데이터 초기화가 완료 되었습니다!", "렛플봇", MB_OK | MB_ICONINFORMATION);
					continue;
				}
				else
				{
					continue;
				}
			}

			if (!strcmp("/help color", input)) {
				system("color help");
				continue;
			}

			//출력
			strcpy(buf, search_question(input, teach));     //input에 맞는 output을 찾아서 buf에 저장, 없으면 NULL
			output = allocate(strlen(buf) + 1);            //output을 buf크기만큼 동적할당(널문자 포함)
			strcpy(output, buf);                     //output에 buf를 넣음

													 //가르치는 부분
			if (strcmp(output, "")) {                  //질문에 대한 대답있을경우 

				if (teach == 1) {                     // 가르치기 상태일때
					printf("이미 렛플봇이 알고있는 질문입니다.\n\n");
					input = input - 3;                  //할당 받은 만큼 free하기 위해 다시 input의 크기를 원래대로 해줌
				}
				else {
					log_save(input, output, user_name);  //INPUT과 OUTPUT이 정상적으로 출력되었을때 저장
				}
				print_answer(output);   //output을 출력 
			}
			else {                                 //-질문에 일치하는 대답이 없을경우
				printf("렛플봇이 모르는 말입니다. 가르쳐주세요.\n");
				teach_answer(input);
				free(input);
				continue;
			}
		}

		//FREE
		free(input);
		free(output);
	}
}

char *allocate(int len) {  //메모리동적할당
	return (char*)malloc(sizeof(char)*len);
}

void input_data(char *buf, char *who) {
	fflush(stdin);  //입력장치 초기화
	int color_input;
	FILE *fp;
	fp = fopen("Name.txt", "w");
	fscanf(fp, "%s", who);

	while (1) {                              //아무것도 입력안하면 반복 -> 입력할때 까직 반복               //누구 : 
		printf("%s : ", who);
		//textcolor(7); 
		nfgets(buf, SIZE, stdin);
		printf("\n");
		//내용을 SIZE만큼 프린트 stdin -> 출력장치
		if (strcmp(buf, "")) break;                  //입력되면 반복문 탈출
	}

}

//질문에 대한 대답을 찾아서 리턴, 없으면 ""
char *search_question(char *input, int teach) {
	FILE *fp;
	int output_num, random, check = 0, i;
	char *buf;
	char *similar;
	buf = allocate(SIZE);
	similar = allocate(SIZE);

	if ((fp = fopen("question.txt", "r")) == NULL) return "";   //파일이 없으면 리턴


	for (i = 0; i < 2; i++) {                     //총 2번 파일을 탐색 i - 0.완벽히 일치하는가,  1.조금 일치하는가
		while (!feof(fp)) {                        //파일 끝까직 탐색
			fscanf(fp, "%d", &output_num);            //질문의 답이 몇개인지 output_num에 저장
			nfgets(buf, SIZE, fp);                  //buf에 질문 저장

			if (i == 0 && !strcmp(input, buf)) check = 1;//질문과 완벽히 일치하는가

			if (i == 1 && strlen(buf) > 3 && strstr(input, buf) != NULL) { //if 유사한 질문이 있는가
				check = 1;
				if (teach == 0) printf("\n원하는 대답이 아닐경우 \"/t 질문\" 을 통해 가르쳐 주세요.\n\n");
			}

			if (check == 1)                        //input과 질문과 일치거나 비슷 하면
			{
				random = rand() % output_num;         //질문의 답중 출력할 답을 랜덤으로 설정
				next_line(fp, random);               //출력할 대답으로 이동
				nfgets(buf, SIZE, fp);               //대답을 buf에 저장
				fclose(fp);
				return buf;                        //저장한 대답을 리턴
			}
			next_line(fp, output_num + 1);            //다음 질문이 있는 파일위치로 이동
		}
		if (teach == 1) break;
		rewind(fp);                              //파일탐색 위치를 처음으로 돌림
	}

	fclose(fp);
	return "";
}


//대답을 프린트 해줌
void print_answer(char *output) {
	//textcolor(14);
	printf("┌─ LetpleBot  ──────────────────────────────────┐\n");
	printf(" %s\n", output);
	printf("└─────────────────────────────────────────┘\n\n");
	//textcolor(7);
}


//대답을 파일에 입력하게함 
void teach_answer(char *input) {
	char buf[SIZE];
	int num, i;
	char tmp;
	FILE *fp;
	fp = fopen("question.txt", "a");

	//textcolor(12); 
	printf("가르칠 대답의 갯수를 입력해 주세요( 0 입력시 스킵 )>>");
	//textcolor(7);
	scanf("%s", &buf);
	num = atoi(buf);
	clearBuffer();

	if (num == 0) {
		fclose(fp);
		return;
	}

	fprintf(fp, "%d%s\n", num, input);   //대답의 갯수와 질문을 저장         3안녕
	for (i = 0; i < num; i++) {         //대답의 갯수만큼 for문            안녕안녕
		input_data(buf, "TEACH");      //TEACH : 대답을 입력받음         웅 안녕
		fprintf(fp, "%s\n", buf);      //입력받은 대답을 파일에 저장      반가워
	}
	fprintf(fp, " \n");               //공백 처리
	fclose(fp);
}


//line만큼 다음줄로 이동
void next_line(FILE *file, int line) {
	int i;
	for (i = 0; i < line; i++) {
		while (!feof(file))
		{
			if (fgetc(file) == '\n') break;
		}
	}
}

char *nfgets(char *buf, int max, FILE *file) {
	fgets(buf, max, file);                        //한줄불러옴
	buf[strlen(buf) - 1] = '\0';                  //개행문자(엔터)를 제거해줌
	return buf;                                 //개행문자 제거한걸 리턴
}

//Log파일 생성
void log_save(char* input, char* output, char* user_name) {
	FILE *fp;
	fp = fopen("log.txt", "a");
	fprintf(fp, "%s : %s \n렛플봇 : %s\n", user_name, input, output);
	fclose(fp);
}


//욕 필터링
int filtering(char *input) {
	if (strstr(input, "시발") != NULL || strstr(input, "ㅗ") != NULL) {
		MessageBox(NULL, "험한 말 사용하지 말아줘요..", "렛플봇", MB_OK | MB_ICONWARNING); {
		}
		return 1;
	}
	return 0;
}


void textcolor(int color_number) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}