#include "Matrix.h"

void CheckAddr_2D_Array(double** dM, int row_SIZE, int col_SIZE) // 2차원배열 주소 체크 함수
{
	printf("m\t= %p\n", dM);								// 전체 배열의 주소(dM[0][0]의 주소)

	for (int i = 0; i < row_SIZE; i++)
		printf("m[%d]\t= %p\n", i, dM + i);					// 2차원 배열중 행에따른 주소값 출력
	for (int j = 0; j < row_SIZE; j++)
		printf("m[%d][0]\t= %p\n", j, &dM[j][0]);			// 2차원 배열중 행, 열에 따른 주소값
}

void DeleteDoubleMatrix(double** dM, int row_SIZE)			// 동적 할당 해제 함수 (2차원배열 해제)
{
	for (int i = 0; i < row_SIZE; i++)						// 먼저 한 행마다 했던 동적할당을 해제
	{
		free(dM[i]);
	}
	free(dM);												// 그리고 이제 전체 해제
}

double** fGetMtrx(FILE* fin, int* row_SIZE, int* col_SIZE)	// 파일 입력 함수
{
	double d = 0.0;											// 파일에 있는 값을 담을 변수 d
	double** MtrxD;											// 파일에 있는 2차원 배열 담을 배열포인터 생성

	fscanf(fin, "%d %d", &(*row_SIZE), &(*col_SIZE));		// 파일로부터 행, 열 값을 읽어오기

	MtrxD = (double**)calloc(*row_SIZE, sizeof(double*));	// 2차원배열의 행수만큼 먼저 동적할당을 해준다.
	for (int i = 0; i < *row_SIZE; i++)
		MtrxD[i] = (double*)calloc(*col_SIZE, sizeof(double));
	// 이제 2차원배열의 한 행에 col_SIZE만큼 한번더 동적할당
	// 즉, 세로를 먼저 만들어주고, 세로 한칸에 대응하는 가로배열을 줄지어 만들어준다

	for (int m = 0; m < *row_SIZE; m++)
	{
		for (int n = 0; n < *col_SIZE; n++)
		{
			if (fscanf(fin, "%lf", &d) != EOF)				// EOF = -1, 1줄의 끝
				MtrxD[m][n] = d;							// 값 대입
		}
	}
	return MtrxD;											// 주소값 반환 (double**형의 값이 반환됨)
}

double** getStaticsMtrx(double** mA, int n_row_SIZE, int n_col_SIZE)	// 행렬의 각 평균값 산출 함수
{
	double** mR;													// 새로만들 확장배열 mR
	double sum;														// 한 행,한 열의 합계를 담을 변수 
	double sumALL = 0;												// 2차원배열 전체 인수의 합계

	mR = (double**)calloc(n_row_SIZE + 1, sizeof(double*));
	for (int i = 0; i < n_row_SIZE + 1; i++)
		mR[i] = (double*)calloc(n_col_SIZE + 1, sizeof(double));	// 확장배열 mR생성

	for (int i = 0; i < n_row_SIZE; i++)
	{
		for (int j = 0; j < n_col_SIZE; j++)
		{
			mR[i][j] = mA[i][j];									// mR에 mA의 값을 대입
			sumALL += mA[i][j];										// 하면서 전체인수합계도 계산
		}
	}
	
	// 행의 평균
	for (int k = 0; k < n_row_SIZE; k++)
	{
		sum = 0;
		for (int u = 0; u < n_col_SIZE; u++)
			sum += mR[k][u];										// 한 행의 합계
		mR[k][n_col_SIZE] = sum / n_col_SIZE;						// 한행의 평균을 행의 마지막에 대입
	}

	//열의 평균
	for (int u = 0; u < n_col_SIZE; u++)
	{
		sum = 0;
		for (int k = 0; k < n_row_SIZE; k++)
			sum += mR[k][u];										// 한 열의 합계
		mR[n_row_SIZE][u] = sum / n_row_SIZE;						// 한열의 평균을 열의 마지막에 대입
	}

	// 전체 평균
	mR[n_row_SIZE][n_col_SIZE] = sumALL / ((double)n_row_SIZE * (double)n_col_SIZE);
	

	return mR;														// 배열 주소값 반환 
}

void PrintMtrx(double** mA, int row_SIZE, int col_SIZE)		// 행렬 출력 함수
{
	const unsigned char a6 = 0xa6, a5 = 0xa5, a4 = 0xa4, a3 = 0xa3, a2 = 0xa2, a1 = 0xa1;
	//확장형 문자코드 : ( ─ : a6a1, │ : a6a2, ┌ : a6a3, ┐ : a6a4, ┘ : a6a5, └ : a6a6 )

	for (int i = 0; i < row_SIZE; i++)
	{
		for (int k = 0; k < col_SIZE; k++)
		{
			// 대괄호 출력부분 ( 앞줄 [ )
			if (i == 0 && k == 0)
				printf("%c%c", a6, a3);							// ┌
			else if (i > 0 && i < row_SIZE - 1 && k == 0)
				printf("%c%c", a6, a2);							// │
			else if (i == row_SIZE - 1 && k == 0)
				printf("%c%c", a6, a6);							// └

			printf(" %10.2lf ", mA[i][k]);						// 숫자 출력부분

			// 대괄호 출력부분 ( 뒷줄 ] )
			if (i == 0 && k == col_SIZE - 1)
				printf("%c%c", a6, a4);							// ┐
			else if (i > 0 && i < row_SIZE - 1 && k == col_SIZE - 1)
				printf("%c%c", a6, a2);							// │
			else if (i == row_SIZE - 1 && k == col_SIZE - 1)
				printf("%c%c", a6, a5);							// ┘
		}
		printf("\n");
	}
	printf("\n");
}

void FPrintMtrx(FILE* fout, double** mA, int row_SIZE, int col_SIZE)		// 행렬 출력 함수
{
	const unsigned char a6 = 0xa6, a5 = 0xa5, a4 = 0xa4, a3 = 0xa3, a2 = 0xa2, a1 = 0xa1;
	//확장형 문자코드 : ( ─ : a6a1, │ : a6a2, ┌ : a6a3, ┐ : a6a4, ┘ : a6a5, └ : a6a6 )

	for (int i = 0; i < row_SIZE; i++)
	{
		for (int k = 0; k < col_SIZE; k++)
		{
			// 대괄호 출력부분 ( 앞줄 [ )
			if (i == 0 && k == 0)
				fprintf(fout, "%c%c", a6, a3);							// ┌
			else if (i > 0 && i < row_SIZE - 1 && k == 0)
				fprintf(fout, "%c%c", a6, a2);							// │
			else if (i == row_SIZE - 1 && k == 0)
				fprintf(fout, "%c%c", a6, a6);							// └

			fprintf(fout, " %7.2lf ", mA[i][k]);						// 숫자 출력부분

			// 대괄호 출력부분 ( 뒷줄 ] )
			if (i == 0 && k == col_SIZE - 1)
				fprintf(fout, "%c%c", a6, a4);							// ┐
			else if (i > 0 && i < row_SIZE - 1 && k == col_SIZE - 1)
				fprintf(fout, "%c%c", a6, a2);							// │
			else if (i == row_SIZE - 1 && k == col_SIZE - 1)
				fprintf(fout, "%c%c", a6, a5);							// ┘
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
}
