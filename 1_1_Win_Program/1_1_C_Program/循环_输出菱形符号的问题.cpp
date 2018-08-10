// ������η��ŵ�����.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "stdafx.h"
#include <windows.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;


int _tmain(int argc, _TCHAR* argv[])
{


	int row, col, col2;


			//         *
			//        ***
			//       *****
			//        ***
			//         *





	        /*                �ϰ벿��*/
			//         ����   �ո�   ����
			//         1      2      1                2*i-1                 
			//         2      1      3                2*i-1                 
			//         3      0      5                2*i-1                  




	       /*�ϰ벿��*/
			for (row = 1; row <= 3; row++)
			{

				for (col = 1; col <=3-row; col++)
				{
					cout << " ";
				}


				for (col2 = 1; col2 <= 2 * row - 1; col2++)
				{
					cout << "*";
				}
				cout << "" << endl;
			}



			//         *
			//        ***
			//       *****
			//        ***
			//         *

			/*                �°벿��*/
			//         ����   �ո�   ����
			//         1      1       3                   5-2*1  = 3
 			//         2      2       1                   5-2*2  = 1

			//�°벿��

			for (row = 1; row <= 2;row++)
			{
				for (col = 0; col < row;col++)
				{
					cout << " ";
				}
				for (col2 = 0; col2 < 5 - 2 * row;col2++)
				{
					cout << "*";

				}
				cout << "" << endl;
			}





	system("pause");
	
	return 0;
}
