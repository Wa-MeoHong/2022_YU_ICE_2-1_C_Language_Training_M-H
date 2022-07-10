
/*
  ���ϸ� : "�ǽ�7_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- 2���� �迭 ���� �Ҵ� ��, ��� ���� �� ����ϴ� ���α׷�

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 4�� 9��)
  ���� Update : Version 1.0.1, 2022�� 4�� 9��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/04/09		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/04/10		v1.0.1		  �����Լ� �ϼ�

===========================================================================================================
*/

#include "Matrix.h"
#include "Mtrx_Cal.h"

#define MtrxDataFile "MtrxInputData.txt"
#define Mtrx3x5DF "Mtrx3x5InputData.txt"

void CheckAddress_2DimArray_for_Matrix();					// �迭 �ּ� Ȯ��
void Test_2D_DynamicArray_FileIO_Statistics();				// �ؽ�Ʈ���Ϸκ��� ����� �о�� ����� ����� ���
void Test_Matrix_Addition_Subtraction();					// ��� ����, ���� ���
void Test_Matrix_Multiplication();							// ��� �����

int main(void)
{
	int menu;

	while (1)
	{
		// �޴� ���� ( -1 �Է� �� ����)
		printf("----------Testing Matrix Operations with 2-Dimensional Dynamic Array------------\n");
		printf(" 1 : Check addresses of 2-Dim array for Matrix\n");
		printf(" 2 : Test 2-D Dynamic Array Creation ofr Matrix with File I/O, Statistics\n");
		printf(" 3 : Test Matrix Addition, Subtraction\n");
		printf(" 4 : Test Matrix Multiplication]\n");
		printf(" Input menu ( -1 to quit) : ");
		scanf("%d", &menu); 
		if (menu == -1)
			break;
		printf("\n");

		switch (menu)
		{
		case 1:
		{	CheckAddress_2DimArray_for_Matrix();			// �迭 �ּ� Ȯ��
		break; }
		case 2:
		{	Test_2D_DynamicArray_FileIO_Statistics();		// �ؽ�Ʈ���Ϸκ��� ����� �о�� ����� ����� ���
		break; }
		case 3:
		{	Test_Matrix_Addition_Subtraction();				// ��� ����, ���� ���
		break; }	
		case 4:
		{	Test_Matrix_Multiplication();					// ��� �����
		break; }
		default:
		{	break; }
		}
	}
	return 0;
}

void CheckAddress_2DimArray_for_Matrix() //�迭 �ּ� Ȯ��
{
	double m[3][3] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
	//�̸� ������ ���� ���

	printf("m\t = % 8p\n", m);								// �迭m�� �ּ� ���
	printf("m[0]\t = % 8p\n", m[0]);						// �迭m[0]�� �ּ� = �迭 m�� �ּҰ�
	printf("m[1]\t = % 8p\n", m[1]);						// �迭m[1]�� �ּ� = �迭 m+1 �ּҰ�
	printf("m[2]\t = % 8p\n", m[2]);						// �迭m[2]�� �ּ� = �迭 m+2 �ּҰ� 
	printf("&m[0][0] = % 8p\n", &m[0][0]);					// �迭m[0][0]�� �ּ� = �迭 m�� �ּҰ�
	printf("&m[1][0] = % 8p\n", &m[1][0]);					// �迭m[1][0]�� �ּ� = �迭 m+1 �ּҰ�
	printf("&m[2][0] = % 8p\n", &m[2][0]);					// �迭m[2][0]�� �ּ� = �迭 m+2 �ּҰ� 
	printf("\n");
}

