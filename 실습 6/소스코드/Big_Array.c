
#include "Big_Array.h"

#define Randomize() srand((unsigned int)time(NULL))

void genBigRandArray(int* array, int SIZE, int offset)			// 큰난수 생성, (offset ~ SIZE 까지 난수)
{
	char* flag = NULL;											// 중복되는 난수 값을 확인하기 위해 만들어둠
	int count = 0;												// while 초기식
	unsigned int bigRand = 0;									// 임시저장 공간

	Randomize();

	flag = (char*)calloc(SIZE + offset, sizeof(char));			// 발생시킬 개수만큼 동적메모리 할당
	if (flag == NULL)
	{
		printf("Error in Dynamic memory allocation for character array of size (%d)\n ", SIZE);
		exit(-1);
	}	//얘도 만약에 못받는 상황이 오면 그냥 끄도록한다.

	while (count < SIZE)										// 발생시킬 개수만큼
	{
		bigRand = (((unsigned int)rand() << 15) | rand()) % SIZE;

		if (flag[bigRand] == 1)									// 만약 bigRand가 이미 나온 난수라면 
		{
			continue;
		} 
		else
		{
			flag[bigRand] = 1;									// 아니면 체크해주고
			array[count++] = bigRand + offset;					// array에 값을 대입해준후, count를 ++한다.
		}
	}
	free(flag);													// 다끝나면 동적메모리 반환해줌
}

void printBigarraySample(int* array, int SIZE, int items_per_size, int num_sample_lines)
//큰 배열 출력 함수(items_per_size = 10, num_sample_lines = 2)
{
	int count = 0;

	if (SIZE < Small_SIZE)										// 만약 SIZE가 적은 수라면
		num_sample_lines = SIZE / items_per_size + 1;			// 출력을 위해 num_~변수를 출력에 맞게 고친다.
	for (int i = 0; i < num_sample_lines; i++)					// 처음 20개 출력
	{
		for (int j = 0; j < items_per_size; j++)
		{
			if (count == SIZE)
				break;
			printf("%9d", array[count]);
			count++;
		}
		printf("\n");
	}
	if (SIZE >= Small_SIZE)										// 큰사이즈의 배열이라면 추가적으로 밑의 연산을 처리한다.
	{
		printf("\n\t . . . . . .\n");
		count = SIZE - (items_per_size * num_sample_lines);		// count(배열인덱스 번호)를 뒤에서 30번째 번호로 바꾸기

		for (int i = 0; i < num_sample_lines; i++)				// 마지막 20개 출력
		{
			for (int j = 0; j < items_per_size; j++)
			{
				printf("%9d", array[count++]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void SuffleBigArray(int* array, int SIZE)						// 배열 섞어주기
{
	int i1, i2, d;												// 무작위로 뽑힌 i1, i2, 그리고 옮겨담을 임시저장변수 d
	Randomize();

	for (int i = 0; i < SIZE / 2; i++)
	{
		i1 = (((unsigned int)rand() << 15) | rand()) % (SIZE);
		i2 = (((unsigned int)rand() << 15) | rand()) % (SIZE);

		d = array[i1];
		array[i1] = array[i2];
		array[i2] = d;
	}
}