#include "Matrix.h"

void CheckAddr_2D_Array(double** dM, int row_SIZE, int col_SIZE) // 2�����迭 �ּ� üũ �Լ�
{
	printf("m\t= %p\n", dM);								// ��ü �迭�� �ּ�(dM[0][0]�� �ּ�)

	for (int i = 0; i < row_SIZE; i++)
		printf("m[%d]\t= %p\n", i, dM + i);					// 2���� �迭�� �࿡���� �ּҰ� ���
	for (int j = 0; j < row_SIZE; j++)
		printf("m[%d][0]\t= %p\n", j, &dM[j][0]);			// 2���� �迭�� ��, ���� ���� �ּҰ�
}

void DeleteDoubleMatrix(double** dM, int row_SIZE)			// ���� �Ҵ� ���� �Լ� (2�����迭 ����)
{
	for (int i = 0; i < row_SIZE; i++)						// ���� �� �ึ�� �ߴ� �����Ҵ��� ����
	{
		free(dM[i]);
	}
	free(dM);												// �׸��� ���� ��ü ����
}

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

double** getStaticsMtrx(double** mA, int n_row_SIZE, int n_col_SIZE)	// ����� �� ��հ� ���� �Լ�
{
	double** mR;													// ���θ��� Ȯ��迭 mR
	double sum;														// �� ��,�� ���� �հ踦 ���� ���� 
	double sumALL = 0;												// 2�����迭 ��ü �μ��� �հ�

	mR = (double**)calloc(n_row_SIZE + 1, sizeof(double*));
	for (int i = 0; i < n_row_SIZE + 1; i++)
		mR[i] = (double*)calloc(n_col_SIZE + 1, sizeof(double));	// Ȯ��迭 mR����

	for (int i = 0; i < n_row_SIZE; i++)
	{
		for (int j = 0; j < n_col_SIZE; j++)
		{
			mR[i][j] = mA[i][j];									// mR�� mA�� ���� ����
			sumALL += mA[i][j];										// �ϸ鼭 ��ü�μ��հ赵 ���
		}
	}
	
	// ���� ���
	for (int k = 0; k < n_row_SIZE; k++)
	{
		sum = 0;
		for (int u = 0; u < n_col_SIZE; u++)
			sum += mR[k][u];										// �� ���� �հ�
		mR[k][n_col_SIZE] = sum / n_col_SIZE;						// ������ ����� ���� �������� ����
	}

	//���� ���
	for (int u = 0; u < n_col_SIZE; u++)
	{
		sum = 0;
		for (int k = 0; k < n_row_SIZE; k++)
			sum += mR[k][u];										// �� ���� �հ�
		mR[n_row_SIZE][u] = sum / n_row_SIZE;						// �ѿ��� ����� ���� �������� ����
	}

	// ��ü ���
	mR[n_row_SIZE][n_col_SIZE] = sumALL / ((double)n_row_SIZE * (double)n_col_SIZE);
	

	return mR;														// �迭 �ּҰ� ��ȯ 
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
