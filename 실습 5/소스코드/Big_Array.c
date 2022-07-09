#include "Big_Array.h" 

void printBigarraySample(int* array, int SIZE, int line_size, int num_sample_lines)	//큰 배열 출력 함수
{
	int count = 0;
	if (SIZE < BIG_SIZE)							//만약 SIZE가 적은 수라면
	{
		num_sample_lines = SIZE / LINE_SIZE + 1;
	}												//출력을 위해 num_~변수를 출력에 맞게 고친다.

	for (int i = 0; i < num_sample_lines; i++)		//처음 30개 출력
	{
		for (int j = 0; j < line_size; j++)
		{
			if (count == SIZE)
			{
				break;
			}
			printf("%8d", array[count]);
			count++;
		}
		printf("\n");
	}
	if (SIZE >= BIG_SIZE)								//큰사이즈의 배열이라면 추가적으로 밑의 연산을 처리한다.
	{
		printf("\n . . . . . .\n");
		count = SIZE - (line_size * num_sample_lines);	// count(배열인덱스 번호)를 뒤에서 30번째 번호로 바꾸기

		for (int i = 0; i < num_sample_lines; i++)		// 마지막 30개 출력
		{
			for (int j = 0; j < line_size; j++)
			{
				printf("%8d", array[count]);
				count++;
			}
			printf("\n");
		}
		printf("\n");
	}
}

void fprintBigarraySample(FILE* fout, int* array, int SIZE, int line_size, int num_sample_lines)
{	// 파일용 큰함수 출력 함수
	int count = 0;

	if (SIZE < BIG_SIZE)								//만약 SIZE가 적은 수라면
	{
		num_sample_lines = SIZE / LINE_SIZE + 1;
	}													//출력을 위해 num_~변수를 출력에 맞게 고친다.
	for (int i = 0; i < num_sample_lines; i++)			// 파일에다가 입력 (맨처음 배열원소 30개 출력)
	{
		for (int j = 0; j < line_size; j++)
		{
			if (count == SIZE)
			{
				break;
			}
			fprintf(fout, "%8d", array[count]);
			count++;
		}
		fprintf(fout, "\n");
	}
	if (SIZE >= BIG_SIZE)								//큰사이즈의 배열이라면 추가적으로 밑의 연산을 처리한다.
	{
		fprintf(fout, "\n . . . . . .\n");
		count = SIZE - (line_size * num_sample_lines);	// count(배열인덱스 번호)를 뒤에서 30번째 번호로 바꾸기

		for (int i = 0; i < num_sample_lines; i++)		// 파일에다가 입력 (맨뒤의 배열원소 30개 출력)
		{
			for (int j = 0; j < line_size; j++)
			{
				fprintf(fout, "%8d", array[count]);
				count++;
			}
			fprintf(fout, "\n");
		}
		fprintf(fout, "\n");
	}
}

void getArrayStatistics(int* array, int SIZE)			//배열 원소 연산 함수
{
	double sum = 0, max = array[0], min = array[0];
	// 이미 배열을 매개변수로 받아왔기 때문에 초기화할때 배열의 첫값으로 초기화
	double avg, var = 0, std;

	for (int i = 0; i < SIZE; i++)						// MIN, MAX 구하기
	{
		max = MAX(max, array[i]);
		min = MIN(min, array[i]);
	}

	for (int i = 0; i < SIZE; i++)						// 배열 합 구하기
		sum += array[i];
	avg = sum / SIZE;									// 평균 구함

	for (int j = 0; j < SIZE; j++)						//분산 : (각 편차의 제곱의 평균)
	{
		var += pow(array[j] - avg, POWNUM);
	}
	var /= SIZE;
	std = sqrt(var);									// 표준편차 : √분산

	printf("Total (%3d) integer data : \n\n", SIZE);	// 배열 출력
	printBigarraySample(array, SIZE, LINE_SIZE, 3);		//큰배열 출력
	printf("MIN : (%.0lf), MAX : (%.0lf), AVG : (%5.2lf), VAR = (%5.2lf), STD : (%5.2lf) \n"\
		, min, max, avg, var, std);						//결과 출력
}

void fgetArrayStatistics(FILE* fout, int* array, int SIZE) //파일용 배열 원소 연산 함수, 위와 똑같다
{
	double sum = 0, max = array[0], min = array[0];
	double avg, var = 0, std;

	for (int i = 0; i < SIZE; i++)
	{
		max = MAX(max, array[i]);
		min = MIN(min, array[i]);
	}

	for (int i = 0; i < SIZE; i++)
		sum += array[i];
	avg = (double)sum / SIZE;

	for (int j = 0; j < SIZE; j++)
	{
		var += pow(array[j] - avg, POWNUM);
	}
	std = sqrt(var);

	fprintf(fout, "Total (%3d) integer data : \n", SIZE);
	fprintBigarraySample(fout, array, SIZE, LINE_SIZE, 3);
	fprintf(fout, "MIN : (%.0lf), MAX : (%.0lf), AVG : (%5.2lf), VAR = (%5.2lf), STD : (%5.2lf) \n"\
		, min, max, avg, var, std);
}

void BigRandArray(int* array, int SIZE)					// 큰난수 생성 
{
	char* flag = NULL;									// 중복되는 난수 값을 확인하기 위해 만들어둠
	int count = 0;										// while 초기식
	unsigned int bigRand = 0;							// 임시저장 공간 2

	flag = (char*)calloc(SIZE, sizeof(char));			// 발생시킬 개수만큼 동적메모리 할당
	if (flag == NULL)
	{
		printf("Error in Dynamic memory allocation for character array of size (%d)\n ", SIZE);
		exit(-1);
	}	//얘도 만약에 못받는 상황이 오면 그냥 끄도록한다.
	while (count < SIZE) //발생시킬 개수만큼
	{
		// 먼저 RAND()로 발생시키고, 15비트를 옮긴후, 그다음RAND()한 값과 OR연산으로 묶음
		bigRand = (((unsigned int)rand() << 15) | rand()) % SIZE; 

		if (flag[bigRand] == 1)							// 만약 bigRand가 이미 나온 난수라면 다시실행
		{
			continue;
		}
		else
		{
			flag[bigRand] = 1;							// 아니면 체크해주고
			array[count++] = bigRand + OFFSET;			// array에 값을 대입해준후, count를 ++한다.
		}
	}
	free(flag);											// 다끝나면 동적메모리 반환해줌
}