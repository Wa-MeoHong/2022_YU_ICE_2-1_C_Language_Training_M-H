/*
  ���ϸ� : "�ǽ�8_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- ����� ���콺-���� �ҰŹ�, ��������� ����ȸ�� �ý��� �ؼ��ϴ� ���α׷�

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 4�� 22��)
  ���� Update : Version 2.0.1, 2022�� 4�� 27��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/04/22		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/04/22		v1.1.0		  ��� ����, ����, �������� �ϼ�
	�Ŵ�ȫ		 2022/04/23		v1.2.0	 	  ���콺-���� �ҰŹ� �ڵ� �ϼ�
	�Ŵ�ȫ		 2022/04/23		v2.0.0		  ����� �ڵ� �ϼ�
	�Ŵ�ȫ		 2022/04/27		v2.0.1		  ����� �ڵ� ����
===========================================================================================================
*/

#include "Matrix.h"
#include "Mtrx_GJ.h"

#define OUTPUTFILE "OutputResult.txt"
#define MtrxInputDATA "MtrxInputData.txt"
#define Mtrx_nxn_DATA "Mtrx_nxn_Data.txt"
#define AugMtrx_ElecC_Data "AugMtrx_ElecCircuit_5x5.txt"
#define InvMtrx_ElecC_Data "InvMtrx_ElecCircuit_5x5.txt"

void Test_2D_DynArray_FileIO(FILE* fout);						// ��� A, B�� ���Ͽ��� �о�� ���� �־��ְ� ���
void Test_MtrxCal(FILE* fout);									// ��� A, B�� ����, ���� ��� ��� ���
void Test_MtrxMultiple(FILE* fout);								// ��� A, B�� ���� ��� ��� ���
void Test_GJ_LinearSys(FILE* fout);								// �־��� ����ȸ�ν��� �ؼ��Ͽ� ����� ���(���콺-���� �ҰŹ�)
void Test_InvMtrx_LinearSys(FILE* fout);						// �־��� ����ȸ�ν��� �ؼ��Ͽ� ����� ���(�����)

int main(void)
{
	FILE* fout;
	int menu;

	fout = fopen(OUTPUTFILE, "w");
	if (fout == NULL)
	{
		printf("Error! it doesn't opening OutputResult.txt file!!\n");
		exit(-1);
	}

	while (1)
	{
		// �޴� �Է�
		printf("Testing Matrix Operations with 2-Dimensional Dynamic Array\n");
		printf(" 1: Test 2-D Dynamic Array Creation for Matrix with File I/O\n");
		printf(" 2: Test Matrix Addition, Subtraction\n");
		printf(" 3: Test Matrix Multiplication\n");
		printf(" 4: Test Gauss-Jordan Elimination for Linear System\n");
		printf(" 5: Test Inverse Matrix with Gauss-Jordan Elimination for Linear System\n");
		printf(" 0: Quit\n");
		printf("Input menu (0 to quit) : ");
		scanf("%d", &menu);

		if (menu == 0)
			break;

		printf("\n");
		switch (menu)
		{
		case 1:										// ��� A, B�� ���Ͽ��� �о�� ���� �־��ְ� ���
		{
			Test_2D_DynArray_FileIO(fout);
			break;
		}
		case 2:										// ��� A, B�� ����, ���� ��� ��� ���
		{
			Test_MtrxCal(fout);
			break;
		}
		case 3:										// ��� A, B�� ���� ��� ��� ���
		{
			Test_MtrxMultiple(fout);
			break;
		}
		case 4:										// �־��� ����ȸ�ν��� �ؼ��Ͽ� ����� ���(���콺-���� �ҰŹ�)
		{
			Test_GJ_LinearSys(fout);
			break;
		}
		case 5:										// �־��� ����ȸ�ν��� �ؼ��Ͽ� ����� ���(�����)
		{
			Test_InvMtrx_LinearSys(fout);
			break;
		}
		default:
		{
			break;
		}
		}
	}
	fclose(fout);
}

void Test_2D_DynArray_FileIO(FILE* fout)						// ��� A, B�� ���Ͽ��� �о�� ���� �־��ְ� ���
{
	FILE* fin;
	int a_row_SIZE, a_col_SIZE;
	int b_row_SIZE, b_col_SIZE;
	double** mA, ** mB;

	// ���� ����
	if ((fin = fopen(MtrxInputDATA, "r")) == NULL)
	{
		printf("Error! it doesn't opening MtrxInputData.txt file!!\n");
		exit(-1);
	}

	// ���Ͽ��� ��,��(�����͸� ���� ���� �� ��ȯ) �о�ͼ� ���
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Matrix A (%d * %d) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);						// ���

	// ���Ͽ��� ��,��(�����͸� ���� ���� �� ��ȯ) �о�ͼ� ���
	mB = fGetMtrx(fin, &b_row_SIZE, &b_col_SIZE);
	printf("Input Matrix B (%d * %d) : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mB, b_row_SIZE, b_col_SIZE);						// ���

	// �����Ҵ� ����
	DeleteDynMtrx(mA, a_row_SIZE);
	DeleteDynMtrx(mB, b_row_SIZE);
	fclose(fin);												//���� �ݱ�
}

