/*
  ���ϸ� : "�ǽ�6_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- 1. ���� �迭�� �����ϴ� 3���� ���Ĺ�( ����, ����, ��)�� �����ϰ� ó���ϴµ� �ɸ� �ð� ��
	  2. ū ���� �迭�� ���� ��, ���̺긮�� �����ķ� ���ĵ� ����� ���
	  3. �� ���İ� ���̺긮�� �������� �ð����� ��

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 6�� 3��)
  ���� Update : Version 1.0.0, 2022�� 6�� 3��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/04/05		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/04/06		v1.5.0		  ���̺긮�� ������ �߰�
	�Ŵ�ȫ		 2022/04/07		v1.5.1	 	  ���̺긮�� ������ �ڵ� ����
	�Ŵ�ȫ		 2022/06/03		v1.0.0		  �����ۼ�
===========================================================================================================
*/

#include "Big_Array.h"
#include "Sorting.h"
#include <windows.h>

#define BIGSIZE 1000000
void Compare_Sorting_Algorithms_SmallIntArray();			// �������� ���� �迭�� ���� ��
void testBigRandArray();									// ���� ���� �׽�Ʈ
void PM_Hybrid_QS_SS_IntArray();							// ���� �迭 ���̺긮�� �� ����

int main(void)
{

	int menu;

	while (1)								// 0�Է� ������ ����, �޴�
	{
		printf("\nTest Array Algorithms   \n");
		printf("	1: Performance Comparison of Selection Sort and Quick Sort for Small Integer Array\n");
		printf("	2: Test bigRandArray (Array_size : 1,000,000 ~ 50,000,000)\n");
		printf("	3: Performance Measurements of hybrid_QS_SS ofr Integer Array\n");
		printf("Input menu (0 is exit): ");
		scanf("%d", &menu);


		// �޴�
		if (menu == 0)
			break;
		switch (menu)
		{
		case 1:
			Compare_Sorting_Algorithms_SmallIntArray();
			break;
		case 2:
			testBigRandArray();
			break;
		case 3:
			PM_Hybrid_QS_SS_IntArray();
			break;
		default:
			break;
		}
	}
	return 0;
}

void Compare_Sorting_Algorithms_SmallIntArray()
{
	int* array;
	int size, offset = 0;
	LARGE_INTEGER freq, t_1, t_2;
	double t_diff;									//�ð� �� ���

	double t_Selection, t_Merge, t_Quick;

	QueryPerformanceFrequency(&freq);				// CPU�� Ŭ������ ����, Ŭ������ ���� ���ϴ� ���� �ƴϹǷ� �ѹ��� ����

	printf("Compare the performance of sorting algorithms for small array\n");
	printf("====================================================================\n");
	printf(" Array size	QuickSort[��s]	MergeSort[��s]	SelectionSort[��s]\n");
	printf("--------------------------------------------------------------------\n");

	for (size = 10; size <= 100; size += 10)
	{
		array = (int*)calloc(size, sizeof(int));
		if (array == NULL)
		{
			printf("Error in creation of array (size = %d)!\n", size);
			exit(1);
		}
		genBigRandArray(array, size, offset);		// ���� ���� ����

		QueryPerformanceCounter(&t_1);				// �ð����(�Լ�������)
		_QUICKSORT(array, size);					// ������
		QueryPerformanceCounter(&t_2);				// �ð����(�Լ���)
		t_diff = t_2.QuadPart - t_1.QuadPart;
		t_Quick = ((double)t_diff / (double)freq.QuadPart) * Micro; // ��s���� ��ȯ
		SuffleBigArray(array, size);
		// �ٽ� �����ش�.

		QueryPerformanceCounter(&t_1);				// �ð����(�Լ�������)
		mergeSort(array, size);						// ��������
		QueryPerformanceCounter(&t_2);				// �ð����(�Լ���)
		t_diff = t_2.QuadPart - t_1.QuadPart;
		t_Merge = ((double)t_diff / (double)freq.QuadPart) * Micro; // ��s���� ��ȯ
		SuffleBigArray(array, size);
		// �ٽ� �����ش�.

		QueryPerformanceCounter(&t_1);				// �ð����(�Լ�������)
		selectionSort(array, size, 0, size - 1);	// ��������
		QueryPerformanceCounter(&t_2);				// �ð����(�Լ���)
		t_diff = t_2.QuadPart - t_1.QuadPart;
		t_Selection = ((double)t_diff / (double)freq.QuadPart) * Micro; // ��s���� ��ȯ
		SuffleBigArray(array, size);

		printf("%10d\t%10.2lf\t%10.2lf\t%10.2lf\n", size, t_Quick, t_Merge, t_Selection);
		free(array);
	}
}

