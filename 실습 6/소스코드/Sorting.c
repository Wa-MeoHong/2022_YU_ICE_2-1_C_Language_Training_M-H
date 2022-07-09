#include "Sorting.h"
#include "Big_Array.h"

void selectionSort(int* array, int SIZE, int left, int right)			//선택 정렬 함수
{
	int min_NUM;										// 작은값 찾기
	int Index_min_NUM;									// 작은값의 인덱스 넘버

	for (int round = left; round < right - 1; round++)
	{
		Index_min_NUM = round;							// 최소값의 인덱스 초기값(round) 설정
		min_NUM = array[round];							// 최소값 초기값 설정
		for (int i = round + 1; i < right; i++)
		{
			if (array[i] < min_NUM)
			{
				Index_min_NUM = i;
				min_NUM = array[i];
			}
		}
		if (Index_min_NUM != round)						// 만약 가장 작은 값이 자기자신(기준값)이 아니라면
		{
			array[Index_min_NUM] = array[round];		// 찾았던 인덱스 주소안의 값을 기준값과 변경
			array[round] = min_NUM;						// 가장작은값은 아까 저장했던 그 작은값.
		}
	}
}

// 병합정렬
void mergeSort(int* array, int SIZE)					// 병합정렬 초기함수
{
	int* temp_array = (int*)calloc(SIZE, sizeof(int));
	if (temp_array == NULL)
	{
		printf("Error in creation of temp_array (size = %d)!\n", SIZE);
		exit(-1);
	}
	_mergeSort(array, temp_array, 0, SIZE - 1);			// 시작
	free(temp_array);
}

void _mergeSort(int* array, int* temp_array, int left, int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	_mergeSort(array, temp_array, left, mid);			// 계속 반을 쪼개서 왼쪽끝까지 간다.
	_mergeSort(array, temp_array, mid + 1, right);		// 반을 쪼개서 오른쪽을 간다.

	for (int i = left; i <= mid; i++)					// 왼쪽은 순서대로 임시 배열에 넣어줌
		temp_array[i] = array[i];
	for (int j = 1; j <= right - mid; j++)				// 오른쪽은 역순(중요)으로 임시배열에 넣어줌
		temp_array[right - j + 1] = array[j + mid];
	// [1, 5, 2, 9, ----- ] → [1, 5, 9, 2, -----]

	for (int i = left, j = right, k = left; k <= right; k++) //중간 기준으로
	{
		if (temp_array[i] < temp_array[j])
			array[k] = temp_array[i++];
		else
			array[k] = temp_array[j--];
	}
}

// 퀵정렬
int _partition(int* array, int SIZE, int left, int right, int P_I) //파티션 위치값 반환 함수
{
	int P_V;							// pivot value, 그 위치에 있는 값
	int newPI;							// new pivot index, 새로운 위치값
	int temp;							// 값 자리바꾸기 하기 위한 임시저장 변수

	P_V = array[P_I];
	array[P_I] = array[right];
	array[right] = P_V;					// 맨 처음 P_I에 있던 값을 맨 오른쪽(혹은 P_I-1위치에 있는 값)과 바꾼다

	newPI = left;						// 이제 새로운 피벗위치를 설정해주는데 초기값은 맨 왼쪽(혹은 P_I + 1위치)으로 설정
	for (int i = left; i <= right - 1; i++) // 맨뒤로 가게된 P_V는 빼고 나머지 배열들을 범위로 잡는다.
	{
		if (array[i] <= P_V)			//만약 맨뒤로 간 P_V보다 값이 작다면
		{
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp;		// 현재(i)위치에 있는 값을 newPI에 있는 값과와 바꿔준다.
			newPI += 1;
		}
	}
	// 결론적으로 처음 P_V값을 기준으로 왼쪽은 P_V보다 작은 값들의 배열, 오른쪽은 P_V보다 큰 값들의 배열이 형성되었다.
	P_V = array[right];
	array[right] = array[newPI];
	array[newPI] = P_V;

	return newPI;						// 새로운 PI의 값을 반환해준다.
}

