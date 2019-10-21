#include<stdio.h>
int main()
{
	int * ptr1;
	char *ptr3;

	ptr3 = (char*)malloc(80);
	if (ptr3 == NULL)
	{
		printf("¿¡·¯");
		exit(1);
	}
	gets(ptr3);
	printf("%p %s %c\n", ptr3, ptr3, *ptr3);
	ptr1 = &n;
	printf("%p\n", ptr1);
}