void Test_MtrxCal(FILE* fout)									// ��� A, B�� ����, ���� ��� ��� ���
{
	FILE* fin;
	double** mA, ** mB, ** mC, ** mD;
	int a_row_SIZE, a_col_SIZE;
	int b_row_SIZE, b_col_SIZE;
	int c_row_SIZE, c_col_SIZE;
	int d_row_SIZE, d_col_SIZE;

	// ���� ����
	if ((fin = fopen(Mtrx_nxn_DATA, "r")) == NULL)
	{
		printf("Error! it doesn't opening Mtrx_nxn_Data.txt file!!\n");
		exit(-1);
	} 

	// �迭�� �����Ҵ� ��, ���� ����ְ� ��ȯ
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Mtrx_A (%d * %d) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);

	mB = fGetMtrx(fin, &b_row_SIZE, &b_col_SIZE);
	printf("Input Mtrx_B (%d * %d) : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mB, b_row_SIZE, b_col_SIZE);

	// Mtrx_C = Mtrx_A + Mtrx_B
	c_row_SIZE = a_row_SIZE;
	c_col_SIZE = b_col_SIZE;
	mC = AddMtrx(mA, mB, a_row_SIZE, a_col_SIZE);				// ��� ����
	printf("Mtrx_C (%d * %d) = Mtrx_A + Mtrx_B : \n", c_row_SIZE, c_col_SIZE);
	PrintMtrx(mC, c_row_SIZE, c_col_SIZE);

	// Mtrx_D = Mtrx_A - Mtrx_B
	d_row_SIZE = a_row_SIZE;
	d_col_SIZE = b_col_SIZE;
	mD = SubMtrx(mA, mB, a_row_SIZE, a_col_SIZE);				// ��� ����
	printf("Mtrx_D (%d * %d) = Mtrx_A - Mtrx_B : \n", d_row_SIZE, d_col_SIZE);
	PrintMtrx(mD, d_row_SIZE, d_col_SIZE);

	// �Ҵ� ����
	DeleteDynMtrx(mA, a_row_SIZE); 
	DeleteDynMtrx(mB, b_row_SIZE);
	DeleteDynMtrx(mC, c_row_SIZE);
	DeleteDynMtrx(mD, d_row_SIZE);
	fclose(fin);												// ���� �ݱ�
}

void Test_MtrxMultiple(FILE* fout)
{
	FILE* fin;
	int a_row_SIZE, a_col_SIZE;
	int b_row_SIZE, b_col_SIZE;
	int c_row_SIZE, c_col_SIZE;
	int SIZE_K;
	double** mA, ** mB, ** mC;

	fin = fopen(MtrxInputDATA, "r");
	if (fin == NULL)
	{
		printf("Error! it doesn't opening MtrxInputData.txt file!!\n");
		exit(-1);
	}

	// �迭�� �����Ҵ� ��, ���� ����ְ� ���
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Matrix A (%d * %d) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);

	mB = fGetMtrx(fin, &b_row_SIZE, &b_col_SIZE);
	printf("Input Matrix B (%d * %d) : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mB, b_row_SIZE, b_col_SIZE);

	//Mtrx_C = Mtrx_A * Mtrx_B
	c_row_SIZE = a_row_SIZE;
	c_col_SIZE = b_col_SIZE;
	SIZE_K = a_col_SIZE;
	mC = MulMtrx(mA, mB, a_row_SIZE, SIZE_K, a_col_SIZE);		// ��� ���� �Լ�
	printf("Mtrx_C (%d * %d) = Mtrx_A x Mtrx_B : \n", c_row_SIZE, c_col_SIZE);
	PrintMtrx(mC, c_row_SIZE, c_col_SIZE);

	//�����Ҵ� ����
	DeleteDynMtrx(mA, a_row_SIZE);
	DeleteDynMtrx(mB, b_row_SIZE);
	DeleteDynMtrx(mC, c_row_SIZE);
	fclose(fin); //���� �ݱ�
}

