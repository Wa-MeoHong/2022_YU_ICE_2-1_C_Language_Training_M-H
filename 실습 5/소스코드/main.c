#include "Big_Array.h"

#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"

void arrayStatistics_basicArray(FILE* fout);					// 1��, �Լ��ȿ� ����� �迭�� ���� ���� ��� 
void arrayStatistics_externArray(FILE* fout);					// 2��, �ܺ��� ������ ����ͼ� ���
void arrayStatistics_fileDataArray(FILE* fout);					// 3��, ������ �ҷ��ͼ� �迭 ���
void arrayStatistics_inputArray(FILE* fout);					// 4��, �迭 �Է� �� ��� 
void arrayStatistics_genBigRandArray(FILE* fout);				// 5�� ū���� �迭

int main(void)
{
	FILE* fout;
	char menu;

	fout = fopen(Data_Output_File, "w");		//output ������ ������� ����, ������ ����
	if (fout == NULL)
	{
		printf("Error in creation of %s !! \n", Data_Output_File);
		return -1;
	}

	while (1)
	{
		printf("Test Array Handing (1: data_array; 2: extern_array;\
 3: data_file; 4:data_input;5: genBigRandArray; ESC: terminate) : ");
		menu = _getche();								// ���ڰ� �ִ� _getch()
		if (menu == ESC)
			break;
		switch (menu)
		{
		case '1':
			arrayStatistics_basicArray(fout);			// �⺻ �迭 ���
			break;
		case '2':
			arrayStatistics_externArray(fout);			// �ܺ� �ҽ� �迭 ���
			break;
		case '3':
			arrayStatistics_fileDataArray(fout);		// �ܺ� ���� �迭 ���
			break;
		case '4':
			arrayStatistics_inputArray(fout);			// ���Ͽ� ���� �迭 �ֱ�
			break;
		case '5':
			arrayStatistics_genBigRandArray(fout);		// ���� �Ŵ��� ���� ���� ���� �� �м� �� ���
			break;
		default:
			printf("\nWrong number!! If you trying to terminate this program, press ESC\n");
			continue;
		}
	}
	fclose(fout);										// ���� ��� ��, ������ �ݴ´�.
	return 0;
}

void arrayStatistics_basicArray(FILE* fout)						// 1��, �Լ��ȿ� ����� �迭�� ���� ���� ��� 
{
	int num_data = 10;
	int data_array1[MAX_NUM_DATA] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // ���� ����� �迭�� ���

	printf("\nArrayStatistics_BasicArray .....\n");
	fprintf(fout, "\nArrayStatistics_BasicArray .....\n");
	getArrayStatistics(data_array1, num_data);					// ����ϰ� ���
	fgetArrayStatistics(fout, data_array1, num_data);			// ��� �ϰ� ���(���Ͽ� �Է�)
	printf("arrayStatistics_basicArray - completed. Result is also stored in output\
 file(%s). \n\n", Data_Output_File);							//�Ϸ�Ǿ��ٰ� ���� ���, ���Ͽ� ����Ǿ��ٰ� ���
}

void arrayStatistics_externArray(FILE* fout)					// 2��, �ܺ��� ������ ����ͼ� ���
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
	getArrayStatistics(data_array, num_data);					// ����ϰ� ���
	fgetArrayStatistics(fout, data_array, num_data);			// ��� �ϰ� ���
	printf("arrayStatistics_externArray - completed. Result is also stored in output\
 file(%s). \n\n", Data_Output_File);							// 1���� �Ȱ���
}

void arrayStatistics_fileDataArray(FILE* fout)						// 3��, ������ �ҷ��ͼ� �迭 ���
{
	FILE* fin;
	int num_data = 0, data;
	int data_array2[MAX_NUM_DATA];

	fin = fopen(Data_Input_File, "r");								// ������ �б���� ����
	if (fin == NULL)												// ������ �ȷȷȴٸ� �ȿ��ȴٰ� ���
	{
		printf("Error in opening input data file !!\n");
		return 0;
	}
	while (1)
	{
		fscanf(fin, "%d", &data);									// ���Ͽ� �ۼ��� ���� data�� �޾ƿ�
		if (data == EOF || num_data >= MAX_NUM_DATA)				// ������ ����(-1)�� �� ���� ã���� �ݺ��� �ߴ�
			break;
		data_array2[num_data] = data;								// �迭�� data ���� �Ҵ�
		num_data++;
	}
	fclose(fin);													// ���� �ݱ�(�б�� �ҷ��� ����)

	printf("\nArrayStatistics_FileDataArray .....\n");
	fprintf(fout, "\nArrayStatistics_FileDataArray .....\n");
	getArrayStatistics(data_array2, num_data);						// ����ϰ� ���
	fgetArrayStatistics(fout, data_array2, num_data);				// ��� �ϰ� ���
	printf("arrayStatistics_FileDataArray - completed. Result is also stored in output\
 file(%s). \n\n", Data_Output_File);
}

void arrayStatistics_inputArray(FILE* fout)						// 4��, �迭 �Է� �� ��� 
{
	int num_data = 0, data = 0;
	int data_array3[MAX_NUM_DATA] = { 0 };

	printf("\nArrayStatistics_InputArray .....\n");
	fprintf(fout, "\nArrayStatistics_InputArray .....\n");
	printf("Please input the number of integers (less than %d) : ", MAX_NUM_DATA);

	// MAX_NUM_DATA���� Ŭ�� ���� �Է�
	do
	{
		scanf("%d", &num_data);
	} while (num_data > MAX_NUM_DATA);

	printf("Please input integers : ");							// �迭�� �Է�
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

void arrayStatistics_genBigRandArray(FILE* fout)				// 5�� ū���� �迭 
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