#include<stdio.h>
int add(int, int);
int sub(int, int);
int mul(int, int);
int div(int, int);

int main()
{
	int a, b, sw;
	printf("두 수 입력\n");
	scanf("%d %d", &a, &b);
	printf("1 + 2 - 3 * 4 / 5 종료\n");
	scanf("%d", &sw);
	int(*ptr[4])(int, int);

	switch (sw)
	{
	case 1:
			ptr[0] = add;
			printf("%d\n", ptr[0](a, b));
			break; 
	case 2:
			ptr[1] = sub;
			printf("%d\n", ptr[1](a, b));
			break;
	case 3:
			ptr[2] = mul;
			printf("%d\n", ptr[2](a, b));
			break;
	case 4:
			ptr[3] = div;
			printf("%d\n", ptr[3](a, b));
			break;
	default:
			printf("종료\n");
			break;
	}	
	ptr[0] = add;
	ptr[1] = sub;
	ptr[2] = mul;
	ptr[3] = div;

	return 0;
}

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int mul(int a, int b)
{
	return a * b;
}

int div(int a, int b)
{
	return a / b;
}