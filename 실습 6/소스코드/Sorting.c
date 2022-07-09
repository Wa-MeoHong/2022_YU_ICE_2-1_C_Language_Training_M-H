#include "Sorting.h"
#include "Big_Array.h"

void selectionSort(int* array, int SIZE, int left, int right)			//���� ���� �Լ�
{
	int min_NUM;										// ������ ã��
	int Index_min_NUM;									// �������� �ε��� �ѹ�

	for (int round = left; round < right - 1; round++)
	{
		Index_min_NUM = round;							// �ּҰ��� �ε��� �ʱⰪ(round) ����
		min_NUM = array[round];							// �ּҰ� �ʱⰪ ����
		for (int i = round + 1; i < right; i++)
		{
			if (array[i] < min_NUM)
			{
				Index_min_NUM = i;
				min_NUM = array[i];
			}
		}
		if (Index_min_NUM != round)						// ���� ���� ���� ���� �ڱ��ڽ�(���ذ�)�� �ƴ϶��
		{
			array[Index_min_NUM] = array[round];		// ã�Ҵ� �ε��� �ּҾ��� ���� ���ذ��� ����
			array[round] = min_NUM;						// ������������ �Ʊ� �����ߴ� �� ������.
		}
	}
}

// ��������
void mergeSort(int* array, int SIZE)					// �������� �ʱ��Լ�
{
	int* temp_array = (int*)calloc(SIZE, sizeof(int));
	if (temp_array == NULL)
	{
		printf("Error in creation of temp_array (size = %d)!\n", SIZE);
		exit(-1);
	}
	_mergeSort(array, temp_array, 0, SIZE - 1);			// ����
	free(temp_array);
}

void _mergeSort(int* array, int* temp_array, int left, int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	_mergeSort(array, temp_array, left, mid);			// ��� ���� �ɰ��� ���ʳ����� ����.
	_mergeSort(array, temp_array, mid + 1, right);		// ���� �ɰ��� �������� ����.

	for (int i = left; i <= mid; i++)					// ������ ������� �ӽ� �迭�� �־���
		temp_array[i] = array[i];
	for (int j = 1; j <= right - mid; j++)				// �������� ����(�߿�)���� �ӽù迭�� �־���
		temp_array[right - j + 1] = array[j + mid];
	// [1, 5, 2, 9, ----- ] �� [1, 5, 9, 2, -----]

	for (int i = left, j = right, k = left; k <= right; k++) //�߰� ��������
	{
		if (temp_array[i] < temp_array[j])
			array[k] = temp_array[i++];
		else
			array[k] = temp_array[j--];
	}
}

// ������
int _partition(int* array, int SIZE, int left, int right, int P_I) //��Ƽ�� ��ġ�� ��ȯ �Լ�
{
	int P_V;							// pivot value, �� ��ġ�� �ִ� ��
	int newPI;							// new pivot index, ���ο� ��ġ��
	int temp;							// �� �ڸ��ٲٱ� �ϱ� ���� �ӽ����� ����

	P_V = array[P_I];
	array[P_I] = array[right];
	array[right] = P_V;					// �� ó�� P_I�� �ִ� ���� �� ������(Ȥ�� P_I-1��ġ�� �ִ� ��)�� �ٲ۴�

	newPI = left;						// ���� ���ο� �ǹ���ġ�� �������ִµ� �ʱⰪ�� �� ����(Ȥ�� P_I + 1��ġ)���� ����
	for (int i = left; i <= right - 1; i++) // �ǵڷ� ���Ե� P_V�� ���� ������ �迭���� ������ ��´�.
	{
		if (array[i] <= P_V)			//���� �ǵڷ� �� P_V���� ���� �۴ٸ�
		{
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp;		// ����(i)��ġ�� �ִ� ���� newPI�� �ִ� ������ �ٲ��ش�.
			newPI += 1;
		}
	}
	// ��������� ó�� P_V���� �������� ������ P_V���� ���� ������ �迭, �������� P_V���� ū ������ �迭�� �����Ǿ���.
	P_V = array[right];
	array[right] = array[newPI];
	array[newPI] = P_V;

	return newPI;						// ���ο� PI�� ���� ��ȯ���ش�.
}

