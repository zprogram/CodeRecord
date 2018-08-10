#include <stdio.h>
#include <stdlib.h>
#include <strsafe.h>


int main(void)     //�����������
{

	printf("  * \n");
	printf(" *** \n");
	printf(" **** \n");
	printf("****** \n");

	char *s = "color ";
	char *t = "title ";
	char buffer[20];
	char title[20];
	for (int i = 0; i < 100; i++)
	{
		memset(buffer, sizeof(char) * 20, 0);
		memset(title, sizeof(char) * 20, 0);
		sprintf_s(buffer, sizeof(char) * 20, "%s %d", s, i);
		sprintf_s(title, sizeof(char) * 20, "%s %d",t, i);
		system(title);
		system(buffer);
	}


	system("pause");
    return 0;

}