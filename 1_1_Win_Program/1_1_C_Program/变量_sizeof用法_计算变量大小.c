#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	char a = sizeof(char);

	double b = sizeof(double);

	int c = sizeof(int);

	printf(" %d \n %d \n %d \n", sizeof(a), sizeof(b), sizeof(c));
	system("pause");
	return 0;

}