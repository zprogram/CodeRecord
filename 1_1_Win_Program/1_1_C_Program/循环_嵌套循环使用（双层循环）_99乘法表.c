#include<stdio.h>

#include<stdlib.h>

#include<string.h>




int main(void)

{

	for (int row = 1; row <= 9; row++){  //��ӡ0-8��һ���ŴΣ�
		for (int col = 1; col <= row; col++){  //����ÿһ����ô��ӡ
			printf("%d * %d = %2d   ", col,row,col*row);
		}
		printf("\n");
	}
    system("pause");
    return 0;

}