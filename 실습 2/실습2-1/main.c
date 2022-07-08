/*
  파일명 : "실습2-1_21912193_신대홍"

  프로그램의 목적 및 기본 기능:
	- 값을 16진수로 입력 받은 후, 입력받은 값을 10,8,2진수로 출력한 후, 그 값들을 비트연산, 사칙연산한 값을 2진수로 표현한다.

  프로그램 작성자 : 신대홍(2022년 3월 8일)
  최종 Update : Version 2.0.0, 2022년 3월 10일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
   신대홍		 2022/03/08		v1.0.0		  최초작성
   신대홍		 2022/03/10		v2.0.0		  코드 대폭수정 및 main축약
===========================================================================================================
*/

#include <stdio.h>

#define shift 0x3							//shift 상수

// 비트연산자 enum 열거형 자료
enum BITSUM { PLUS, MINUS, AND, OR, XOR, LSHIFT, RSHIFT, NOT };
// ↑비트연산자를 편하게 불러오기 위해 사용된 사용자지정변수,배열들
const char bit_wise[][3] = { "+","-","&","|","^","<<",">>","~" };
const char bitwiseName[][50] = { "PLUS", "MINUS", "AND", "OR", "XOR", "Shift Left", "Shift Right", "NOT" };


// ↓(순서대로)이진수 비트 출력 함수, 10진수, 8진수, 2진수 출력함수 , 비트연산 계산식 출력함수
void printInt_Bits(int x);							//2진수 비트 출력 함수
void printBitWise(int a, int b, int wise);			// 비트연산 출력함수(2진수 비트출력 함수 사용)
void printresult(int b, int wise, int result);		// 출력함수 1
void PR(int a, int b, int wise, int result);		// 출력함수 2

int main(void)
{
	int x, y;

	printf("input first hexadecimal number in (0x00000000 ~ 0xFFFFFFFF): 0x");
	scanf_s("%x", &x);
	printf(" x =  %#X = (in decimal) %d = (in octal) %o\n	= (in binary) ", x, x, x);
	printInt_Bits(x);

	printf("input second hexadecimal number in (0x00000000 ~ 0xFFFFFFFF): 0x");
	scanf_s("%x", &y);
	printf(" y =  %#X = (in decimal) %d = (in octal) %o\n	= (in binary) ", y, y, y);
	printInt_Bits(y);


	for (int i = 0; i < 8; i++)
		printBitWise(x, y, i); //비트연산 출력함수 

	return 0;
}

//======================================================================================
void printInt_Bits(int x)							//2진수 비트 출력 함수
{
	for (int i = 31; i >= 0; i--)
	{
		printf("%d", (x >> i) & 1);
		if (i % 8 == 0)
			printf(" ");
	}
	printf("\n");
}

void printBitWise(int a, int b, int wise)			//비트연산 출력함수  (2진수 비트출력 함수 사용)
{
	switch (wise)									// wise = enum으로 지정된 비트연산자를 불러오는 변수, 이값에따라 어떤 계산을 할지 결정함.
	{
	case PLUS:
	{PR(a, b, wise, a + b);
	break; }
	case MINUS:
	{PR(a, b, wise, a - b);
	break; }
	case AND:
	{PR(a, b, wise, a & b);
	break; }
	case OR:
	{PR(a, b, wise, a | b);
	break; }
	case XOR:
	{PR(a, b, wise, a ^ b);
	break; }
	case LSHIFT:
	{PR(a, shift, wise, a << shift);
	break; }
	case RSHIFT:
	{PR(b, shift, wise, b >> shift);
	break; }
	case NOT:
	{PR(a, b, wise, ~b);
	break; }
	}
}

void PR(int a, int b, int wise, int result)			// 출력함수 1
{
	if (wise == NOT)
	{
		printf("\nBitwise %s :	%s%#X => %#X\n", bitwiseName[wise], bit_wise[wise], b, result);
		printresult(b, wise, result);
	}
	else
	{
		printf("\nBitwise %s :	%#X %s %#X => %#X\n", bitwiseName[wise], a, bit_wise[wise], b, result);
		printf("	"); printInt_Bits(a);
		printresult(b, wise, result);
	}

}
void printresult(int b, int wise, int result)		// 출력 함수 2
{
	printf("%3s	", bit_wise[wise]);
	printInt_Bits(b);
	printf("  -----------------------------------------------------------\n");
	printf("	");
	printInt_Bits(result);							//결과값 출력
}