
/*
  ���ϸ� : "�ǽ�3-2_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- (5*5)���A, (5*5)���B�� ����, ����, ������ ����� C,D,E�� ����ϴ� ���α׷�

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 3�� 17��)
  ���� Update : Version 1.1.0, 2022�� 3�� 18��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/03/17		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/03/18		v1.1.0		  �Ҽ��� ��°�ڸ����� ��µǰ� ����

===========================================================================================================
*/

#include <stdio.h>

#define Mtrx_SIZE 5
const unsigned char a6 = 0xa6, a5 = 0xa5, a4 = 0xa4, a3 = 0xa3, a2 = 0xa2, a1 = 0xa1;
//Ȯ���� �����ڵ� : ( �� : a6a1, �� : a6a2, �� : a6a3, �� : a6a4, �� : a6a5, �� : a6a6 )

void addMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size);		// ��� ����
void substractMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size);	// ��� ����
void multiplyMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size);	// ��� ����
void printMtx(double A[][Mtrx_SIZE], int SIZE);							// ��� ���

int main(void)
{
	// ��� �ʱⰪ ����
	double A[][Mtrx_SIZE] = { {5.0, 4.0, 3.0, 2.0, 1.0},
		{6.0, 7.0, 8.0, 9.0, 10.0},{11.0,12.0,13.0,14.0,15.0},
		{16.0,17.0,18.0,19.0,20.0},{21.0,22.0,23.0,24.0,25.0} };
	double B[][Mtrx_SIZE] = { {1.0, 0.0, 0.0, 0.0, 0.0},{0.0, 1.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 1.0, 0.0, 0.0},{0.0, 0.0 ,0.0 ,1.0, 0.0},{0.0, 0.0, 0.0, 0.0, 1} };
	double C[][Mtrx_SIZE] = { {0.0},{0.0},{0.0},{0.0},{0.0} };
	double D[][Mtrx_SIZE] = { {0.0},{0.0},{0.0},{0.0},{0.0} };
	double E[][Mtrx_SIZE] = { {0.0},{0.0},{0.0},{0.0},{0.0} };
	
	// ��� ����
	addMtrx(A, B, C, Mtrx_SIZE);				// ��� ���ϱ�
	substractMtrx(A, B, D, Mtrx_SIZE);			// ��� ����
	multiplyMtrx(A, B, E, Mtrx_SIZE);			// ��� ����

	// ���
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

//��� ���ϱ�
void addMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size)
{
	for (int i = 0; i < size; i++)				//�� ��ȯ
	{
		for (int j = 0; j < size; j++)			//�� ��ȯ
		{
			X[i][j] = A[i][j] + B[i][j];
		}
	}
} 

//��� ����
void substractMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size)
{
	for (int i = 0; i < size; i++)				//�� ��ȯ
	{
		for (int j = 0; j < size; j++)			// ����ȯ
		{
			X[i][j] = A[i][j] - B[i][j];
		}
	}
} 

// ��� ����
void multiplyMtrx(double A[][Mtrx_SIZE], double B[][Mtrx_SIZE], double X[][Mtrx_SIZE], int size)
{
	for (int i = 0; i < size; i++)				//�� ��ȯ
	{
		for (int j = 0; j < size; j++)			//�� ��ȯ
		{
			for (int k = 0; k < size; k++)		//�μ��� �����ϱ�
			{
				X[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// ��� ���
void printMtx(double A[][Mtrx_SIZE], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int k = 0; k < SIZE; k++)
		{
			// ���ȣ ��ºκ� ( ���� [ )
			if (i == 0 && k == 0)
				printf("%c%c", a6, a3);							// ��
			else if (i > 0 && i < SIZE - 1 && k == 0)
				printf("%c%c", a6, a2);							// ��
			else if (i == SIZE - 1 && k == 0)
				printf("%c%c", a6, a6);							// ��

			printf(" %5.2lf ", A[i][k]);						// ���� ��ºκ�

			// ���ȣ ��ºκ� ( ���� ] )
			if (i == 0 && k == SIZE - 1)
				printf("%c%c", a6, a4);							// ��
			else if (i > 0 && i < SIZE - 1 && k == SIZE - 1)
				printf("%c%c", a6, a2);							// ��
			else if (i == SIZE - 1 && k == SIZE - 1)
				printf("%c%c", a6, a5);							// ��
		}
		printf("\n");
	}
	printf("\n");
}