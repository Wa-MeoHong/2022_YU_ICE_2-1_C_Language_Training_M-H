/*
  파일명 : "실습8_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 행렬의 가우스-조던 소거법, 역행렬으로 선형회로 시스템 해석하는 프로그램

  프로그램 작성자 : 신대홍(2022년 4월 22일)
  최종 Update : Version 2.0.1, 2022년 4월 27일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/04/22		v1.0.0		  최초작성
	신대홍		 2022/04/22		v1.1.0		  행렬 덧셈, 뺄셈, 곱셈까지 완성
	신대홍		 2022/04/23		v1.2.0	 	  가우스-조던 소거법 코드 완성
	신대홍		 2022/04/23		v2.0.0		  역행렬 코드 완성
	신대홍		 2022/04/27		v2.0.1		  역행렬 코드 수정
===========================================================================================================
*/

#include "Matrix.h"
#include "Mtrx_GJ.h"

#define OUTPUTFILE "OutputResult.txt"
#define MtrxInputDATA "MtrxInputData.txt"
#define Mtrx_nxn_DATA "Mtrx_nxn_Data.txt"
#define AugMtrx_ElecC_Data "AugMtrx_ElecCircuit_5x5.txt"
#define InvMtrx_ElecC_Data "InvMtrx_ElecCircuit_5x5.txt"

void Test_2D_DynArray_FileIO(FILE* fout);						// 행렬 A, B에 파일에서 읽어온 값을 넣어주고 출력
void Test_MtrxCal(FILE* fout);									// 행렬 A, B의 덧셈, 뺄셈 결과 행렬 출력
void Test_MtrxMultiple(FILE* fout);								// 행렬 A, B의 곱셈 결과 행렬 출력
void Test_GJ_LinearSys(FILE* fout);								// 주어진 선형회로식을 해석하여 결과를 출력(가우스-조던 소거법)
void Test_InvMtrx_LinearSys(FILE* fout);						// 주어진 선형회로식을 해석하여 결과를 출력(역행렬)

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
		// 메뉴 입력
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
		case 1:										// 행렬 A, B에 파일에서 읽어온 값을 넣어주고 출력
		{
			Test_2D_DynArray_FileIO(fout);
			break;
		}
		case 2:										// 행렬 A, B의 덧셈, 뺄셈 결과 행렬 출력
		{
			Test_MtrxCal(fout);
			break;
		}
		case 3:										// 행렬 A, B의 곱셈 결과 행렬 출력
		{
			Test_MtrxMultiple(fout);
			break;
		}
		case 4:										// 주어진 선형회로식을 해석하여 결과를 출력(가우스-조던 소거법)
		{
			Test_GJ_LinearSys(fout);
			break;
		}
		case 5:										// 주어진 선형회로식을 해석하여 결과를 출력(역행렬)
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

void Test_2D_DynArray_FileIO(FILE* fout)						// 행렬 A, B에 파일에서 읽어온 값을 넣어주고 출력
{
	FILE* fin;
	int a_row_SIZE, a_col_SIZE;
	int b_row_SIZE, b_col_SIZE;
	double** mA, ** mB;

	// 파일 오픈
	if ((fin = fopen(MtrxInputDATA, "r")) == NULL)
	{
		printf("Error! it doesn't opening MtrxInputData.txt file!!\n");
		exit(-1);
	}

	// 파일에서 행,열(포인터를 통해 읽은 값 반환) 읽어와서 출력
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Matrix A (%d * %d) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);						// 출력

	// 파일에서 행,열(포인터를 통해 읽은 값 반환) 읽어와서 출력
	mB = fGetMtrx(fin, &b_row_SIZE, &b_col_SIZE);
	printf("Input Matrix B (%d * %d) : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mB, b_row_SIZE, b_col_SIZE);						// 출력

	// 동적할당 해제
	DeleteDynMtrx(mA, a_row_SIZE);
	DeleteDynMtrx(mB, b_row_SIZE);
	fclose(fin);												//파일 닫기
}

