
/*
  파일명 : "실습3-1_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 년, 월, 일을 입력받아 서기 1년 1월 1일부터 며칠이 지났는지와 현재 요일을 출력한 후,
	입력한 년, 달의 달력을 만들어 출력한다

  프로그램 작성자 : 신대홍(2022년 3월 17일)
  최종 Update : Version 2.0.0, 2022년 3월 17일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
   신대홍		 2022/03/17		v1.0.0		  최초작성
   신대홍		 2022/03/17		v2.0.0		  입력오류시 재작성 코드 추가

===========================================================================================================
*/

#include <stdio.h>
#include <stdbool.h>									// bool 자료형, true, false 불러오기
#define weekdays 7										// 1주일은 7일
#define MONTHS_YEAR 13									// 0부터 시작해서 12 + 1을 했다.

enum MONTH_NAME { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC }; //1 ~ 12
const char* weekday_NAME[weekdays] = { "SUN", "MON", "TUE", "WED", "TUR", "FRI", "SAT" };

bool isLeapYear(int year);								//윤년 판단하기
int getDaysFromJan01AD01(int year, int month, int day); //일수 구하기
void PrintCalender(int year, int month);				// 달력출력
bool checkrightdays(int year, int month, int day);		//입력한 값이 옳은지 확인

int main(void)
{
	int year, month, day, days = 0;

	while (1)
	{
		//입력
		printf("년, 월, 일을 쓰시오. : (0년 입력시 중단)\n");
		scanf("%d %d %d", &year, &month, &day); 
		if (year == 0)									//0년 입력시 종료
			break;
		else if (checkrightdays(year, month, day) == false)
		{
			printf("다시 입력하세요.\n");
			continue;
		}
		days = getDaysFromJan01AD01(year, month, day);						//일수 구하기
		printf("%4d년%2d월%2d일(%s)는 1년1월1일(월)에서 %d일만큼 \
지난 날입니다.\n", year, month, day, weekday_NAME[(days) % 7], days - 1);		//지난날 출력
		PrintCalender(year, month);											//달력 출력
	}
	printf("\n출력을 종료합니다. \n");										
	return 0;
}

// 윤년 판단
bool isLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;		//윤년이면 TRUE(1) 반납
	else
		return false;		//아니면 FALSE(0) 반납
}

// 입력한 값이 옳은지 확인
bool checkrightdays(int year, int month, int day)
{
	int months[MONTHS_YEAR] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (year >= 1)											// 1년 이상으로 맞게 입력했으면
	{
		if (isLeapYear(year))								// 윤년확인
			months[FEB] = 29;								// 윤달교체
		if (month > 0 && month <= 12)						// 월도 맞게 입력
		{
			if (day <= months[month] && day > 0)			// 일도 맞게 입력하면
				return true;								// true(1)반환
			else
				return false;								// 나머지는 false(0)반환
		}
		else
			return false;
	}
	else
		return false;
}

//일수 구하기
int getDaysFromJan01AD01(int year, int month, int day)
{
	int DaysFromJan01AD01 = 0;
	int months[MONTHS_YEAR] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	for (int i = 1; i < year; i++)							//1년 부터이므로 1부터시작,  입력한 년도 까지
	{
		// 윤년을 지나갔나?
		if (isLeapYear(i))									
		{
			DaysFromJan01AD01 += 366;						//지나갔으면 1일을 더해서 366일 추가
		} 
		else
		{
			DaysFromJan01AD01 += 365;						// 윤년이 아니면 365일
		}  
	}

	//입력한 년도가 윤년이라면
	if (isLeapYear(year)) 
	{
		months[FEB] = 29;
	} //2월을 29일로..

	for (int j = 0; j < month; j++)
	{
		DaysFromJan01AD01 += months[j];
	}

	DaysFromJan01AD01 += day;
	months[FEB] = 28;										// 다시 배열안의 2월의 값을 28로 초기화 시키기
	return DaysFromJan01AD01;
}

// 달력출력
void PrintCalender(int year, int month)
{
	int months[MONTHS_YEAR] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int days = 0;

	days = getDaysFromJan01AD01(year, month, 1);

	if (isLeapYear(year))								//입력한 년도가 윤년이라면
	{
		months[FEB] = 29;								//2월을 29일로.
	}.

	printf(">>>>>>>>>>>>>%4d년 %2d월<<<<<<<<<<<<<\n", year, month); //달력 년,월 출력
	for (int i = 0; i < weekdays; i++)
	{
		printf("%5s", weekday_NAME[i]);					//요일 출력
	} 
	printf("\n====================================\n");

	for (int j = 0; j < (days % 7); j++)				// 1일이 시작하는 요일까지 공백으로 채우기
	{
		printf("     ");
	}
	for (int d = 1; d <= months[month]; d++, days++)	// 1일부터 그 월의 마지막날까지 출력
	{
		if (days % 7 == 0)
		{
			printf("\n");
		}												// 일요일이면 한줄 엔터로 다음줄로
		printf("%5d", d);								// 일 출력 
	}
	printf("\n====================================\n");
}