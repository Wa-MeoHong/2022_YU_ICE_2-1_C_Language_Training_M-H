#include "Big_Array.h" 

void printBigarraySample(int* array, int SIZE, int line_size, int num_sample_lines)	//ū �迭 ��� �Լ�
{
	int count = 0;
	if (SIZE < BIG_SIZE)							//���� SIZE�� ���� �����
	{
		num_sample_lines = SIZE / LINE_SIZE + 1;
	}												//����� ���� num_~������ ��¿� �°� ��ģ��.

	for (int i = 0; i < num_sample_lines; i++)		//ó�� 30�� ���
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
	if (SIZE >= BIG_SIZE)								//ū�������� �迭�̶�� �߰������� ���� ������ ó���Ѵ�.
	{
		printf("\n . . . . . .\n");
		count = SIZE - (line_size * num_sample_lines);	// count(�迭�ε��� ��ȣ)�� �ڿ��� 30��° ��ȣ�� �ٲٱ�

		for (int i = 0; i < num_sample_lines; i++)		// ������ 30�� ���
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
{	// ���Ͽ� ū�Լ� ��� �Լ�
	int count = 0;

	if (SIZE < BIG_SIZE)								//���� SIZE�� ���� �����
	{
		num_sample_lines = SIZE / LINE_SIZE + 1;
	}													//����� ���� num_~������ ��¿� �°� ��ģ��.
	for (int i = 0; i < num_sample_lines; i++)			// ���Ͽ��ٰ� �Է� (��ó�� �迭���� 30�� ���)
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
	if (SIZE >= BIG_SIZE)								//ū�������� �迭�̶�� �߰������� ���� ������ ó���Ѵ�.
	{
		fprintf(fout, "\n . . . . . .\n");
		count = SIZE - (line_size * num_sample_lines);	// count(�迭�ε��� ��ȣ)�� �ڿ��� 30��° ��ȣ�� �ٲٱ�

		for (int i = 0; i < num_sample_lines; i++)		// ���Ͽ��ٰ� �Է� (�ǵ��� �迭���� 30�� ���)
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

void getArrayStatistics(int* array, int SIZE)			//�迭 ���� ���� �Լ�
{
	double sum = 0, max = array[0], min = array[0];
	// �̹� �迭�� �Ű������� �޾ƿԱ� ������ �ʱ�ȭ�Ҷ� �迭�� ù������ �ʱ�ȭ
	double avg, var = 0, std;

	for (int i = 0; i < SIZE; i++)						// MIN, MAX ���ϱ�
	{
		max = MAX(max, array[i]);
		min = MIN(min, array[i]);
	}

	for (int i = 0; i < SIZE; i++)						// �迭 �� ���ϱ�
		sum += array[i];
	avg = sum / SIZE;									// ��� ����

	for (int j = 0; j < SIZE; j++)						//�л� : (�� ������ ������ ���)
	{
		var += pow(array[j] - avg, POWNUM);
	}
	var /= SIZE;
	std = sqrt(var);									// ǥ������ : ��л�

	printf("Total (%3d) integer data : \n\n", SIZE);	// �迭 ���
	printBigarraySample(array, SIZE, LINE_SIZE, 3);		//ū�迭 ���
	printf("MIN : (%.0lf), MAX : (%.0lf), AVG : (%5.2lf), VAR = (%5.2lf), STD : (%5.2lf) \n"\
		, min, max, avg, var, std);						//��� ���
}

void fgetArrayStatistics(FILE* fout, int* array, int SIZE) //���Ͽ� �迭 ���� ���� �Լ�, ���� �Ȱ���
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

void BigRandArray(int* array, int SIZE)					// ū���� ���� 
{
	char* flag = NULL;									// �ߺ��Ǵ� ���� ���� Ȯ���ϱ� ���� ������
	int count = 0;										// while �ʱ��
	unsigned int bigRand = 0;							// �ӽ����� ���� 2

	flag = (char*)calloc(SIZE, sizeof(char));			// �߻���ų ������ŭ �����޸� �Ҵ�
	if (flag == NULL)
	{
		printf("Error in Dynamic memory allocation for character array of size (%d)\n ", SIZE);
		exit(-1);
	}	//�굵 ���࿡ ���޴� ��Ȳ�� ���� �׳� �������Ѵ�.
	while (count < SIZE) //�߻���ų ������ŭ
	{
		// ���� RAND()�� �߻���Ű��, 15��Ʈ�� �ű���, �״���RAND()�� ���� OR�������� ����
		bigRand = (((unsigned int)rand() << 15) | rand()) % SIZE; 

		if (flag[bigRand] == 1)							// ���� bigRand�� �̹� ���� ������� �ٽý���
		{
			continue;
		}
		else
		{
			flag[bigRand] = 1;							// �ƴϸ� üũ���ְ�
			array[count++] = bigRand + OFFSET;			// array�� ���� ����������, count�� ++�Ѵ�.
		}
	}
	free(flag);											// �ٳ����� �����޸� ��ȯ����
}