#include "Mtrx_GJ.h"


void GetAugmentedMtrx(FILE* fin, double** Mtrx, int* SIZE_N)				// 파일 입력 함수
{
	double d = 0.0;															// 파일에 있는 값을 담을 변수 d
	double** MtrxD;

	fscanf(fin, "%d", &(*SIZE_N));											// 파일로부터 행, 열 값을 읽어오기

	// 읽어온 사이즈만큼 동적할당 
	MtrxD = (double**)calloc(*SIZE_N, sizeof(double*));
	for (int i = 0; i < *SIZE_N; i++)
		MtrxD[i] = (double*)calloc((*SIZE_N) + 1, sizeof(double));
	
	// 값 대입 
	for (int m = 0; m < *SIZE_N; m++)
	{
		for (int n = 0; n < (*SIZE_N) + 1; n++)
		{
			if (fscanf(fin, "%lf", &d) != EOF)								// EOF가 될때 까지
				MtrxD[m][n] = d;											// 값 대입
		}
	}

	*Mtrx = MtrxD;															// 주소 반환 
}

void pivoting(double** augMtrx, int SIZE_N, int p, int* piv_FOUND) // 행 바꿔주는 함수 pivoting
{
	double max = 0;
	double temp = 0;
	int max_row = p;

	//먼저 가장 큰 행을 찾는다( 그 열에서)
	max = fabs(augMtrx[p][p]); //기준 행, 열 절댓값 (1번째행,열 값, 2번째행, 열값, 3번째행,열 값)
	// abs() = int형의 절댓값 반환, fabs() = double 형의 절댓값 반환

	for (int i = 0; i < SIZE_N; i++)
	{
		if (max < fabs(augMtrx[i][p]))
		{
			max_row = i;
			max = fabs(augMtrx[i][p]);
		}
	}

	if (max < Epsilon)									// 만약 max == 0이라면 
		*piv_FOUND = 0;									// 해를 구할 수 없는 상태라고 하고, solExist를 0으로 만들어줌
	else
	{
		*piv_FOUND = 1;									// 아니면 solExist를 1로 만든 후, 
		if (max_row != p)								// 만약 절댓값이 가장 큰 행번호가 자기 자신이 아닌 경우에 작동
		{
			// 왜 p행, p열부터 하는가는 이미 그 전의 열은 이전의 정리에 의해 모두 정리가 완료되었기 때문이다.
			// 즉, 2행을 정리할 시점에선 1열은 모두 1, 0, 0, 0, 0,... 으로 정리되어 바꿀 필요가 없다.
			for (int k = p; k <= SIZE_N; k++)
			{
				temp = augMtrx[p][k];
				augMtrx[p][k] = augMtrx[max_row][k];
				augMtrx[max_row][k] = temp;
			}
		}
	}
}

void Diagnolize(FILE* fout, double** augMtrx, int SIZE_N, int* solExist) // 가우스-조던 소거법 계산 함수
{
	double pivDivide;
	double anotherDiv;

	for (int p = 0; (p < SIZE_N) && (*solExist); p++)
	{
		pivoting(augMtrx, SIZE_N, p, solExist);

		if (*solExist)
		{
			if (augMtrx[p][p] != 1.00)									// p,p의 값이 1이 아닌경우 (1이면 이 과정을 따로 안거침)
			{
				pivDivide = augMtrx[p][p];
				augMtrx[p][p] = 1.00;
				for (int k = p + 1; k <= SIZE_N; k++)
					augMtrx[p][k] /= pivDivide;							// p,p의 값이 1이 되도록 행의 모든 값을 p,p의 값에 나눔
			}
		}
		else
			break;
		// 여기까지 pivoting 후, p행,p열의 값을 1로 만들어 주면서 그 행의 값들을 전부 나눠준다.

//-----------------------------------------------------------------------------------

	// 여기서부턴 그 정리된 행을 가지고 다른 행을 빼주면서 p열의 나머지 값을 0으로 만들어줌

		for (int j = 0; j < SIZE_N; j++)
		{
			if ((j != p) && (augMtrx[j][p] != 0.0))
				// p행을 제외한 나머지 행, 또한, j행의 p열의 값이 0(정리가 끝난상태)가 아닌 경우라면 진행
			{
				anotherDiv = augMtrx[j][p];
				augMtrx[j][p] = 0;
				for (int k = p + 1; k <= SIZE_N; k++)
					augMtrx[j][k] = augMtrx[j][k] - (anotherDiv * augMtrx[p][k]);
			}
		}
	}
}

