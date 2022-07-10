#include "Matrix.h"

double** fGetMtrx(FILE* fin, int* row_SIZE, int* col_SIZE)	// ���� �Է� �Լ�
{
	double d = 0.0;											// ���Ͽ� �ִ� ���� ���� ���� d
	double** MtrxD;											// ���Ͽ� �ִ� 2���� �迭 ���� �迭������ ����

	fscanf(fin, "%d %d", &(*row_SIZE), &(*col_SIZE));		// ���Ϸκ��� ��, �� ���� �о����

	MtrxD = (double**)calloc(*row_SIZE, sizeof(double*));	// 2�����迭�� �����ŭ ���� �����Ҵ��� ���ش�.
	for (int i = 0; i < *row_SIZE; i++)
		MtrxD[i] = (double*)calloc(*col_SIZE, sizeof(double));
	// ���� 2�����迭�� �� �࿡ col_SIZE��ŭ �ѹ��� �����Ҵ�
	// ��, ���θ� ���� ������ְ�, ���� ��ĭ�� �����ϴ� ���ι迭�� ������ ������ش�

	for (int m = 0; m < *row_SIZE; m++)
	{
		for (int n = 0; n < *col_SIZE; n++)
		{
			if (fscanf(fin, "%lf", &d) != EOF)				// EOF = -1, 1���� ��
				MtrxD[m][n] = d;							// �� ����
		}
	}
	return MtrxD;											// �ּҰ� ��ȯ (double**���� ���� ��ȯ��)
}

void DeleteDynMtrx(double** dM, int row_SIZE)			// ���� �Ҵ� ���� �Լ� (2�����迭 ����)
{
	for (int i = 0; i < row_SIZE; i++)						// ���� �� �ึ�� �ߴ� �����Ҵ��� ����
	{
		free(dM[i]);
	}
	free(dM);												// �׸��� ���� ��ü ����
}

void PrintMtrx(double** mA, int row_SIZE, int col_SIZE)		// ��� ��� �Լ�
{
	const unsigned char a6 = 0xa6, a5 = 0xa5, a4 = 0xa4, a3 = 0xa3, a2 = 0xa2, a1 = 0xa1;
	//Ȯ���� �����ڵ� : ( �� : a6a1, �� : a6a2, �� : a6a3, �� : a6a4, �� : a6a5, �� : a6a6 )

	for (int i = 0; i < row_SIZE; i++)
	{
		for (int k = 0; k < col_SIZE; k++)
		{
			// ���ȣ ��ºκ� ( ���� [ )
			if (i == 0 && k == 0)
				printf("%c%c", a6, a3);							// ��
			else if (i > 0 && i < row_SIZE - 1 && k == 0)
				printf("%c%c", a6, a2);							// ��
			else if (i == row_SIZE - 1 && k == 0)
				printf("%c%c", a6, a6);							// ��

			printf(" %10.2lf ", mA[i][k]);						// ���� ��ºκ�

			// ���ȣ ��ºκ� ( ���� ] )
			if (i == 0 && k == col_SIZE - 1)
				printf("%c%c", a6, a4);							// ��
			else if (i > 0 && i < row_SIZE - 1 && k == col_SIZE - 1)
				printf("%c%c", a6, a2);							// ��
			else if (i == row_SIZE - 1 && k == col_SIZE - 1)
				printf("%c%c", a6, a5);							// ��
		}
		printf("\n");
	}
	printf("\n");
}

void FPrintMtrx(FILE* fout, double** mA, int row_SIZE, int col_SIZE)		// ��� ��� �Լ�
{
	const unsigned char a6 = 0xa6, a5 = 0xa5, a4 = 0xa4, a3 = 0xa3, a2 = 0xa2, a1 = 0xa1;
	//Ȯ���� �����ڵ� : ( �� : a6a1, �� : a6a2, �� : a6a3, �� : a6a4, �� : a6a5, �� : a6a6 )

	for (int i = 0; i < row_SIZE; i++)
	{
		for (int k = 0; k < col_SIZE; k++)
		{
			// ���ȣ ��ºκ� ( ���� [ )
			if (i == 0 && k == 0)
				fprintf(fout, "%c%c", a6, a3);							// ��
			else if (i > 0 && i < row_SIZE - 1 && k == 0)
				fprintf(fout, "%c%c", a6, a2);							// ��
			else if (i == row_SIZE - 1 && k == 0)
				fprintf(fout, "%c%c", a6, a6);							// ��

			fprintf(fout, " %7.2lf ", mA[i][k]);						// ���� ��ºκ�

			// ���ȣ ��ºκ� ( ���� ] )
			if (i == 0 && k == col_SIZE - 1)
				fprintf(fout, "%c%c", a6, a4);							// ��
			else if (i > 0 && i < row_SIZE - 1 && k == col_SIZE - 1)
				fprintf(fout, "%c%c", a6, a2);							// ��
			else if (i == row_SIZE - 1 && k == col_SIZE - 1)
				fprintf(fout, "%c%c", a6, a5);							// ��
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
}

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