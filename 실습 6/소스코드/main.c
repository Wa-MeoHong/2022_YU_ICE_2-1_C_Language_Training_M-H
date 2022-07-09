/*
  파일명 : "실습6_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 1. 적은 배열을 정렬하는 3가지 정렬법( 선택, 병합, 퀵)을 각각하고 처리하는데 걸린 시간 비교
	  2. 큰 난수 배열을 생성 후, 하이브리드 퀵정렬로 정렬된 모습을 출력
	  3. 퀵 정렬과 하이브리드 퀵정렬의 시간차이 비교

  프로그램 작성자 : 신대홍(2022년 6월 3일)
  최종 Update : Version 1.0.0, 2022년 6월 3일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/04/05		v1.0.0		  최초작성
	신대홍		 2022/04/06		v1.5.0		  하이브리드 퀵정렬 추가
	신대홍		 2022/04/07		v1.5.1	 	  하이브리드 퀵정렬 코드 수정
	신대홍		 2022/06/03		v1.0.0		  최초작성
===========================================================================================================
*/

#include "Big_Array.h"
#include "Sorting.h"
#include <windows.h>

#define BIGSIZE 1000000
void Compare_Sorting_Algorithms_SmallIntArray();			// 적은수의 난수 배열의 정렬 비교
void testBigRandArray();									// 난수 생성 테스트
void PM_Hybrid_QS_SS_IntArray();							// 난수 배열 하이브리드 퀵 정렬

int main(void)
{

	int menu;

	while (1)								// 0입력 전까지 실행, 메뉴
	{
		printf("\nTest Array Algorithms   \n");
		printf("	1: Performance Comparison of Selection Sort and Quick Sort for Small Integer Array\n");
		printf("	2: Test bigRandArray (Array_size : 1,000,000 ~ 50,000,000)\n");
		printf("	3: Performance Measurements of hybrid_QS_SS ofr Integer Array\n");
		printf("Input menu (0 is exit): ");
		scanf("%d", &menu);


		// 메뉴
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
	double t_diff;									//시간 차 계산

	double t_Selection, t_Merge, t_Quick;

	QueryPerformanceFrequency(&freq);				// CPU의 클럭수를 측정, 클럭수는 거의 변하는 값이 아니므로 한번만 측정

	printf("Compare the performance of sorting algorithms for small array\n");
	printf("====================================================================\n");
	printf(" Array size	QuickSort[μs]	MergeSort[μs]	SelectionSort[μs]\n");
	printf("--------------------------------------------------------------------\n");

	for (size = 10; size <= 100; size += 10)
	{
		array = (int*)calloc(size, sizeof(int));
		if (array == NULL)
		{
			printf("Error in creation of array (size = %d)!\n", size);
			exit(1);
		}
		genBigRandArray(array, size, offset);		// 최초 난수 생성

		QueryPerformanceCounter(&t_1);				// 시간재기(함수시작전)
		_QUICKSORT(array, size);					// 퀵정렬
		QueryPerformanceCounter(&t_2);				// 시간재기(함수끝)
		t_diff = t_2.QuadPart - t_1.QuadPart;
		t_Quick = ((double)t_diff / (double)freq.QuadPart) * Micro; // μs단위 변환
		SuffleBigArray(array, size);
		// 다시 섞어준다.

		QueryPerformanceCounter(&t_1);				// 시간재기(함수시작전)
		mergeSort(array, size);						// 병합정렬
		QueryPerformanceCounter(&t_2);				// 시간재기(함수끝)
		t_diff = t_2.QuadPart - t_1.QuadPart;
		t_Merge = ((double)t_diff / (double)freq.QuadPart) * Micro; // μs단위 변환
		SuffleBigArray(array, size);
		// 다시 섞어준다.

		QueryPerformanceCounter(&t_1);				// 시간재기(함수시작전)
		selectionSort(array, size, 0, size - 1);	// 선택정렬
		QueryPerformanceCounter(&t_2);				// 시간재기(함수끝)
		t_diff = t_2.QuadPart - t_1.QuadPart;
		t_Selection = ((double)t_diff / (double)freq.QuadPart) * Micro; // μs단위 변환
		SuffleBigArray(array, size);

		printf("%10d\t%10.2lf\t%10.2lf\t%10.2lf\n", size, t_Quick, t_Merge, t_Selection);
		free(array);
	}
}

void testBigRandArray()								// 사이즈만큼의 갯수, OFFSET부터 시작하는 난수 생성기
{
	int SIZE, OFFSET;								// 사이즈, 오프셋
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
		genBigRandArray(array, SIZE, OFFSET);					// 난수 생성
		printf("Generated non-duplicated random array : \n");	// 정렬X 출력
		printBigarraySample(array, SIZE, LINE_SIZE, 2);			// 출력

		printf("Sorted Array : \n");							// 정렬 후 출력
		_H_Brid_QUICKSORT(array, SIZE);							// 하이브리드 퀵정렬
		printBigarraySample(array, SIZE, LINE_SIZE, 2);			// 정렬 후 출력
		free(array);
	}
}

void PM_Hybrid_QS_SS_IntArray()							// 하이브리드 퀵정렬과 퀵정렬의 시간차 비교
{
	int* array;
	LARGE_INTEGER freq, t_1, t_2;
	double t_diff;										// 시간 차 계산
	double t_Quick, t_HQ;								// 시간차 퀵정렬, 하이브리드 퀵

	QueryPerformanceFrequency(&freq);					// CPU의 클럭수를 측정, 클럭수는 거의 변하는 값이 아니므로 한번만 측정

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
		genBigRandArray(array, SIZE, 0);				// 최초 난수 생성

		QueryPerformanceCounter(&t_1);					// 시간재기(함수시작전)
		_QUICKSORT(array, SIZE);						// 퀵정렬
		QueryPerformanceCounter(&t_2);					// 시간재기(함수끝)
		t_diff = t_2.QuadPart - t_1.QuadPart;
		t_Quick = ((double)t_diff / (double)freq.QuadPart) * Milli; // ms단위 변환
		SuffleBigArray(array, SIZE);

		QueryPerformanceCounter(&t_1);					// 시간재기(함수시작전)
		_H_Brid_QUICKSORT(array, SIZE);					// 퀵정렬
		QueryPerformanceCounter(&t_2);					// 시간재기(함수끝)
		t_diff = t_2.QuadPart - t_1.QuadPart;
		t_HQ = ((double)t_diff / (double)freq.QuadPart) * Milli; // ms단위 변환
		printf("%10d\t%10.2lf\t%10.2lf\n", SIZE, t_Quick, t_HQ);
		free(array);
	}
	printf("--------------------------------------------------------------------\n");
}