void quickSort(int* array, int SIZE, int left, int right) // 퀵정렬,본함수
{
	int P_I, newPI;
	if (left >= right)
		// 만약 left가 right보다 크거나 같다면 newPI반환 중지, 거의 left가 1혹은 0일때이다..
		return;

	else if (left < right)
	{
		P_I = (left + right) / 2;						// 중간값, 만약 홀수인경우 내림값으로 나누기위치값 산출
	}

	newPI = _partition(array, SIZE, left, right, P_I);	//새로운 P_I(나누기위치값) 산출 및, 정렬

	// 이렇게 왼쪽, 오른쪽 순서대로 작은덩이 → 큰덩이
	if (left < (newPI - 1))								
	// 이제 newPI기준으로 왼쪽부분
	{
		quickSort(array, SIZE, left, newPI - 1);		// 다시 newPI를 산출하면서 크기정렬을 쭉해준다.
	}
	if ((newPI + 1) < right)							
	// 다음, 왼쪽이 quickSort를 진행후, newPI기준 오른쪽 부분
	{
		quickSort(array, SIZE, newPI + 1, right);		// 오른쪽으로 newPI산출및 크기순으로 정렬해준다.
	}
}

void _QUICKSORT(int* array, int SIZE) //퀵 정렬 최초 함수
{
	quickSort(array, SIZE, 0, SIZE - 1);
	//처음 할때는 left = 위치값이 0, right = size-1
}

// ==============================================================

void _H_Brid_QUICKSORT(int* array, int SIZE) //하이브리드 퀵정렬 초기함수
{
	H_Brid_quickSort(array, SIZE, 0, SIZE - 1);
	//처음 할때는 left = 위치값이 0, right = size-1
}

void H_Brid_quickSort(int* array, int SIZE, int left, int right)
//하이브리드 퀵정렬 본함수, 파티션은 끌어온다.
{
	int temp; // 값 자리바꾸기 하기 위한 임시저장 변수
	int P_I;  // P_I = pivot index(위치값)
	int newPI; //new pivot index, 새로운 위치값
	int P_V; //pivot value, 그 위치에 있는 값

	if (right - left < QUICK_SELECTION_THRESHOLD)
		//만약 PI로 나눈 배열들의 길이가 QUICK_SELECTION_THRESHOLD보다 적다면
		// 퀵 정렬보다 선택정렬이 더 효율적이므로 다른것 보다 이걸 진행시킨후, 돌아간다.
	{
		selectionSort(array, SIZE, left, right + 1);
		return;
	}
	else if (left < right)
	{
		P_I = (left + right) / 2; // 중간값, 만약 홀수인경우 내림값으로 나누기위치값 산출
	}

	// newPI 재설정하는 코드들 
	P_V = array[P_I]; // 가져온 배열의 중앙값 P_V
	array[P_I] = array[right];
	array[right] = P_V; // 맨 처음 P_I에 있던 값을 맨 오른쪽(혹은 P_I-1위치에 있는 값)과 바꾼다
	newPI = left; // 이제 새로운 피벗위치를 설정해주는데 초기값은 맨 왼쪽(혹은 P_I + 1위치)으로 설정
	for (int i = left; i <= right - 1; i++) // 맨뒤로 가게된 P_V는 빼고 나머지 배열들을 범위로 잡는다.
	{
		if (array[i] <= P_V) //만약 맨뒤로 간 P_V보다 값이 작다면
		{
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp; // 현재(i)위치에 있는 값을 newPI에 있는 값과와 바꿔준다.
			newPI += 1;
		}
	}
	// 결론적으로 처음 P_V값을 기준으로 왼쪽은 P_V보다 작은 값들의 배열, 오른쪽은 P_V보다 큰 값들의 배열이 형성되었다.
	P_V = array[right];
	array[right] = array[newPI];
	array[newPI] = P_V;
	// partition 코드 거의 가져옴

	// 이렇게 왼쪽, 오른쪽 순서대로 작은덩이 → 큰덩이
	if (left < (newPI - 1)) // 이제 newPI기준으로 왼쪽부분
	{
		H_Brid_quickSort(array, SIZE, left, newPI - 1);
		// 다시 newPI를 산출하면서 크기정렬을 쭉해준다.
	}
	if (right > (newPI + 1)) // 다음, 왼쪽이 quickSort를 진행후, newPI기준 오른쪽 부분
	{
		H_Brid_quickSort(array, SIZE, newPI + 1, right);
		// 오른쪽으로 newPI산출및 크기순으로 정렬해준다.
	}
}