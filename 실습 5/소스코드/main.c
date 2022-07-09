#include "Big_Array.h"

#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"

void arrayStatistics_basicArray(FILE* fout);					// 1번, 함수안에 선언된 배열에 관한 계산들 출력 
void arrayStatistics_externArray(FILE* fout);					// 2번, 외부의 변수를 끌고와서 계산
void arrayStatistics_fileDataArray(FILE* fout);					// 3번, 파일을 불러와서 배열 계산
void arrayStatistics_inputArray(FILE* fout);					// 4번, 배열 입력 후 계산 
void arrayStatistics_genBigRandArray(FILE* fout);				// 5번 큰난수 배열

int main(void)
{
	FILE* fout;
	char menu;

	fout = fopen(Data_Output_File, "w");		//output 파일을 쓰기모드로 열기, 없으면 만듦
	if (fout == NULL)
	{
		printf("Error in creation of %s !! \n", Data_Output_File);
		return -1;
	}

	while (1)
	{
		printf("Test Array Handing (1: data_array; 2: extern_array;\
 3: data_file; 4:data_input;5: genBigRandArray; ESC: terminate) : ");
		menu = _getche();								// 에코가 있는 _getch()
		if (menu == ESC)
			break;
		switch (menu)
		{
		case '1':
			arrayStatistics_basicArray(fout);			// 기본 배열 출력
			break;
		case '2':
			arrayStatistics_externArray(fout);			// 외부 소스 배열 출력
			break;
		case '3':
			arrayStatistics_fileDataArray(fout);		// 외부 파일 배열 출력
			break;
		case '4':
			arrayStatistics_inputArray(fout);			// 파일에 숫자 배열 넣기
			break;
		case '5':
			arrayStatistics_genBigRandArray(fout);		// 아주 거대한 랜덤 숫자 생성 후 분석 및 출력
			break;
		default:
			printf("\nWrong number!! If you trying to terminate this program, press ESC\n");
			continue;
		}
	}
	fclose(fout);										// 파일 사용 후, 파일을 닫는다.
	return 0;
}

void arrayStatistics_basicArray(FILE* fout)						// 1번, 함수안에 선언된 배열에 관한 계산들 출력 
{
	int num_data = 10;
	int data_array1[MAX_NUM_DATA] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // 먼저 선언된 배열을 사용

	printf("\nArrayStatistics_BasicArray .....\n");
	fprintf(fout, "\nArrayStatistics_BasicArray .....\n");
	getArrayStatistics(data_array1, num_data);					// 계산하고 출력
	fgetArrayStatistics(fout, data_array1, num_data);			// 계산 하고 출력(파일에 입력)
	printf("arrayStatistics_basicArray - completed. Result is also stored in output\
 file(%s). \n\n", Data_Output_File);							//완료되었다고 문장 출력, 파일에 저장되었다고도 출력
}

void arrayStatistics_externArray(FILE* fout)					// 2번, 외부의 변수를 끌고와서 계산
{
	int num_data = 0;
	extern int data_array[MAX_NUM_DATA];
	int i = 0;

	while (data_array[i] != EOF)
	{
		num_data++;
		i++;
	}

	printf("\nArrayStatistics_externArray .....\n");
	fprintf(fout, "\nArrayStatistics_externArray .....\n");
	getArrayStatistics(data_array, num_data);					// 계산하고 출력
	fgetArrayStatistics(fout, data_array, num_data);			// 계산 하고 출력
	printf("arrayStatistics_externArray - completed. Result is also stored in output\
 file(%s). \n\n", Data_Output_File);							// 1번과 똑같음
}

void arrayStatistics_fileDataArray(FILE* fout)						// 3번, 파일을 불러와서 배열 계산
{
	FILE* fin;
	int num_data = 0, data;
	int data_array2[MAX_NUM_DATA];

	fin = fopen(Data_Input_File, "r");								// 파일을 읽기모드로 열기
	if (fin == NULL)												// 파일이 안렸렸다면 안열렸다고 출력
	{
		printf("Error in opening input data file !!\n");
		return 0;
	}
	while (1)
	{
		fscanf(fin, "%d", &data);									// 파일에 작성된 값을 data로 받아옴
		if (data == EOF || num_data >= MAX_NUM_DATA)				// 프라임 문자(-1)가 들어간 것을 찾으면 반복을 중단
			break;
		data_array2[num_data] = data;								// 배열에 data 값을 할당
		num_data++;
	}
	fclose(fin);													// 파일 닫기(읽기로 불러온 파일)

	printf("\nArrayStatistics_FileDataArray .....\n");
	fprintf(fout, "\nArrayStatistics_FileDataArray .....\n");
	getArrayStatistics(data_array2, num_data);						// 계산하고 출력
	fgetArrayStatistics(fout, data_array2, num_data);				// 계산 하고 출력
	printf("arrayStatistics_FileDataArray - completed. Result is also stored in output\
 file(%s). \n\n", Data_Output_File);
}

void arrayStatistics_inputArray(FILE* fout)						// 4번, 배열 입력 후 계산 
{
	int num_data = 0, data = 0;
	int data_array3[MAX_NUM_DATA] = { 0 };

	printf("\nArrayStatistics_InputArray .....\n");
	fprintf(fout, "\nArrayStatistics_InputArray .....\n");
	printf("Please input the number of integers (less than %d) : ", MAX_NUM_DATA);

	// MAX_NUM_DATA보다 클때 무한 입력
	do
	{
		scanf("%d", &num_data);
	} while (num_data > MAX_NUM_DATA);

	printf("Please input integers : ");							// 배열에 입력
	for (int i = 0; i < num_data; i++)
	{
		scanf("%d", &data);
		data_array3[i] = data;
	}

	getArrayStatistics(data_array3, num_data);
	fgetArrayStatistics(fout, data_array3, num_data);
	printf("arrayStatistics_InputArray - completed. Result is also stored in output\
 file(%s). \n\n", Data_Output_File);
}

void arrayStatistics_genBigRandArray(FILE* fout)				// 5번 큰난수 배열 
{
	int* data_array4 = NULL;
	int SIZE = 0;
	srand((unsigned int)time(NULL));
	printf("\nArrayStatistics_GenBigRandArray .....\n");
	fprintf(fout, "\nArrayStatistics_GenBigRandArray .....\n");
	printf("Big_Array Size (more than 50000) : ");
	scanf("%d", &SIZE);

	data_array4 = (int*)calloc(SIZE, sizeof(int));

	BigRandArray(data_array4, SIZE);
	getArrayStatistics(data_array4, SIZE);
	fgetArrayStatistics(fout, data_array4, SIZE);
	printf("arrayStatistics_GenBigRandArray - completed. Result is also stored in output\
 file(%s). \n\n", Data_Output_File);
}