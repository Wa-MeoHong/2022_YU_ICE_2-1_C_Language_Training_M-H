
/*
  ���ϸ� : "�ǽ�2-2_21912193_�Ŵ�ȫ"

  ���α׷��� ���� �� �⺻ ���:
	- imit.h�� �̿��ؼ� �ڷ����� �ִ�,�ּҰ��� �ҷ��� ��, �� �����, +-1�� �� ������ ����Ͽ�
	�����÷ΰ� �Ͼ���� Ȯ�� �� ��, ����

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 3�� 9��)
  ���� Update : Version 1.0.0, 2022�� 3�� 9��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
   �Ŵ�ȫ		 2022/03/09		v1.0.0		  �����ۼ�

===========================================================================================================
*/


#include <limits.h>
#include <stdio.h>

int main(void)
{
	char char_max = CHAR_MAX, char_min = CHAR_MIN;
	short short_max = SHRT_MAX, short_min = SHRT_MIN;
	int int_max = INT_MAX, int_min = INT_MIN;

	printf("char_max = %d\n ", char_max);
	printf("char_min = %d\n ", char_min);
	printf("char_max (%d) + 1 = %d\n ", char_max, char_max + 1);
	printf("char_min (%d) - 1 = %d\n ", char_min, char_min - 1);

	printf("short_max = %d\n ", short_max);
	printf("short_min = %d\n ", short_min);
	printf("short_max (%d) + 1 = %d\n ", short_max, short_max + 1);
	printf("short_min (%d) - 1 = %d\n ", short_min, short_min - 1);

	printf("int_max = %d\n ", int_max);
	printf("int_min = %d\n ", int_min);
	printf("int_max (%d) + 1 = %d\n ", int_max, int_max + 1);
	printf("int_min (%d) - 1 = %d\n ", int_min, int_min - 1);
	return 0;
}