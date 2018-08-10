// 04_01_��ά������ϰ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include  <string.h>


int _tmain(int argc, _TCHAR* argv[])
{
	int Row, Col;
	char arrayA[40][40] = {0};


	for (Row = 0; Row < 40;Row++)
	{
		for (Col = 0; Col < 40; Col++)
		{
			    arrayA[0][Col] = 1;
				arrayA[Row][0] = 1;
				arrayA[Row][39] = 1;
				arrayA[39][Col] = 1;

				if ((arrayA[Row][Col]!=0))
				{
					printf("%c%c", 0xa8, 0x80); 
			
				} else{
					printf("%d ", arrayA[Row][Col]);
					
				}
		}
		printf("\n");
	}



	//for (Row = 0; Row < 40; Row++)
	//{
	//	for (Col = 0; Col < 40; Col++)
	//	{
	//		if (arrayA[Row][Col] == 1)
	//		{
	//			printf("%c%c", 0xa8, 0x80);
	//			arrayA[Row + 1][Col + 1];

	//		}
	//		printf("%d",arrayA[Row][Col]);
	//	}
	//	printf("\n");
	//}


	



	system("pause");

	return 0;
}
