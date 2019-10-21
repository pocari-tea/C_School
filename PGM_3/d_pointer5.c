#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int i;
	double d;

	i = atoi(argv[1]);
	d = atof(argv[2]);

	printf("%d+%f = %.2f\n", i, d, i + d);
	printf("%d-%f = %.2f\n", i, d, i - d);
	printf("%d*%f = %.2f\n", i, d, i * d);
	printf("%d/%f = %.2f\n", i, d, i / d);

	system("pause");

	return 0;
}