void Test_2D_DynamicArray_FileIO_Statistics()				// �ؽ�Ʈ���Ϸκ��� ����� �о�� ����� ����� ���
{
	FILE* fin = NULL;
	int a_row_SIZE, a_col_SIZE;
	int b_row_SIZE, b_col_SIZE;
	double** mA, ** mB, ** mR;

	// ���� ����
	if ((fin = fopen(MtrxDataFile, "r")) == NULL)
	{
		printf("\tError in opening input.txt FILE !!\n\n");
		exit(-1);
	}

	// ��� A�� �����Ҵ� �� ��, ���� ���Ͽ��� �о�� ������ �� ���
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Mtrx_A ( %d * %d ) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);
	
	// ��� A�� ���� ���, ���� ���, ��ü ����� ����� �������� ���ٿ��� ���
	mR = getStaticsMtrx(mA, a_row_SIZE, a_col_SIZE);
	printf("Mtrx_A ( %d * %d ) with row & col averages : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mR, a_row_SIZE + 1, a_col_SIZE + 1);
	DeleteDoubleMatrix(mR, a_row_SIZE + 1);					// ������ mR�� �����Ҵ� �������ش�.
	
	// ��� B�� �����Ҵ� �� ��, ���� ���Ͽ��� �о�� ������ �� ���
	mB = fGetMtrx(fin, &b_row_SIZE, &b_col_SIZE);
	printf("Input Mtrx_B ( %d * %d ) : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mB, b_row_SIZE, b_col_SIZE);
	
	// ��� B�� ���� ���, ���� ���, ��ü����� ����� �������� ���ٿ��� ���
	mR = getStaticsMtrx(mB, b_row_SIZE, b_col_SIZE);
	printf("Mtrx_B ( %d * %d ) with row & col averages : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mR, b_row_SIZE + 1, b_col_SIZE + 1);	
	DeleteDoubleMatrix(mR, b_row_SIZE + 1);					// ������ mR�� �����Ҵ� �������ش�.
	
	// �پ� ��� A,B�� �����Ҵ� �������ش�.
	DeleteDoubleMatrix(mB, b_row_SIZE);
	DeleteDoubleMatrix(mA, a_row_SIZE);
	fclose(fin);											// ���� �ݱ�
}

void Test_Matrix_Addition_Subtraction()						// ��� ����, ���� ���
{
	FILE* fin;

	double** mA, ** mB, ** mC, ** mD;
	int a_row_SIZE, a_col_SIZE;
	int b_row_SIZE, b_col_SIZE;
	int c_row_SIZE, c_col_SIZE;
	int d_row_SIZE, d_col_SIZE;

	if ((fin = fopen(Mtrx3x5DF, "r")) == NULL)
	{
		printf("\tError in opening input.txt FILE !!\n\n");
		exit(-1);
	}

	// ��� A �����Ҵ� �� ��� ����
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Mtrx_A ( %d * %d ) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);
	
	// ��� B �����Ҵ� �� ��� ����
	mB = fGetMtrx(fin, &b_row_SIZE, &b_col_SIZE);
	printf("Input Mtrx_B ( %d * %d ) : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mB, b_row_SIZE, b_col_SIZE);
	
	// ���� �� �� �ϳ��� ���� �ʴٸ� ( ��� ����, ������ �ΰ��� ��,���� ���ƾ� ����)
	// �ϴ����� : ���ᰡ �Ǵ��� �ٽ� �ݺ����� �ؾ��ϱ� ����
	if ((a_row_SIZE != b_row_SIZE) || (a_col_SIZE != b_col_SIZE))
	{ 
		printf("\tError! row_SIZE and/or col_SIZE aren't equal!!\n ");
		fclose(fin);
		return;						
	}

	//mC = mA + mB;
	c_row_SIZE = a_row_SIZE;
	c_col_SIZE = b_col_SIZE;
	mC = AddMtrx(mA, mB, c_row_SIZE, c_col_SIZE);
	printf("Input Mtrx_C ( %d * %d ) : \n", c_row_SIZE, c_col_SIZE);
	PrintMtrx(mC, c_row_SIZE, c_col_SIZE);

	//mD = mA - mB;
	d_row_SIZE = a_row_SIZE;
	d_col_SIZE = b_col_SIZE;
	mD = SubMtrx(mA, mB, d_row_SIZE, d_col_SIZE);
	printf("Input Mtrx_D ( %d * %d ) : \n", d_row_SIZE, d_col_SIZE);
	PrintMtrx(mD, d_row_SIZE, d_col_SIZE);

	//�����Ҵ� ���� �� ���� �ݱ�
	DeleteDoubleMatrix(mA, a_row_SIZE);
	DeleteDoubleMatrix(mB, b_row_SIZE);
	DeleteDoubleMatrix(mC, c_row_SIZE);
	DeleteDoubleMatrix(mD, d_row_SIZE);
	fclose(fin);
}

void Test_Matrix_Multiplication()						// ��� �����
{
	FILE* fin;
	double** mA, ** mB, ** mC;
	int a_row_SIZE, a_col_SIZE;
	int b_row_SIZE, b_col_SIZE;
	int c_row_SIZE, c_col_SIZE;

	fin = fopen(MtrxDataFile, "r");
	if (fin == NULL)
	{
		printf("\tError in opening input.txt FILE !!\n\n");
		exit(-1);
	}

	// ��� A �����Ҵ� �� ��� ����
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Mtrx_A ( %d * %d ) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);

	// ��� B �����Ҵ� �� ��� ����
	mB = fGetMtrx(fin, &b_row_SIZE, &b_col_SIZE);
	printf("Input Mtrx_B ( %d * %d ) : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mB, b_row_SIZE, b_col_SIZE);

	//mC = mA * mB
	c_row_SIZE = a_row_SIZE;
	c_col_SIZE = b_col_SIZE;
	mC = MulMtrx(mA, mB, c_row_SIZE, b_row_SIZE, c_col_SIZE);
	printf("Input Mtrx_C ( %d * %d ) : \n", c_row_SIZE, c_col_SIZE);
	PrintMtrx(mC, c_row_SIZE, c_col_SIZE);

	DeleteDoubleMatrix(mA, a_row_SIZE);
	DeleteDoubleMatrix(mB, b_row_SIZE);
	DeleteDoubleMatrix(mC, c_row_SIZE);
	fclose(fin);
}