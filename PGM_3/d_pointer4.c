#include<stdio.h>
#include<windows.h>
int main(int argc, char *argv[])
{
	int cnt = 0;
	char *ptr = argv[1];

	printf("argcÀÇ °¹¼ö: %d\n", argc);

	/*for (int i = 0; i < argc; i++)
	{
		printf("%d %p %s %c\n", i + 1, *argv, *argv, **argv);
		argv++;
	}*/

	while (*ptr)
	{
		if (*ptr == *argv[2])
			cnt++;
		ptr++;
	}

	printf("%d", cnt);

	system("pause");
	return 0;
}