void testBigRandArray()								// �����ŭ�� ����, OFFSET���� �����ϴ� ���� ������
{
	int SIZE, OFFSET;								// ������, ������
	int* array;

	while (1)
	{
		printf("Input BigRandArray_SIZE (0 to Quit) and offset : ");
		scanf("%d %d", &SIZE, &OFFSET);

		if (SIZE == 0)
			break;

		array = (int*)calloc(SIZE, sizeof(int));
		if (array == NULL)
		{
			printf("Error in creation of array (size = %d)!\n", SIZE);
			exit(1);
		}
		genBigRandArray(array, SIZE, OFFSET);					// ���� ����
		printf("Generated non-duplicated random array : \n");	// ����X ���
		printBigarraySample(array, SIZE, LINE_SIZE, 2);			// ���

		printf("Sorted Array : \n");							// ���� �� ���
		_H_Brid_QUICKSORT(array, SIZE);							// ���̺긮�� ������
		printBigarraySample(array, SIZE, LINE_SIZE, 2);			// ���� �� ���
		free(array);
	}
}

void PM_Hybrid_QS_SS_IntArray()							// ���̺긮�� �����İ� �������� �ð��� ��
{
	int* array;
	LARGE_INTEGER freq, t_1, t_2;
	double t_diff;										// �ð� �� ���
	double t_Quick, t_HQ;								// �ð��� ������, ���̺긮�� ��

	QueryPerformanceFrequency(&freq);					// CPU�� Ŭ������ ����, Ŭ������ ���� ���ϴ� ���� �ƴϹǷ� �ѹ��� ����

	printf("Compare the perfomance of quickSort and Hybrid_quick_selectionSort for large array\n");
	printf("QS_SS_THRESHOLD : %d\n", QUICK_SELECTION_THRESHOLD);
	printf("====================================================================\n");
	printf(" Array Size\tQuickSort[ms]\tHybridQuickSelectionSort[ms]\n");
	printf("--------------------------------------------------------------------\n");
	for (int SIZE = BIGSIZE; SIZE <= BIGSIZE * 5; SIZE += BIGSIZE)
	{
		array = (int*)calloc(SIZE, sizeof(int));
		if (array == NULL)
		{
			printf("Error in creation of array (size = %d)!\n", SIZE);
			exit(1);
		}
		genBigRandArray(array, SIZE, 0);				// ���� ���� ����

		QueryPerformanceCounter(&t_1);					// �ð����(�Լ�������)
		_QUICKSORT(array, SIZE);						// ������
		QueryPerformanceCounter(&t_2);					// �ð����(�Լ���)
		t_diff = t_2.QuadPart - t_1.QuadPart;
		t_Quick = ((double)t_diff / (double)freq.QuadPart) * Milli; // ms���� ��ȯ
		SuffleBigArray(array, SIZE);

		QueryPerformanceCounter(&t_1);					// �ð����(�Լ�������)
		_H_Brid_QUICKSORT(array, SIZE);					// ������
		QueryPerformanceCounter(&t_2);					// �ð����(�Լ���)
		t_diff = t_2.QuadPart - t_1.QuadPart;
		t_HQ = ((double)t_diff / (double)freq.QuadPart) * Milli; // ms���� ��ȯ
		printf("%10d\t%10.2lf\t%10.2lf\n", SIZE, t_Quick, t_HQ);
		free(array);
	}
	printf("--------------------------------------------------------------------\n");
}