void Test_MtrxCal(FILE* fout)									// 행렬 A, B의 덧셈, 뺄셈 결과 행렬 출력
{
	FILE* fin;
	double** mA, ** mB, ** mC, ** mD;
	int a_row_SIZE, a_col_SIZE;
	int b_row_SIZE, b_col_SIZE;
	int c_row_SIZE, c_col_SIZE;
	int d_row_SIZE, d_col_SIZE;

	// 파일 오픈
	if ((fin = fopen(Mtrx_nxn_DATA, "r")) == NULL)
	{
		printf("Error! it doesn't opening Mtrx_nxn_Data.txt file!!\n");
		exit(-1);
	} 

	// 배열을 동적할당 후, 값을 집어넣고 반환
	mA = fGetMtrx(fin, &a_row_SIZE, &a_col_SIZE);
	printf("Input Mtrx_A (%d * %d) : \n", a_row_SIZE, a_col_SIZE);
	PrintMtrx(mA, a_row_SIZE, a_col_SIZE);

	mB = fGetMtrx(fin, &b_row_SIZE, &b_col_SIZE);
	printf("Input Mtrx_B (%d * %d) : \n", b_row_SIZE, b_col_SIZE);
	PrintMtrx(mB, b_row_SIZE, b_col_SIZE);

	// Mtrx_C = Mtrx_A + Mtrx_B
	c_row_SIZE = a_row_SIZE;
	c_col_SIZE = b_col_SIZE;
	mC = AddMtrx(mA, mB, a_row_SIZE, a_col_SIZE);				// 행렬 덧셈
	printf("Mtrx_C (%d * %d) = Mtrx_A + Mtrx_B : \n", c_row_SIZE, c_col_SIZE);
	PrintMtrx(mC, c_row_SIZE, c_col_SIZE);

	// Mtrx_D = Mtrx_A - Mtrx_B
	d_row_SIZE = a_row_SIZE;
	d_col_SIZE = b_col_SIZE;
	mD = SubMtrx(mA, mB, a_row_SIZE, a_col_SIZE);				// 행렬 뺄셈
	printf("Mtrx_D (%d * %d) = Mtrx_A - Mtrx_B : \n", d_row_SIZE, d_col_SIZE);
	PrintMtrx(mD, d_row_SIZE, d_col_SIZE);

	// 할당 해제
	DeleteDynMtrx(mA, a_row_SIZE); 
	DeleteDynMtrx(mB, b_row_SIZE);
	DeleteDynMtrx(mC, c_row_SIZE);
	DeleteDynMtrx(mD, d_row_SIZE);
	fclose(fin);												// 파일 닫기
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

	// 배열을 동적할당 후, 값을 집어넣고 출력
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
	mC = MulMtrx(mA, mB, a_row_SIZE, SIZE_K, a_col_SIZE);		// 행렬 곱셈 함수
	printf("Mtrx_C (%d * %d) = Mtrx_A x Mtrx_B : \n", c_row_SIZE, c_col_SIZE);
	PrintMtrx(mC, c_row_SIZE, c_col_SIZE);

	//동적할당 해제
	DeleteDynMtrx(mA, a_row_SIZE);
	DeleteDynMtrx(mB, b_row_SIZE);
	DeleteDynMtrx(mC, c_row_SIZE);
	fclose(fin); //파일 닫기
}

