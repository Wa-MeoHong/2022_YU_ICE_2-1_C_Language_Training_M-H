#include "Matrix.h"

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

void DeleteDynMtrx(double** dM, int row_SIZE)			// 동적 할당 해제 함수 (2차원배열 해제)
{
	for (int i = 0; i < row_SIZE; i++)						// 먼저 한 행마다 했던 동적할당을 해제
	{
		free(dM[i]);
	}
	free(dM);												// 그리고 이제 전체 해제
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