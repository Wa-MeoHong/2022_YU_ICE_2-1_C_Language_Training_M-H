#include "Mtrx_Cal.h"	

double** AddMtrx(double** mA, double** mB, int row_SIZE, int col_SIZE) // 행렬 덧셈
{
	double** mR = NULL;

	// 배열 동적할당 
	mR = (double**)calloc(row_SIZE, sizeof(double*));
	for (int i = 0; i < row_SIZE; i++)
		mR[i] = (double*)calloc(col_SIZE, sizeof(double));

	for (int i = 0; i < row_SIZE; i++)						// 행 전환
	{
		for (int j = 0; j < col_SIZE; j++)					// 열 전환
		{
			mR[i][j] = mA[i][j] + mB[i][j];					// 덧셈
		}
	}

	return mR;												// 주소 반환
}

double** SubMtrx(double** mA, double** mB, int row_SIZE, int col_SIZE) // 행렬 뺄셈
{
	double** mR = NULL;

	//배열 동적할당 
	mR = (double**)calloc(row_SIZE, sizeof(double*));
	for (int i = 0; i < row_SIZE; i++)
		mR[i] = (double*)calloc(col_SIZE, sizeof(double));

	for (int i = 0; i < row_SIZE; i++)						// 행 전환
	{
		for (int j = 0; j < col_SIZE; j++)					// 열 전환
		{
			mR[i][j] = mA[i][j] - mB[i][j];					// 뺄셈
		}
	}

	return mR;												// 주소 반환
}

double** MulMtrx(double** mA, double** mB, int row_SIZE, int SIZE_k, int col_SIZE) // 행렬 곱셈 
{
	double** mR = NULL;

	//배열 동적할당 
	mR = (double**)calloc(row_SIZE, sizeof(double*));
	for (int i = 0; i < row_SIZE; i++)
		mR[i] = (double*)calloc(col_SIZE, sizeof(double));

	for (int i = 0; i < row_SIZE; i++)						// 행 전환
	{
		for (int j = 0; j < col_SIZE; j++)					// 열 전환
		{
			for (int k = 0; k < SIZE_k; k++)				// 인수를 곱한것들 덧셈하기
			{
				mR[i][j] += mA[i][k] * mB[k][j];
			}
		}
	}
	return mR;												// 주소 반환
}