void quickSort(int* array, int SIZE, int left, int right) // ������,���Լ�
{
	int P_I, newPI;
	if (left >= right)
		// ���� left�� right���� ũ�ų� ���ٸ� newPI��ȯ ����, ���� left�� 1Ȥ�� 0�϶��̴�..
		return;

	else if (left < right)
	{
		P_I = (left + right) / 2;						// �߰���, ���� Ȧ���ΰ�� ���������� ��������ġ�� ����
	}

	newPI = _partition(array, SIZE, left, right, P_I);	//���ο� P_I(��������ġ��) ���� ��, ����

	// �̷��� ����, ������ ������� �������� �� ū����
	if (left < (newPI - 1))								
	// ���� newPI�������� ���ʺκ�
	{
		quickSort(array, SIZE, left, newPI - 1);		// �ٽ� newPI�� �����ϸ鼭 ũ�������� �����ش�.
	}
	if ((newPI + 1) < right)							
	// ����, ������ quickSort�� ������, newPI���� ������ �κ�
	{
		quickSort(array, SIZE, newPI + 1, right);		// ���������� newPI����� ũ������� �������ش�.
	}
}

void _QUICKSORT(int* array, int SIZE) //�� ���� ���� �Լ�
{
	quickSort(array, SIZE, 0, SIZE - 1);
	//ó�� �Ҷ��� left = ��ġ���� 0, right = size-1
}

// ==============================================================

void _H_Brid_QUICKSORT(int* array, int SIZE) //���̺긮�� ������ �ʱ��Լ�
{
	H_Brid_quickSort(array, SIZE, 0, SIZE - 1);
	//ó�� �Ҷ��� left = ��ġ���� 0, right = size-1
}

void H_Brid_quickSort(int* array, int SIZE, int left, int right)
//���̺긮�� ������ ���Լ�, ��Ƽ���� ����´�.
{
	int temp; // �� �ڸ��ٲٱ� �ϱ� ���� �ӽ����� ����
	int P_I;  // P_I = pivot index(��ġ��)
	int newPI; //new pivot index, ���ο� ��ġ��
	int P_V; //pivot value, �� ��ġ�� �ִ� ��

	if (right - left < QUICK_SELECTION_THRESHOLD)
		//���� PI�� ���� �迭���� ���̰� QUICK_SELECTION_THRESHOLD���� ���ٸ�
		// �� ���ĺ��� ���������� �� ȿ�����̹Ƿ� �ٸ��� ���� �̰� �����Ų��, ���ư���.
	{
		selectionSort(array, SIZE, left, right + 1);
		return;
	}
	else if (left < right)
	{
		P_I = (left + right) / 2; // �߰���, ���� Ȧ���ΰ�� ���������� ��������ġ�� ����
	}

	// newPI �缳���ϴ� �ڵ�� 
	P_V = array[P_I]; // ������ �迭�� �߾Ӱ� P_V
	array[P_I] = array[right];
	array[right] = P_V; // �� ó�� P_I�� �ִ� ���� �� ������(Ȥ�� P_I-1��ġ�� �ִ� ��)�� �ٲ۴�
	newPI = left; // ���� ���ο� �ǹ���ġ�� �������ִµ� �ʱⰪ�� �� ����(Ȥ�� P_I + 1��ġ)���� ����
	for (int i = left; i <= right - 1; i++) // �ǵڷ� ���Ե� P_V�� ���� ������ �迭���� ������ ��´�.
	{
		if (array[i] <= P_V) //���� �ǵڷ� �� P_V���� ���� �۴ٸ�
		{
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp; // ����(i)��ġ�� �ִ� ���� newPI�� �ִ� ������ �ٲ��ش�.
			newPI += 1;
		}
	}
	// ��������� ó�� P_V���� �������� ������ P_V���� ���� ������ �迭, �������� P_V���� ū ������ �迭�� �����Ǿ���.
	P_V = array[right];
	array[right] = array[newPI];
	array[newPI] = P_V;
	// partition �ڵ� ���� ������

	// �̷��� ����, ������ ������� �������� �� ū����
	if (left < (newPI - 1)) // ���� newPI�������� ���ʺκ�
	{
		H_Brid_quickSort(array, SIZE, left, newPI - 1);
		// �ٽ� newPI�� �����ϸ鼭 ũ�������� �����ش�.
	}
	if (right > (newPI + 1)) // ����, ������ quickSort�� ������, newPI���� ������ �κ�
	{
		H_Brid_quickSort(array, SIZE, newPI + 1, right);
		// ���������� newPI����� ũ������� �������ش�.
	}
}