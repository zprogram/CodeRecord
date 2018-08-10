#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	int Numa, Numb;

	// ������
	// ����д����ʹ��putcharֻ�����һ���ַ������޷���������
    //     
	//numa = getchar();
	//fflush(stdin);
	//numb = getchar();
	//putchar(numa + numb);
	//putchar(numa - numb);
	//putchar(numa * numb);
	//putchar(numa / numb);

	// 
	//��ȷд��
	// 

	printf("��Ӽ���������������\n");
	scanf_s("%d", &Numa);
	getchar();
	scanf_s("%d", &Numb);
	printf("+���ͣ��Ľ��Ϊ%d \n", Numa + Numb);
	printf("-����Ľ��Ϊ%d \n", Numa - Numb);
	printf("*�������Ľ��Ϊ%d \n", Numa * Numb);
	printf("/���̣��Ľ��Ϊ%d \n", Numa / Numb);
    system("pause");
    return 0;

}