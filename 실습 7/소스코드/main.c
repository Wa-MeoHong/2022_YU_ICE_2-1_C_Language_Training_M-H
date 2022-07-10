
/*
  파일명 : "실습7_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 2차원 배열 동적 할당 후, 행렬 연산 후 출력하는 프로그램

  프로그램 작성자 : 신대홍(2022년 4월 9일)
  최종 Update : Version 1.0.1, 2022년 4월 9일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/04/09		v1.0.0		  최초작성
	신대홍		 2022/04/10		v1.0.1		  메인함수 완성

===========================================================================================================
*/

#include "Matrix.h"
#include "Mtrx_Cal.h"

#define MtrxDataFile "MtrxInputData.txt"
#define Mtrx3x5DF "Mtrx3x5InputData.txt"

void CheckAddress_2DimArray_for_Matrix();					// 배열 주소 확인
void Test_2D_DynamicArray_FileIO_Statistics();				// 텍스트파일로부터 행렬을 읽어와 행렬의 평균을 계산
void Test_Matrix_Addition_Subtraction();					// 행렬 덧셈, 뺄셈 출력
void Test_Matrix_Multiplication();							// 행렬 곱출력

int main(void)
{
	int menu;

	while (1)
	{
		// 메뉴 선택 ( -1 입력 시 종료)
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
		{	CheckAddress_2DimArray_for_Matrix();			// 배열 주소 확인
		break; }
		case 2:
		{	Test_2D_DynamicArray_FileIO_Statistics();		// 텍스트파일로부터 행렬을 읽어와 행렬의 평균을 계산
		break; }
		case 3:
		{	Test_Matrix_Addition_Subtraction();				// 행렬 덧셈, 뺄셈 출력
		break; }	
		case 4:
		{	Test_Matrix_Multiplication();					// 행렬 곱출력
		break; }
		default:
		{	break; }
		}
	}
	return 0;
}

void CheckAddress_2DimArray_for_Matrix() //배열 주소 확인
{
	double m[3][3] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
	//미리 만들어둔 샘플 행렬

	printf("m\t = % 8p\n", m);								// 배열m의 주소 출력
	printf("m[0]\t = % 8p\n", m[0]);						// 배열m[0]의 주소 = 배열 m의 주소값
	printf("m[1]\t = % 8p\n", m[1]);						// 배열m[1]의 주소 = 배열 m+1 주소값
	printf("m[2]\t = % 8p\n", m[2]);						// 배열m[2]의 주소 = 배열 m+2 주소값 
	printf("&m[0][0] = % 8p\n", &m[0][0]);					// 배열m[0][0]의 주소 = 배열 m의 주소값
	printf("&m[1][0] = % 8p\n", &m[1][0]);					// 배열m[1][0]의 주소 = 배열 m+1 주소값
	printf("&m[2][0] = % 8p\n", &m[2][0]);					// 배열m[2][0]의 주소 = 배열 m+2 주소값 
	printf("\n");
}

void Test_2D_DynamicArray_FileIO_Statistics()				// 텍스트파일로부터 행렬을 읽어와 행렬의 평균을 계산
{
	FILE* fin = NULL;
	int a_row_SIZE, a_col_SIZE;
	int b_row_SIZE, b_col_SIZE;
	double** mA, ** mB, ** mR;

	// 파일 열기
	if ((fin = fopen(MtrxDataFile, "r")) == NULL)
	{
		printf("\tError in opening input.txt FILE !!\n\n");
		exit(-1);
	}

	// 행렬 A를 동적할당 한 후, 값을 파일에서 읽어와 매핑한 후 출력
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Mtrx_A ( %d * %d ) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);
	
	// 행렬 A의 행의 평균, 열의 평균, 전체 평균을 계산해 마지막에 덧붙여서 출력
	mR = getStaticsMtrx(mA, a_row_SIZE, a_col_SIZE);
	printf("Mtrx_A ( %d * %d ) with row & col averages : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mR, a_row_SIZE + 1, a_col_SIZE + 1);
	DeleteDoubleMatrix(mR, a_row_SIZE + 1);					// 끝나면 mR을 동적할당 해제해준다.
	
	// 행렬 B를 동적할당 한 후, 값을 파일에서 읽어와 매핑한 후 출력
	mB = fGetMtrx(fin, &b_row_SIZE, &b_col_SIZE);
	printf("Input Mtrx_B ( %d * %d ) : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mB, b_row_SIZE, b_col_SIZE);
	
	// 행렬 B의 행의 평균, 열의 평균, 전체평균을 계산해 마지막에 덧붙여서 출력
	mR = getStaticsMtrx(mB, b_row_SIZE, b_col_SIZE);
	printf("Mtrx_B ( %d * %d ) with row & col averages : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mR, b_row_SIZE + 1, b_col_SIZE + 1);	
	DeleteDoubleMatrix(mR, b_row_SIZE + 1);					// 끝나면 mR을 동적할당 해제해준다.
	
	// 다쓴 행렬 A,B를 동적할당 해제해준다.
	DeleteDoubleMatrix(mB, b_row_SIZE);
	DeleteDoubleMatrix(mA, a_row_SIZE);
	fclose(fin);											// 파일 닫기
}

void Test_Matrix_Addition_Subtraction()						// 행렬 덧셈, 뺄셈 출력
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

	// 행렬 A 동적할당 및 행렬 생성
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Mtrx_A ( %d * %d ) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);
	
	// 행렬 B 동적할당 및 행렬 생성
	mB = fGetMtrx(fin, &b_row_SIZE, &b_col_SIZE);
	printf("Input Mtrx_B ( %d * %d ) : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mB, b_row_SIZE, b_col_SIZE);
	
	// 만약 둘 중 하나라도 같지 않다면 ( 행렬 덧셈, 뺄셈은 두개의 행,열이 같아야 성립)
	// 하는이유 : 종료가 되더라도 다시 반복문을 해야하기 때문
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

	//동적할당 해제 및 파일 닫기
	DeleteDoubleMatrix(mA, a_row_SIZE);
	DeleteDoubleMatrix(mB, b_row_SIZE);
	DeleteDoubleMatrix(mC, c_row_SIZE);
	DeleteDoubleMatrix(mD, d_row_SIZE);
	fclose(fin);
}

void Test_Matrix_Multiplication()						// 행렬 곱출력
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

	// 행렬 A 동적할당 및 행렬 생성
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Mtrx_A ( %d * %d ) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);

	// 행렬 B 동적할당 및 행렬 생성
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