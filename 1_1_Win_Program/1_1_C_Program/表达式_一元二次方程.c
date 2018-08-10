#include<stdio.h>

#include<stdlib.h>
#include<stdio.h>

#include<stdlib.h>
#include<math.h>
#include<string.h>

int main(void)
{

	//����˼·��
	//	1��a=0�����Ƕ��η��̣�
	//	2��b*b-4 * b * c=0 ���������ʵ��
	//					>0������������ʵ��
	//					<0�������������

	double a, b, c, disc, x1, x2, realpart, imagpart;
	scanf_s("%lf %lf %lf", &a, &b, &c);
	printf("����ֵ");
	/*a�ľ���ֵС�ڵ���10�� - 6��, һ���ǵ���0*/
	if (fabs(a)<=0)
		printf("a<=0 ,����û��ʵ��\n");
	else
	{
		disc = b * b - 4 * a * c;
		if (fabs(disc) <= 0)
			printf("������ȵ�ʵ����%8.4f \n", -b / (2 * a));
		else
			if (disc > 0)
			{
				x1 = (-b + sqrt(disc) / (2 * a));
				x2 = (-b - sqrt(disc)) / (2 * a);
				printf("����������ʵ����%8.4f and %8.4f \n", x1, x2);
			}
			else{
				realpart = -b / (2 * a);
				imagpart = sqrt(disc) / (2 * a);
				printf("�������������\n");
				printf("%8.4f+%8.4f\n", realpart, imagpart);
				printf("%8.4f-%8.4f", realpart, imagpart);
			}
	}
    system("pause");
    return 0;

}