#ifndef DATE_H
#define DATE_H
#pragma warning(disable: 4996)						// scanf오류 안뜨게 하는 pragma정의 

#include <stdio.h>

// 구조체 Date 자료형 설정 (typedef를 이용해 설정)
typedef struct Date{
	int year;
	int month;
	int day;
} Date;	

void printDate(Date date);							// 날짜 출력 함수
int compareDate(Date d1, Date d2);					// 날짜 비교 함수

#endif // !DATA_H