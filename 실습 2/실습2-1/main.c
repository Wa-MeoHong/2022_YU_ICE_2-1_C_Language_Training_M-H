/*
  ���ϸ� : "�ǽ�2-1_21912193_�Ŵ�ȫ"

  ���α׷��� ���� �� �⺻ ���:
	- ���� 16������ �Է� ���� ��, �Է¹��� ���� 10,8,2������ ����� ��, �� ������ ��Ʈ����, ��Ģ������ ���� 2������ ǥ���Ѵ�.

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 3�� 8��)
  ���� Update : Version 2.0.0, 2022�� 3�� 10��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
   �Ŵ�ȫ		 2022/03/08		v1.0.0		  �����ۼ�
   �Ŵ�ȫ		 2022/03/10		v2.0.0		  �ڵ� �������� �� main���
===========================================================================================================
*/

#include <stdio.h>

#define shift 0x3							//shift ���

// ��Ʈ������ enum ������ �ڷ�
enum BITSUM { PLUS, MINUS, AND, OR, XOR, LSHIFT, RSHIFT, NOT };
// ���Ʈ�����ڸ� ���ϰ� �ҷ����� ���� ���� �������������,�迭��
const char bit_wise[][3] = { "+","-","&","|","^","<<",">>","~" };
const char bitwiseName[][50] = { "PLUS", "MINUS", "AND", "OR", "XOR", "Shift Left", "Shift Right", "NOT" };


// ��(�������)������ ��Ʈ ��� �Լ�, 10����, 8����, 2���� ����Լ� , ��Ʈ���� ���� ����Լ�
void printInt_Bits(int x);							//2���� ��Ʈ ��� �Լ�
void printBitWise(int a, int b, int wise);			// ��Ʈ���� ����Լ�(2���� ��Ʈ��� �Լ� ���)
void printresult(int b, int wise, int result);		// ����Լ� 1
void PR(int a, int b, int wise, int result);		// ����Լ� 2

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
		printBitWise(x, y, i); //��Ʈ���� ����Լ� 

	return 0;
}

//======================================================================================
void printInt_Bits(int x)							//2���� ��Ʈ ��� �Լ�
{
	for (int i = 31; i >= 0; i--)
	{
		printf("%d", (x >> i) & 1);
		if (i % 8 == 0)
			printf(" ");
	}
	printf("\n");
}

void printBitWise(int a, int b, int wise)			//��Ʈ���� ����Լ�  (2���� ��Ʈ��� �Լ� ���)
{
	switch (wise)									// wise = enum���� ������ ��Ʈ�����ڸ� �ҷ����� ����, �̰������� � ����� ���� ������.
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

void PR(int a, int b, int wise, int result)			// ����Լ� 1
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
void printresult(int b, int wise, int result)		// ��� �Լ� 2
{
	printf("%3s	", bit_wise[wise]);
	printInt_Bits(b);
	printf("  -----------------------------------------------------------\n");
	printf("	");
	printInt_Bits(result);							//����� ���
}