#include<stdio.h>
#include<Windows.h>
void func(char **ptr);

int main()
{
	char *ptr[4] = {"Seoul", "Jeju", "Gwangju", NULL};

	func(ptr);

	system("pause");
	return 0;
}

void func(char **ptr)
{
	while (*ptr)
	{
		printf("%s %p %c\n", *ptr, *ptr, **ptr);
		*ptr++;
	}
}