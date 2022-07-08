
/*
  파일명 : "실습3-2_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- (5*5)행렬A, (5*5)행렬B의 덧셈, 뺄셈, 곱셈한 행렬인 C,D,E를 출력하는 프로그램

  프로그램 작성자 : 신대홍(2022년 3월 17일)
  최종 Update : Version 1.1.0, 2022년 3월 18일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/03/17		v1.0.0		  최초작성
	신대홍		 2022/03/18		v1.1.0		  소수점 둘째자리까지 출력되게 수정

===========================================================================================================
*/

#include <stdio.h>

#define Mtrx_SIZE 5
const unsigned char a6 = 0xa6, a5 = 0xa5, a4 = 0xa4, a3 = 0xa3, a2 = 0xa2, a1 = 0xa1;
//확장형 문자코드 : ( ─ : a6a1, │ : a6a2, ┌ : a6a3, ┐ : a6a4, ┘ : a6a5, └ : a6a6 )

void addMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size);		// 행렬 덧셈
void substractMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size);	// 행렬 뺄셈
void multiplyMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size);	// 행렬 곱셈
void printMtx(double A[][Mtrx_SIZE], int SIZE);							// 행렬 출력

int main(void)
{
	// 행렬 초기값 설정
	double A[][Mtrx_SIZE] = { {5.0, 4.0, 3.0, 2.0, 1.0},
		{6.0, 7.0, 8.0, 9.0, 10.0},{11.0,12.0,13.0,14.0,15.0},
		{16.0,17.0,18.0,19.0,20.0},{21.0,22.0,23.0,24.0,25.0} };
	double B[][Mtrx_SIZE] = { {1.0, 0.0, 0.0, 0.0, 0.0},{0.0, 1.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 1.0, 0.0, 0.0},{0.0, 0.0 ,0.0 ,1.0, 0.0},{0.0, 0.0, 0.0, 0.0, 1} };
	double C[][Mtrx_SIZE] = { {0.0},{0.0},{0.0},{0.0},{0.0} };
	double D[][Mtrx_SIZE] = { {0.0},{0.0},{0.0},{0.0},{0.0} };
	double E[][Mtrx_SIZE] = { {0.0},{0.0},{0.0},{0.0},{0.0} };
	
	// 행렬 연산
	addMtrx(A, B, C, Mtrx_SIZE);				// 행렬 더하기
	substractMtrx(A, B, D, Mtrx_SIZE);			// 행렬 빼기
	multiplyMtrx(A, B, E, Mtrx_SIZE);			// 행렬 곱셈

	// 출력
	printf("matrix A :\n"); 
	printMtx(A, Mtrx_SIZE);
	printf("matrix B :\n");
	printMtx(B, Mtrx_SIZE);
	printf("matrix C :\n");
	printMtx(C, Mtrx_SIZE);
	printf("matrix D :\n");
	printMtx(D, Mtrx_SIZE);
	printf("matrix E :\n");
	printMtx(E, Mtrx_SIZE);

	return 0;
}

//행렬 더하기
void addMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size)
{
	for (int i = 0; i < size; i++)				//행 전환
	{
		for (int j = 0; j < size; j++)			//열 전환
		{
			X[i][j] = A[i][j] + B[i][j];
		}
	}
} 

//행렬 빼기
void substractMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size)
{
	for (int i = 0; i < size; i++)				//행 전환
	{
		for (int j = 0; j < size; j++)			// 열전환
		{
			X[i][j] = A[i][j] - B[i][j];
		}
	}
} 

// 행렬 곱셈
void multiplyMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size)
{
	for (int i = 0; i < size; i++)				//행 전환
	{
		for (int j = 0; j < size; j++)			//열 전환
		{
			for (int k = 0; k < size; k++)		//인수들 덧셈하기
			{
				X[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// 행렬 출력
void printMtx(double A[][Mtrx_SIZE], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int k = 0; k < SIZE; k++)
		{
			// 대괄호 출력부분 ( 앞줄 [ )
			if (i == 0 && k == 0)
				printf("%c%c", a6, a3);							// ┌
			else if (i > 0 && i < SIZE - 1 && k == 0)
				printf("%c%c", a6, a2);							// │
			else if (i == SIZE - 1 && k == 0)
				printf("%c%c", a6, a6);							// └

			printf(" %5.2lf ", A[i][k]);						// 숫자 출력부분

			// 대괄호 출력부분 ( 뒷줄 ] )
			if (i == 0 && k == SIZE - 1)
				printf("%c%c", a6, a4);							// ┐
			else if (i > 0 && i < SIZE - 1 && k == SIZE - 1)
				printf("%c%c", a6, a2);							// │
			else if (i == SIZE - 1 && k == SIZE - 1)
				printf("%c%c", a6, a5);							// ┘
		}
		printf("\n");
	}
	printf("\n");
}