void Test_GJ_LinearSys(FILE* fout)
{
	FILE* fin;
	int SIZE_N;
	double* solution = NULL;							// Solution (���� �迭)
	double** augMtrx = NULL;
	int solExist;										// �ش��� ���Դ��� �ȳ��Դ��� Ȯ���ϱ� ���� ���� SolExist

	fin = fopen(AugMtrx_ElecC_Data, "r");
	if (fin == NULL)
	{
		printf("Error! it doesn't opening AugMtrx_ElecCircuit_5x5.txt file!!\n");
		exit(-1);
	}

	GetAugmentedMtrx(fin, &augMtrx, &SIZE_N);				// ���� �Ҵ� ��, ���� ������(�迭)�� ����־��ִ� �Լ�
	solution = (double*)calloc(SIZE_N, sizeof(double));
	printf("Augmented Matrix : \n");
	PrintMtrx(augMtrx, SIZE_N, SIZE_N + 1);
	fprintf(fout, "Augmented Matrix : \n");
	FPrintMtrx(fout, augMtrx, SIZE_N, SIZE_N + 1);			// �ʱ�� ���

	Diagnolize(fout, augMtrx, SIZE_N, &solExist);			// ���������� Ǯ��

	if (solExist)											// �ذ� ������
	{
		fprintf(fout, "The Solution of given Linear System : \n");
		for (int i = 0; i < SIZE_N; i++)
		{
			solution[i] = augMtrx[i][SIZE_N];
			fprintf(fout, "x[%d] = %4.4lf\n", i, solution[i]);
			printf("x[%d] = % 4.4lf\n", i, solution[i]);
		}
		fprintf(fout, "\n");
		printf("\n");
	}
	else													// �ذ� �ȳ��� (Ȥ�� �ذ� ����)
	{
		fprintf(fout, "No Solutions! \n");
		printf("No Solutions! \n");
	}

	DeleteDynMtrx(augMtrx, SIZE_N);
	free(solution);
	fclose(fin);
}

void Test_InvMtrx_LinearSys(FILE* fout)
{
	FILE* fin;
	double** mA, ** Inv_mA, ** res, ** mE;					// mE : V��
	int SIZE_N;
	double d;
	int solExist;											// �ش��� ���Դ��� �ȳ��Դ��� Ȯ���ϱ� ���� ���� SolExist

	fin = fopen(InvMtrx_ElecC_Data, "r");
	if (fin == NULL)
	{
		printf("Error! it doesn't opening AugMtrx_ElecCircuit_5x5.txt file!!\n");
		exit(-1);
	}
	fscanf(fin, "%d", &SIZE_N);

	mA = (double**)calloc(SIZE_N, sizeof(double*));
	Inv_mA = (double**)calloc(SIZE_N, sizeof(double*));
	res = (double**)calloc(SIZE_N, sizeof(double*));
	mE = (double**)calloc(SIZE_N, sizeof(double*));
	for (int i = 0; i < SIZE_N; i++)
	{
		mA[i] = (double*)calloc(SIZE_N, sizeof(double));
		Inv_mA[i] = (double*)calloc(SIZE_N, sizeof(double));
		res[i] = (double*)calloc(SIZE_N, sizeof(double));
		mE[i] = (double*)calloc(SIZE_N, sizeof(double));
	} // �����Ҵ� 

	for (int i = 0; i < SIZE_N; i++)
		for (int j = 0; j < SIZE_N; j++)
		{
			if (fscanf(fin, "%lf", &d) != EOF)			// EOF�� �ɶ� ����
				mA[i][j] = d;							// mA�� �ʱ��(�迭��)�� �������ش�.
		}
	for (int i = 0; i < SIZE_N; i++)
	{
		if (fscanf(fin, "%lf", &d) != EOF)				// EOF�� �ɶ� ����
			mE[i][0] = d;								// mE�� ���а�(�ʱ���� ����� �迭����)�� ����
	}

	printf("Matrix A : \n");
	PrintMtrx(mA, SIZE_N, SIZE_N);
	fprintf(fout, "Matrix A : \n");
	FPrintMtrx(fout, mA, SIZE_N, SIZE_N);				// �ʱ�� ���

	InvMtrx(fout, mA, Inv_mA, SIZE_N, &solExist);		// ����� ���

	if (solExist == 0)									// ����� ��� �Ұ����� ���̶��? 
	{
		fprintf(fout, "No Solutions! \n");
		printf("No Solutions! \n");

		// �����Ҵ� ����
		DeleteDynMtrx(mA, SIZE_N);
		DeleteDynMtrx(Inv_mA, SIZE_N);
		DeleteDynMtrx(mE, SIZE_N);
		DeleteDynMtrx(res, SIZE_N);						

		fclose(fin);
		return;											// �״�� ����
	}

	printf("Inverse A : \n");
	PrintMtrx(Inv_mA, SIZE_N, SIZE_N);
	fprintf(fout, "Inverse A : \n");
	FPrintMtrx(fout, Inv_mA, SIZE_N, SIZE_N);			// ����� ���

	printf("mE : \n");
	PrintMtrx(mE, SIZE_N, 1);
	fprintf(fout, "mE : \n");
	FPrintMtrx(fout, mE, SIZE_N, 1);					// mE(�ʱ� �������� ���) ���

	res = MulMtrx(Inv_mA, mE, SIZE_N, SIZE_N, 1);		// ����İ� mE�� ���� �� = ���� ���

	printf("Res = Inv_A * mE : \n");
	PrintMtrx(res, SIZE_N, 1);
	fprintf(fout, "Res = Inv_A * mE : \n");
	FPrintMtrx(fout, res, SIZE_N, 1);					// mE(�ʱ� �������� ���) ���

	fprintf(fout, "\n");

	// �����Ҵ� ����
	DeleteDynMtrx(mA, SIZE_N);
	DeleteDynMtrx(Inv_mA, SIZE_N);
	DeleteDynMtrx(mE, SIZE_N);
	DeleteDynMtrx(res, SIZE_N); 

	fclose(fin);
}