#ifndef DATE_H
#define DATE_H
#pragma warning(disable: 4996)						// scanf���� �ȶ߰� �ϴ� pragma���� 

#include <stdio.h>

// ����ü Date �ڷ��� ���� (typedef�� �̿��� ����)
typedef struct Date{
	int year;
	int month;
	int day;
} Date;	

void printDate(Date date);							// ��¥ ��� �Լ�
int compareDate(Date d1, Date d2);					// ��¥ �� �Լ�

#endif // !DATA_H