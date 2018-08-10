#include "stdafx.h"
#include "stdlib.h"

int main()
{
	int array1[3][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	int i, j;
	int len = sizeof(array1) / sizeof(array1[0]);
	int len1 = sizeof(array1) / sizeof(array1[0][0]);


	printf(" %d \n ",len);
	printf(" %d \n ", len1);
	for (i=0;i<=2;i++) //��
	{
		for (j = 0; j <=3; j++)  //��
		{
			printf(" array[%d][%d]=%d \n ",i,j,array1[i][j]);
		}
		printf(" \n " );
	}



	system("pause");

	return 0;
}