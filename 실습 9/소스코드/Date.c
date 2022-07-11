#include "Date.h"

void printDate(Date date)					//날짜 출력 함수
{
	printf("(%4d, %2d, %2d)", date.year, date.month, date.day);
}

int compareDate(Date d1, Date d2)			// 날짜 비교 함수 (크면 1, 작으면 -1, 같으면 0)
{
	if (d1.year > d2.year)
		return 1;
	else if (d1.year < d2.year)
		return -1;

	// d1.year = d2.year 일 때
	else if (d1.month > d2.month)
		return 1;
	else if (d1.month < d2.month)
		return -1;

	// d1.month = d2.month 일 때
	else if (d1.day > d2.day)
		return 1;
	else if (d1.day < d2.day)
		return -1;

	// d1.day = d2.day 일 때
	else
		return 0;
}