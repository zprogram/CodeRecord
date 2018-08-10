#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<math.h>

int main(void)

{

	/*  6�����ú��׹�ʽ�����������������߳�a��b��c�ɼ������롣����������߳����ܹ��������Σ������Ӧ��ʾ��Ϣ
	 *	���׹�ʽ������s=(a+b+c)/2
	 *  ���������: ��s*(s-a)*(s-b)*(s-c)
	 */
	
	double nNuma, nNumb, nNumc;
	double s , area;


	printf(" ���������ε����߳�����ʽ�硾a b c��\n ���硾2.0 3.0 4.0�� \n ");
	scanf_s("%lf%lf%lf", &nNuma, &nNumb,&nNumc);
	

	s = (nNuma + nNumb + nNumc) / 2.0;
	area = sqrt(s*(s - nNuma)*(s - nNumb)*(s - nNumc));

	printf(" a = %7.2f \t b = %7.2f c = %7.2f \n ",nNuma,nNumb,nNumc);
	printf(" area = %7.2f \n ",area);
    system("pause");
    return 0;

}