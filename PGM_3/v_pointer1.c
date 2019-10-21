#include<stdio.h>
int main()
{
	int n = 10;
	void *ptr = &n;

	printf("%d\n", *(int *)ptr);
	char c = 'A';
	ptr = &c;

	printf("%c\n", *(char *)ptr);
	
	int a[3] = { 10, 20, 30 };
	ptr = a;
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", *((int *)ptr + i));
	}

	char s[] = { "programe" };
	ptr = s;
	for (int i = 0; i < sizeof(s); i++)
	{
		printf("%c", *((char *)ptr + i));
	}

	return 0;
}