#include "Mtrx_GJ.h"


void GetAugmentedMtrx(FILE* fin, double** Mtrx, int* SIZE_N)				// ���� �Է� �Լ�
{
	double d = 0.0;															// ���Ͽ� �ִ� ���� ���� ���� d
	double** MtrxD;

	fscanf(fin, "%d", &(*SIZE_N));											// ���Ϸκ��� ��, �� ���� �о����

	// �о�� �����ŭ �����Ҵ� 
	MtrxD = (double**)calloc(*SIZE_N, sizeof(double*));
	for (int i = 0; i < *SIZE_N; i++)
		MtrxD[i] = (double*)calloc((*SIZE_N) + 1, sizeof(double));
	
	// �� ���� 
	for (int m = 0; m < *SIZE_N; m++)
	{
		for (int n = 0; n < (*SIZE_N) + 1; n++)
		{
			if (fscanf(fin, "%lf", &d) != EOF)								// EOF�� �ɶ� ����
				MtrxD[m][n] = d;											// �� ����
		}
	}

	*Mtrx = MtrxD;															// �ּ� ��ȯ 
}

void pivoting(double** augMtrx, int SIZE_N, int p, int* piv_FOUND) // �� �ٲ��ִ� �Լ� pivoting
{
	double max = 0;
	double temp = 0;
	int max_row = p;

	//���� ���� ū ���� ã�´�( �� ������)
	max = fabs(augMtrx[p][p]); //���� ��, �� ���� (1��°��,�� ��, 2��°��, ����, 3��°��,�� ��)
	// abs() = int���� ���� ��ȯ, fabs() = double ���� ���� ��ȯ

	for (int i = 0; i < SIZE_N; i++)
	{
		if (max < fabs(augMtrx[i][p]))
		{
			max_row = i;
			max = fabs(augMtrx[i][p]);
		}
	}

	if (max < Epsilon)									// ���� max == 0�̶�� 
		*piv_FOUND = 0;									// �ظ� ���� �� ���� ���¶�� �ϰ�, solExist�� 0���� �������
	else
	{
		*piv_FOUND = 1;									// �ƴϸ� solExist�� 1�� ���� ��, 
		if (max_row != p)								// ���� ������ ���� ū ���ȣ�� �ڱ� �ڽ��� �ƴ� ��쿡 �۵�
		{
			// �� p��, p������ �ϴ°��� �̹� �� ���� ���� ������ ������ ���� ��� ������ �Ϸ�Ǿ��� �����̴�.
			// ��, 2���� ������ �������� 1���� ��� 1, 0, 0, 0, 0,... ���� �����Ǿ� �ٲ� �ʿ䰡 ����.
			for (int k = p; k <= SIZE_N; k++)
			{
				temp = augMtrx[p][k];
				augMtrx[p][k] = augMtrx[max_row][k];
				augMtrx[max_row][k] = temp;
			}
		}
	}
}

void Diagnolize(FILE* fout, double** augMtrx, int SIZE_N, int* solExist) // ���콺-���� �ҰŹ� ��� �Լ�
{
	double pivDivide;
	double anotherDiv;

	for (int p = 0; (p < SIZE_N) && (*solExist); p++)
	{
		pivoting(augMtrx, SIZE_N, p, solExist);

		if (*solExist)
		{
			if (augMtrx[p][p] != 1.00)									// p,p�� ���� 1�� �ƴѰ�� (1�̸� �� ������ ���� �Ȱ�ħ)
			{
				pivDivide = augMtrx[p][p];
				augMtrx[p][p] = 1.00;
				for (int k = p + 1; k <= SIZE_N; k++)
					augMtrx[p][k] /= pivDivide;							// p,p�� ���� 1�� �ǵ��� ���� ��� ���� p,p�� ���� ����
			}
		}
		else
			break;
		// ������� pivoting ��, p��,p���� ���� 1�� ����� �ָ鼭 �� ���� ������ ���� �����ش�.

//-----------------------------------------------------------------------------------

	// ���⼭���� �� ������ ���� ������ �ٸ� ���� ���ָ鼭 p���� ������ ���� 0���� �������

		for (int j = 0; j < SIZE_N; j++)
		{
			if ((j != p) && (augMtrx[j][p] != 0.0))
				// p���� ������ ������ ��, ����, j���� p���� ���� 0(������ ��������)�� �ƴ� ����� ����
			{
				anotherDiv = augMtrx[j][p];
				augMtrx[j][p] = 0;
				for (int k = p + 1; k <= SIZE_N; k++)
					augMtrx[j][k] = augMtrx[j][k] - (anotherDiv * augMtrx[p][k]);
			}
		}
	}
}