void InvMtrx(FILE* fout, double** mA, double** Inv_mA, int SIZE_N, int* solexist) //역행렬 계산 함수
{
	// 진행방식은 위의 가우스-조던 소거법과 비슷하게 흘러가나, 오른쪽열의 결과값이 단위행렬이 되는것일 뿐이다.
	// 즉, 배열을 두개 합쳐서 가우스-조던 소거법처럼 계산하면 오른쪽의 단위행렬이 역행렬이 되어 나온다.

	double** AugMtrx;										// 역행렬을 구하기위해 원본+첨가행렬을 넣을 배열
	double pivDivide;										// p행, p열의 값을 1로 나누기위한 값. 이 값을 이용해 p행을 전부 나누어준다.
	double anotherDiv;										// p행의 값을 이용하여 다른 행의 값들을 0으로 만들때, 다른행의 값을 맞추어주기위해 사용

	AugMtrx = (double**)calloc(SIZE_N, sizeof(double*));
	for (int i = 0; i < SIZE_N; i++)
		AugMtrx[i] = (double*)calloc(SIZE_N * 2, sizeof(double));

	for (int i = 0; i < SIZE_N; i++)
		for (int j = 0; j < SIZE_N; j++)					// AugMtrx의 왼쪽 부분에 원래 행렬 대입
			AugMtrx[i][j] = mA[i][j];

	for (int i = 0; i < SIZE_N; i++)
		for (int j = SIZE_N; j < SIZE_N * 2; j++)
			AugMtrx[i][j] = (i == j - SIZE_N) ? 1.0 : 0.0;	// AugMtrx의 오른쪽 부분, 행과 열번호가 같다면 1, 아니면 0 대입
 
	//--------------------------------------------------------------------------------------------------
	//  역행렬 계산 시작
	for (int p = 0; p < SIZE_N; p++)
	{
		double max = fabs(AugMtrx[p][p]);
		//기준 행, 열 절댓값 (1번째행,열 값, 2번째행, 열값, 3번째행,열 값)
		// abs() = int형의 절댓값 반환, fabs() = double 형의 절댓값 반환

		for (int i = 0; i < SIZE_N; i++)
		{
			if (max < fabs(AugMtrx[i][p]))
				max = fabs(AugMtrx[i][p]); // 행 p열의 각 행들에 대해 p열에서의 최대값을 갱신
		}

		if (max < Epsilon)									// 만약 max == 0이라면 
			*solexist = 0;									// 해를 구할 수 없는 상태라고 하고, solExist를 0으로 만들어줌
		else
			*solexist = 1;									// 아니면 solExist를 1로 만든 후, 
//=================================해가 유무 판별 과정===================================

		if (*solexist == 0)									// 역행렬을 구할수 없기 때문에 종료
			break;

		if (AugMtrx[p][p] != 1.00)							// p,p의 값이 1이 아닌경우 (1이면 이 과정을 따로 안거침)
		{
			pivDivide = AugMtrx[p][p];
			AugMtrx[p][p] = 1.00;
			for (int k = p + 1; k < SIZE_N * 2; k++)		// 역행렬 때문에 배열이 오른쪽으로 SIZE_N의 두배가 됨...
				AugMtrx[p][k] /= pivDivide;					// p,p의 값이 1이 되도록 행의 모든 값을 p,p의 값에 나눔
		}

		for (int j = 0; j < SIZE_N; j++)
		{
			if ((j != p) && (AugMtrx[j][p] != 0.0))
				// p행을 제외한 나머지 행, 또한, j행의 p열의 값이 0(정리가 끝난상태)가 아닌 경우라면 진행
			{
				anotherDiv = AugMtrx[j][p];
				AugMtrx[j][p] = 0;
				for (int k = p + 1; k < SIZE_N * 2; k++)	// 모든 행의 값을 기준행에 맞춰 다 빼줌 (즉, p,p번째의 값(1.0)빼고는 전부 0으로 만들어줌
					AugMtrx[j][k] = AugMtrx[j][k] - (anotherDiv * AugMtrx[p][k]);
			}
		}

		fprintf(fout, "\nAfter diagonalizing at p = %d\n", p);
		FPrintMtrx(fout, AugMtrx, SIZE_N, SIZE_N * 2);		// 출력 
	}

	// 역행렬 계산 완료
	//--------------------------------------------------------------------------------------------------
	// 이제 계산된 역행렬을 메인의 Inv_mA에 대입

	for (int i = 0; i < SIZE_N; i++)
		for (int j = 0; j < SIZE_N; j++)
			Inv_mA[i][j] = AugMtrx[i][j + SIZE_N];

	DeleteDynMtrx(AugMtrx, SIZE_N);							// 이 함수 안에서 사용된 AugMtrx는 역할이 끝났으므로 할당 해제한다.
}