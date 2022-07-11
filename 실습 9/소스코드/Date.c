#include "Date.h"

void printDate(Date date)					//��¥ ��� �Լ�
{
	printf("(%4d, %2d, %2d)", date.year, date.month, date.day);
}

int compareDate(Date d1, Date d2)			// ��¥ �� �Լ� (ũ�� 1, ������ -1, ������ 0)
{
	if (d1.year > d2.year)
		return 1;
	else if (d1.year < d2.year)
		return -1;

	// d1.year = d2.year �� ��
	else if (d1.month > d2.month)
		return 1;
	else if (d1.month < d2.month)
		return -1;

	// d1.month = d2.month �� ��
	else if (d1.day > d2.day)
		return 1;
	else if (d1.day < d2.day)
		return -1;

	// d1.day = d2.day �� ��
	else
		return 0;
}