void Test_GJ_LinearSys(FILE* fout)
{
	FILE* fin;
	int SIZE_N;
	double* solution = NULL;							// Solution (해의 배열)
	double** augMtrx = NULL;
	int solExist;										// 해답이 나왔는지 안나왔는지 확인하기 위한 변수 SolExist

	fin = fopen(AugMtrx_ElecC_Data, "r");
	if (fin == NULL)
	{
		printf("Error! it doesn't opening AugMtrx_ElecCircuit_5x5.txt file!!\n");
		exit(-1);
	}

	GetAugmentedMtrx(fin, &augMtrx, &SIZE_N);				// 동적 할당 후, 선형 방정식(배열)을 집어넣어주는 함수
	solution = (double*)calloc(SIZE_N, sizeof(double));
	printf("Augmented Matrix : \n");
	PrintMtrx(augMtrx, SIZE_N, SIZE_N + 1);
	fprintf(fout, "Augmented Matrix : \n");
	FPrintMtrx(fout, augMtrx, SIZE_N, SIZE_N + 1);			// 초기식 출력

	Diagnolize(fout, augMtrx, SIZE_N, &solExist);			// 선형방정식 풀이

	if (solExist)											// 해가 나왔음
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
	else													// 해가 안나옴 (혹은 해가 없음)
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
	double** mA, ** Inv_mA, ** res, ** mE;					// mE : V값
	int SIZE_N;
	double d;
	int solExist;											// 해답이 나왔는지 안나왔는지 확인하기 위한 변수 SolExist

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
	} // 동적할당 

	for (int i = 0; i < SIZE_N; i++)
		for (int j = 0; j < SIZE_N; j++)
		{
			if (fscanf(fin, "%lf", &d) != EOF)			// EOF가 될때 까지
				mA[i][j] = d;							// mA에 초기식(배열값)을 삽입해준다.
		}
	for (int i = 0; i < SIZE_N; i++)
	{
		if (fscanf(fin, "%lf", &d) != EOF)				// EOF가 될때 까지
			mE[i][0] = d;								// mE에 전압값(초기식의 결과값 배열값들)을 삽입
	}

	printf("Matrix A : \n");
	PrintMtrx(mA, SIZE_N, SIZE_N);
	fprintf(fout, "Matrix A : \n");
	FPrintMtrx(fout, mA, SIZE_N, SIZE_N);				// 초기식 출력

	InvMtrx(fout, mA, Inv_mA, SIZE_N, &solExist);		// 역행렬 계산

	if (solExist == 0)									// 역행렬 계산 불가능한 식이라면? 
	{
		fprintf(fout, "No Solutions! \n");
		printf("No Solutions! \n");

		// 동적할당 해제
		DeleteDynMtrx(mA, SIZE_N);
		DeleteDynMtrx(Inv_mA, SIZE_N);
		DeleteDynMtrx(mE, SIZE_N);
		DeleteDynMtrx(res, SIZE_N);						

		fclose(fin);
		return;											// 그대로 종료
	}

	printf("Inverse A : \n");
	PrintMtrx(Inv_mA, SIZE_N, SIZE_N);
	fprintf(fout, "Inverse A : \n");
	FPrintMtrx(fout, Inv_mA, SIZE_N, SIZE_N);			// 역행렬 출력

	printf("mE : \n");
	PrintMtrx(mE, SIZE_N, 1);
	fprintf(fout, "mE : \n");
	FPrintMtrx(fout, mE, SIZE_N, 1);					// mE(초기 선형식의 결과) 출력

	res = MulMtrx(Inv_mA, mE, SIZE_N, SIZE_N, 1);		// 역행렬과 mE를 곱한 값 = 최종 결과

	printf("Res = Inv_A * mE : \n");
	PrintMtrx(res, SIZE_N, 1);
	fprintf(fout, "Res = Inv_A * mE : \n");
	FPrintMtrx(fout, res, SIZE_N, 1);					// mE(초기 선형식의 결과) 출력

	fprintf(fout, "\n");

	// 동적할당 해제
	DeleteDynMtrx(mA, SIZE_N);
	DeleteDynMtrx(Inv_mA, SIZE_N);
	DeleteDynMtrx(mE, SIZE_N);
	DeleteDynMtrx(res, SIZE_N); 

	fclose(fin);
}