void InvMtrx(FILE* fout, double** mA, double** Inv_mA, int SIZE_N, int* solexist) //����� ��� �Լ�
{
	// �������� ���� ���콺-���� �ҰŹ��� ����ϰ� �귯����, �����ʿ��� ������� ��������� �Ǵ°��� ���̴�.
	// ��, �迭�� �ΰ� ���ļ� ���콺-���� �ҰŹ�ó�� ����ϸ� �������� ��������� ������� �Ǿ� ���´�.

	double** AugMtrx;										// ������� ���ϱ����� ����+÷������� ���� �迭
	double pivDivide;										// p��, p���� ���� 1�� ���������� ��. �� ���� �̿��� p���� ���� �������ش�.
	double anotherDiv;										// p���� ���� �̿��Ͽ� �ٸ� ���� ������ 0���� ���鶧, �ٸ����� ���� ���߾��ֱ����� ���

	AugMtrx = (double**)calloc(SIZE_N, sizeof(double*));
	for (int i = 0; i < SIZE_N; i++)
		AugMtrx[i] = (double*)calloc(SIZE_N * 2, sizeof(double));

	for (int i = 0; i < SIZE_N; i++)
		for (int j = 0; j < SIZE_N; j++)					// AugMtrx�� ���� �κп� ���� ��� ����
			AugMtrx[i][j] = mA[i][j];

	for (int i = 0; i < SIZE_N; i++)
		for (int j = SIZE_N; j < SIZE_N * 2; j++)
			AugMtrx[i][j] = (i == j - SIZE_N) ? 1.0 : 0.0;	// AugMtrx�� ������ �κ�, ��� ����ȣ�� ���ٸ� 1, �ƴϸ� 0 ����
 
	//--------------------------------------------------------------------------------------------------
	//  ����� ��� ����
	for (int p = 0; p < SIZE_N; p++)
	{
		double max = fabs(AugMtrx[p][p]);
		//���� ��, �� ���� (1��°��,�� ��, 2��°��, ����, 3��°��,�� ��)
		// abs() = int���� ���� ��ȯ, fabs() = double ���� ���� ��ȯ

		for (int i = 0; i < SIZE_N; i++)
		{
			if (max < fabs(AugMtrx[i][p]))
				max = fabs(AugMtrx[i][p]); // �� p���� �� ��鿡 ���� p�������� �ִ밪�� ����
		}

		if (max < Epsilon)									// ���� max == 0�̶�� 
			*solexist = 0;									// �ظ� ���� �� ���� ���¶�� �ϰ�, solExist�� 0���� �������
		else
			*solexist = 1;									// �ƴϸ� solExist�� 1�� ���� ��, 
//=================================�ذ� ���� �Ǻ� ����===================================

		if (*solexist == 0)									// ������� ���Ҽ� ���� ������ ����
			break;

		if (AugMtrx[p][p] != 1.00)							// p,p�� ���� 1�� �ƴѰ�� (1�̸� �� ������ ���� �Ȱ�ħ)
		{
			pivDivide = AugMtrx[p][p];
			AugMtrx[p][p] = 1.00;
			for (int k = p + 1; k < SIZE_N * 2; k++)		// ����� ������ �迭�� ���������� SIZE_N�� �ι谡 ��...
				AugMtrx[p][k] /= pivDivide;					// p,p�� ���� 1�� �ǵ��� ���� ��� ���� p,p�� ���� ����
		}

		for (int j = 0; j < SIZE_N; j++)
		{
			if ((j != p) && (AugMtrx[j][p] != 0.0))
				// p���� ������ ������ ��, ����, j���� p���� ���� 0(������ ��������)�� �ƴ� ����� ����
			{
				anotherDiv = AugMtrx[j][p];
				AugMtrx[j][p] = 0;
				for (int k = p + 1; k < SIZE_N * 2; k++)	// ��� ���� ���� �����࿡ ���� �� ���� (��, p,p��°�� ��(1.0)����� ���� 0���� �������
					AugMtrx[j][k] = AugMtrx[j][k] - (anotherDiv * AugMtrx[p][k]);
			}
		}

		fprintf(fout, "\nAfter diagonalizing at p = %d\n", p);
		FPrintMtrx(fout, AugMtrx, SIZE_N, SIZE_N * 2);		// ��� 
	}

	// ����� ��� �Ϸ�
	//--------------------------------------------------------------------------------------------------
	// ���� ���� ������� ������ Inv_mA�� ����

	for (int i = 0; i < SIZE_N; i++)
		for (int j = 0; j < SIZE_N; j++)
			Inv_mA[i][j] = AugMtrx[i][j + SIZE_N];

	DeleteDynMtrx(AugMtrx, SIZE_N);							// �� �Լ� �ȿ��� ���� AugMtrx�� ������ �������Ƿ� �Ҵ� �����Ѵ�.
}