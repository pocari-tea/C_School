#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#define SIZE 200
#pragma warning(disable:4996);

void clearBuffer(void)                                      //�ܻ� ����
{
	while (getchar() != '\n');
}
char *allocate(int len);                           //���ڿ� �����Ҵ�
void input_data(char *buf, char *who);                  //���ڿ��� �Է¹���
char *search_question(char *input, int teach);            //������ ���� ����� ã�Ƽ� ǥ��
void print_answer(char *output);                     //����� ������ִ� �κ�
void teach_answer(char *buf);                        //����� ���Ͽ� �Է��ϰ��� 
void next_line(FILE *file, int line);                  //Ű���忡 ������ ����� ã�� �Լ�
char *nfgets(char *buf, int max, FILE *file);            //'\0' ���� �����Է�
void log_save(char* input, char* output, char* user_name);   //Log���� ����
int filtering(char *input);                           //�� ���͸�
void textcolor(int color_number);                     //�۾� ������
char answer = 0;
void setrgb(char *s);                              //��� ����

void main() {
	system("title Let's Play! -���ú�-");
	system("color f0");
	MessageBox(NULL, "����� : �ڽ��� �̸��� ���� �� �ϰ���� ���� ������ ���ּ���! \n���ú��� ����ġ�� �ʹٸ� \"/t ����\" �������� ���ּ���. \n+)��ȭ�� �����ϰ� �ʹٸ� \"/exit\"�� �Է��� �ּ���\n������ : ������, ����, �ֿ���", "���ú� ����", MB_OK | MB_ICONINFORMATION);
	MessageBox(NULL, "Ư�� ��ɾ �ñ��� ��� /help�� ġ�ñ� �ٶ��ϴ�!\n", "���ú� ����", MB_OK | MB_ICONINFORMATION);
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
		input_data(user_name, "����� �̸�");
		//textcolor(14);
		printf("���� LetpleBot  ����������������������������������������������������������������������\n");
		printf(" �ȳ��ϼ���! %s��!\n", user_name);
		printf("��������������������������������������������������������������������������������������\n\n");
		//textcolor(7);

		while (1) {
			teach = 0;

			//�Է�
			input_data(buf, user_name);                   //buf�� �Է¹���
			input = allocate(strlen(buf) + 1);             //input�� bufũ�⸸ŭ �����Ҵ�(�ι��� ����)
			strcpy(input, buf);                         //input�� buf�� ����

														//�Է��� ������ �弳���� �ƴ��� �˻�
			if (filtering(input) == 1) {                  //������ intput free�ϰ� continue()
				free(input);
				continue;
			}
			if (!strcmp("/exit", input)) {             //"�߰�" �Է½� �ɽ��� ����
				MessageBox(NULL, "������ ����~~", "���ú��� �ۺ��λ�", MB_OK | MB_ICONINFORMATION);
				break;
			}
			if (!strncmp(input, "/t ", 3)) {            //if �ɽ��� ����ġ�� /t ���� ���� �϶�
				input = input + 3;    //�տ� '/t '�� input���� ����
				teach_answer(input);
				input = input - 3;
				free(input);
				continue;
			}

			if (!strcmp("/game", input)) {
				MessageBox(NULL, "������ �����ϰڽ��ϴ�!", "���ú�", MB_OK | MB_ICONINFORMATION);
				WinExec("C:\\Users\\jshga\\source\\repos\\Let's Play!\\Debug\\Game.exe", SW_SHOW);
				flag = 1;
				break;
			}

			if (!strcmp("/help", input)) {
				MessageBox(NULL, "�ٵ��򸻡�\n/help: ���� �׸��� ���ϴ�.\n/game: ����Ǿ��ִ� ������ �����ŵ�ϴ�.\n/exit: ���ú��� �����մϴ�.\n/clean: ê ������ �����մϴ�.\n/reset: ���ú����� ����ģ ��� �� �ʱ�ȭ ��ŵ�ϴ�.\n/joke: ���ú��� ����� ���ݴϴ�.\n/color: �ܼ��� ��Ʈ�� ����� �����մϴ�.\n(+/help color: /color�� ������ ���ϴ�.)", "���ú� ��뼳��", MB_OK | MB_ICONINFORMATION);
				continue;
			}

			if (!strcmp("/clean", input)) {
				MessageBox(NULL, "ȭ�� û�Ұ� �Ϸ� �Ǿ����ϴ�!", "���ú�", MB_OK | MB_ICONINFORMATION);
				system("cls");
				continue;
			}

			if (!strcmp("/joke", input)) {
				MessageBox(NULL, "ȭ�� û�Ұ� �Ϸ� �Ǿ����ϴ�!", "���ú�", MB_OK | MB_ICONINFORMATION);

				system("cls");
				continue;
			}

			if (!strcmp("/reset", input)) {
				if (MessageBox(NULL, "���� �����͸� �ʱ�ȭ ��Ű�ڽ��ϱ�?", "����", MB_YESNO | MB_ICONINFORMATION) == IDYES)
				{
					fp = fopen("question.txt", "w");
					fprintf(fp, "");
					fclose(fp);
					MessageBox(NULL, "������ �ʱ�ȭ�� �Ϸ� �Ǿ����ϴ�!", "���ú�", MB_OK | MB_ICONINFORMATION);
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

			//���
			strcpy(buf, search_question(input, teach));     //input�� �´� output�� ã�Ƽ� buf�� ����, ������ NULL
			output = allocate(strlen(buf) + 1);            //output�� bufũ�⸸ŭ �����Ҵ�(�ι��� ����)
			strcpy(output, buf);                     //output�� buf�� ����

													 //����ġ�� �κ�
			if (strcmp(output, "")) {                  //������ ���� ���������� 

				if (teach == 1) {                     // ����ġ�� �����϶�
					printf("�̹� ���ú��� �˰��ִ� �����Դϴ�.\n\n");
					input = input - 3;                  //�Ҵ� ���� ��ŭ free�ϱ� ���� �ٽ� input�� ũ�⸦ ������� ����
				}
				else {
					log_save(input, output, user_name);  //INPUT�� OUTPUT�� ���������� ��µǾ����� ����
				}
				print_answer(output);   //output�� ��� 
			}
			else {                                 //-������ ��ġ�ϴ� ����� �������
				printf("���ú��� �𸣴� ���Դϴ�. �������ּ���.\n");
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

char *allocate(int len) {  //�޸𸮵����Ҵ�
	return (char*)malloc(sizeof(char)*len);
}

void input_data(char *buf, char *who) {
	fflush(stdin);  //�Է���ġ �ʱ�ȭ
	int color_input;
	FILE *fp;
	fp = fopen("Name.txt", "w");
	fscanf(fp, "%s", who);

	while (1) {                              //�ƹ��͵� �Է¾��ϸ� �ݺ� -> �Է��Ҷ� ���� �ݺ�               //���� : 
		printf("%s : ", who);
		//textcolor(7); 
		nfgets(buf, SIZE, stdin);
		printf("\n");
		//������ SIZE��ŭ ����Ʈ stdin -> �����ġ
		if (strcmp(buf, "")) break;                  //�ԷµǸ� �ݺ��� Ż��
	}

}

//������ ���� ����� ã�Ƽ� ����, ������ ""
char *search_question(char *input, int teach) {
	FILE *fp;
	int output_num, random, check = 0, i;
	char *buf;
	char *similar;
	buf = allocate(SIZE);
	similar = allocate(SIZE);

	if ((fp = fopen("question.txt", "r")) == NULL) return "";   //������ ������ ����


	for (i = 0; i < 2; i++) {                     //�� 2�� ������ Ž�� i - 0.�Ϻ��� ��ġ�ϴ°�,  1.���� ��ġ�ϴ°�
		while (!feof(fp)) {                        //���� ������ Ž��
			fscanf(fp, "%d", &output_num);            //������ ���� ����� output_num�� ����
			nfgets(buf, SIZE, fp);                  //buf�� ���� ����

			if (i == 0 && !strcmp(input, buf)) check = 1;//������ �Ϻ��� ��ġ�ϴ°�

			if (i == 1 && strlen(buf) > 3 && strstr(input, buf) != NULL) { //if ������ ������ �ִ°�
				check = 1;
				if (teach == 0) printf("\n���ϴ� ����� �ƴҰ�� \"/t ����\" �� ���� ������ �ּ���.\n\n");
			}

			if (check == 1)                        //input�� ������ ��ġ�ų� ��� �ϸ�
			{
				random = rand() % output_num;         //������ ���� ����� ���� �������� ����
				next_line(fp, random);               //����� ������� �̵�
				nfgets(buf, SIZE, fp);               //����� buf�� ����
				fclose(fp);
				return buf;                        //������ ����� ����
			}
			next_line(fp, output_num + 1);            //���� ������ �ִ� ������ġ�� �̵�
		}
		if (teach == 1) break;
		rewind(fp);                              //����Ž�� ��ġ�� ó������ ����
	}

	fclose(fp);
	return "";
}


//����� ����Ʈ ����
void print_answer(char *output) {
	//textcolor(14);
	printf("���� LetpleBot  ����������������������������������������������������������������������\n");
	printf(" %s\n", output);
	printf("��������������������������������������������������������������������������������������\n\n");
	//textcolor(7);
}


//����� ���Ͽ� �Է��ϰ��� 
void teach_answer(char *input) {
	char buf[SIZE];
	int num, i;
	char tmp;
	FILE *fp;
	fp = fopen("question.txt", "a");

	//textcolor(12); 
	printf("����ĥ ����� ������ �Է��� �ּ���( 0 �Է½� ��ŵ )>>");
	//textcolor(7);
	scanf("%s", &buf);
	num = atoi(buf);
	clearBuffer();

	if (num == 0) {
		fclose(fp);
		return;
	}

	fprintf(fp, "%d%s\n", num, input);   //����� ������ ������ ����         3�ȳ�
	for (i = 0; i < num; i++) {         //����� ������ŭ for��            �ȳ�ȳ�
		input_data(buf, "TEACH");      //TEACH : ����� �Է¹���         �� �ȳ�
		fprintf(fp, "%s\n", buf);      //�Է¹��� ����� ���Ͽ� ����      �ݰ���
	}
	fprintf(fp, " \n");               //���� ó��
	fclose(fp);
}


//line��ŭ �����ٷ� �̵�
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
	fgets(buf, max, file);                        //���ٺҷ���
	buf[strlen(buf) - 1] = '\0';                  //���๮��(����)�� ��������
	return buf;                                 //���๮�� �����Ѱ� ����
}

//Log���� ����
void log_save(char* input, char* output, char* user_name) {
	FILE *fp;
	fp = fopen("log.txt", "a");
	fprintf(fp, "%s : %s \n���ú� : %s\n", user_name, input, output);
	fclose(fp);
}


//�� ���͸�
int filtering(char *input) {
	if (strstr(input, "�ù�") != NULL || strstr(input, "��") != NULL) {
		MessageBox(NULL, "���� �� ������� �������..", "���ú�", MB_OK | MB_ICONWARNING); {
		}
		return 1;
	}
	return 0;
}


void textcolor(int color_number) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}