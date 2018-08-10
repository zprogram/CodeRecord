#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{

	int arr[] = { 8, 5, 3, 1, 4, 7, 9, 6, 0, 2 };
	//int len = _countof(arr);
	//�ڶ���д��
	int len = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < len - 1;i++)  //ÿ��ѡ�����ķ���������󣬹�ѡ��Ŵ�
	{
		for (int j = 0; j < len-1-i; j++) /*������ôѡ�����ģ�ͨ�������Ƚϣ��Ѵ�Ľ��������棬�Ѿ��źõ�Ԫ�ز�����*/
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}

		}
	}



	system("pause");
	return 0;
}