#include "Mtrx_Cal.h"	

double** AddMtrx(double** mA, double** mB, int row_SIZE, int col_SIZE) // ��� ����
{
	double** mR = NULL;

	// �迭 �����Ҵ� 
	mR = (double**)calloc(row_SIZE, sizeof(double*));
	for (int i = 0; i < row_SIZE; i++)
		mR[i] = (double*)calloc(col_SIZE, sizeof(double));

	for (int i = 0; i < row_SIZE; i++)						// �� ��ȯ
	{
		for (int j = 0; j < col_SIZE; j++)					// �� ��ȯ
		{
			mR[i][j] = mA[i][j] + mB[i][j];					// ����
		}
	}

	return mR;												// �ּ� ��ȯ
}

double** SubMtrx(double** mA, double** mB, int row_SIZE, int col_SIZE) // ��� ����
{
	double** mR = NULL;

	//�迭 �����Ҵ� 
	mR = (double**)calloc(row_SIZE, sizeof(double*));
	for (int i = 0; i < row_SIZE; i++)
		mR[i] = (double*)calloc(col_SIZE, sizeof(double));

	for (int i = 0; i < row_SIZE; i++)						// �� ��ȯ
	{
		for (int j = 0; j < col_SIZE; j++)					// �� ��ȯ
		{
			mR[i][j] = mA[i][j] - mB[i][j];					// ����
		}
	}

	return mR;												// �ּ� ��ȯ
}

double** MulMtrx(double** mA, double** mB, int row_SIZE, int SIZE_k, int col_SIZE) // ��� ���� 
{
	double** mR = NULL;

	//�迭 �����Ҵ� 
	mR = (double**)calloc(row_SIZE, sizeof(double*));
	for (int i = 0; i < row_SIZE; i++)
		mR[i] = (double*)calloc(col_SIZE, sizeof(double));

	for (int i = 0; i < row_SIZE; i++)						// �� ��ȯ
	{
		for (int j = 0; j < col_SIZE; j++)					// �� ��ȯ
		{
			for (int k = 0; k < SIZE_k; k++)				// �μ��� ���Ѱ͵� �����ϱ�
			{
				mR[i][j] += mA[i][k] * mB[k][j];
			}
		}
	}
	return mR;												// �ּ� ��ȯ
}