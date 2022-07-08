
/*
  ���ϸ� : "�ǽ�3-1_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- ��, ��, ���� �Է¹޾� ���� 1�� 1�� 1�Ϻ��� ��ĥ�� ���������� ���� ������ ����� ��,
	�Է��� ��, ���� �޷��� ����� ����Ѵ�

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 3�� 17��)
  ���� Update : Version 2.0.0, 2022�� 3�� 17��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
   �Ŵ�ȫ		 2022/03/17		v1.0.0		  �����ۼ�
   �Ŵ�ȫ		 2022/03/17		v2.0.0		  �Է¿����� ���ۼ� �ڵ� �߰�

===========================================================================================================
*/

#include <stdio.h>
#include <stdbool.h>									// bool �ڷ���, true, false �ҷ�����
#define weekdays 7										// 1������ 7��
#define MONTHS_YEAR 13									// 0���� �����ؼ� 12 + 1�� �ߴ�.

enum MONTH_NAME { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC }; //1 ~ 12
const char* weekday_NAME[weekdays] = { "SUN", "MON", "TUE", "WED", "TUR", "FRI", "SAT" };

bool isLeapYear(int year);								//���� �Ǵ��ϱ�
int getDaysFromJan01AD01(int year, int month, int day); //�ϼ� ���ϱ�
void PrintCalender(int year, int month);				// �޷����
bool checkrightdays(int year, int month, int day);		//�Է��� ���� ������ Ȯ��

int main(void)
{
	int year, month, day, days = 0;

	while (1)
	{
		//�Է�
		printf("��, ��, ���� ���ÿ�. : (0�� �Է½� �ߴ�)\n");
		scanf("%d %d %d", &year, &month, &day); 
		if (year == 0)									//0�� �Է½� ����
			break;
		else if (checkrightdays(year, month, day) == false)
		{
			printf("�ٽ� �Է��ϼ���.\n");
			continue;
		}
		days = getDaysFromJan01AD01(year, month, day);						//�ϼ� ���ϱ�
		printf("%4d��%2d��%2d��(%s)�� 1��1��1��(��)���� %d�ϸ�ŭ \
���� ���Դϴ�.\n", year, month, day, weekday_NAME[(days) % 7], days - 1);		//������ ���
		PrintCalender(year, month);											//�޷� ���
	}
	printf("\n����� �����մϴ�. \n");										
	return 0;
}

// ���� �Ǵ�
bool isLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;		//�����̸� TRUE(1) �ݳ�
	else
		return false;		//�ƴϸ� FALSE(0) �ݳ�
}

// �Է��� ���� ������ Ȯ��
bool checkrightdays(int year, int month, int day)
{
	int months[MONTHS_YEAR] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (year >= 1)											// 1�� �̻����� �°� �Է�������
	{
		if (isLeapYear(year))								// ����Ȯ��
			months[FEB] = 29;								// ���ޱ�ü
		if (month > 0 && month <= 12)						// ���� �°� �Է�
		{
			if (day <= months[month] && day > 0)			// �ϵ� �°� �Է��ϸ�
				return true;								// true(1)��ȯ
			else
				return false;								// �������� false(0)��ȯ
		}
		else
			return false;
	}
	else
		return false;
}

//�ϼ� ���ϱ�
int getDaysFromJan01AD01(int year, int month, int day)
{
	int DaysFromJan01AD01 = 0;
	int months[MONTHS_YEAR] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	for (int i = 1; i < year; i++)							//1�� �����̹Ƿ� 1���ͽ���,  �Է��� �⵵ ����
	{
		// ������ ��������?
		if (isLeapYear(i))									
		{
			DaysFromJan01AD01 += 366;						//���������� 1���� ���ؼ� 366�� �߰�
		} 
		else
		{
			DaysFromJan01AD01 += 365;						// ������ �ƴϸ� 365��
		}  
	}

	//�Է��� �⵵�� �����̶��
	if (isLeapYear(year)) 
	{
		months[FEB] = 29;
	} //2���� 29�Ϸ�..

	for (int j = 0; j < month; j++)
	{
		DaysFromJan01AD01 += months[j];
	}

	DaysFromJan01AD01 += day;
	months[FEB] = 28;										// �ٽ� �迭���� 2���� ���� 28�� �ʱ�ȭ ��Ű��
	return DaysFromJan01AD01;
}

// �޷����
void PrintCalender(int year, int month)
{
	int months[MONTHS_YEAR] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int days = 0;

	days = getDaysFromJan01AD01(year, month, 1);

	if (isLeapYear(year))								//�Է��� �⵵�� �����̶��
	{
		months[FEB] = 29;								//2���� 29�Ϸ�.
	}.

	printf(">>>>>>>>>>>>>%4d�� %2d��<<<<<<<<<<<<<\n", year, month); //�޷� ��,�� ���
	for (int i = 0; i < weekdays; i++)
	{
		printf("%5s", weekday_NAME[i]);					//���� ���
	} 
	printf("\n====================================\n");

	for (int j = 0; j < (days % 7); j++)				// 1���� �����ϴ� ���ϱ��� �������� ä���
	{
		printf("     ");
	}
	for (int d = 1; d <= months[month]; d++, days++)	// 1�Ϻ��� �� ���� ������������ ���
	{
		if (days % 7 == 0)
		{
			printf("\n");
		}												// �Ͽ����̸� ���� ���ͷ� �����ٷ�
		printf("%5d", d);								// �� ��� 
	}
	printf("\n====================================\n");
}