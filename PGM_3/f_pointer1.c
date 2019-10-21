#include<stdio.h>
void hello(char * ptr);

int main()
{
	//printf("%p\n", hello);
	void(*fp)(char *);
	printf("%d\n", sizeof(fp));
	fp = hello;
	fp("abc"); // = hello("abc")

	return 0;
}

void hello(char *ptr)
{
	printf("hello\n");
}