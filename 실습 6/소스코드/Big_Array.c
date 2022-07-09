
#include "Big_Array.h"

#define Randomize() srand((unsigned int)time(NULL))

void genBigRandArray(int* array, int SIZE, int offset)			// ū���� ����, (offset ~ SIZE ���� ����)
{
	char* flag = NULL;											// �ߺ��Ǵ� ���� ���� Ȯ���ϱ� ���� ������
	int count = 0;												// while �ʱ��
	unsigned int bigRand = 0;									// �ӽ����� ����

	Randomize();

	flag = (char*)calloc(SIZE + offset, sizeof(char));			// �߻���ų ������ŭ �����޸� �Ҵ�
	if (flag == NULL)
	{
		printf("Error in Dynamic memory allocation for character array of size (%d)\n ", SIZE);
		exit(-1);
	}	//�굵 ���࿡ ���޴� ��Ȳ�� ���� �׳� �������Ѵ�.

	while (count < SIZE)										// �߻���ų ������ŭ
	{
		bigRand = (((unsigned int)rand() << 15) | rand()) % SIZE;

		if (flag[bigRand] == 1)									// ���� bigRand�� �̹� ���� ������� 
		{
			continue;
		} 
		else
		{
			flag[bigRand] = 1;									// �ƴϸ� üũ���ְ�
			array[count++] = bigRand + offset;					// array�� ���� ����������, count�� ++�Ѵ�.
		}
	}
	free(flag);													// �ٳ����� �����޸� ��ȯ����
}

void printBigarraySample(int* array, int SIZE, int items_per_size, int num_sample_lines)
//ū �迭 ��� �Լ�(items_per_size = 10, num_sample_lines = 2)
{
	int count = 0;

	if (SIZE < Small_SIZE)										// ���� SIZE�� ���� �����
		num_sample_lines = SIZE / items_per_size + 1;			// ����� ���� num_~������ ��¿� �°� ��ģ��.
	for (int i = 0; i < num_sample_lines; i++)					// ó�� 20�� ���
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
	if (SIZE >= Small_SIZE)										// ū�������� �迭�̶�� �߰������� ���� ������ ó���Ѵ�.
	{
		printf("\n\t . . . . . .\n");
		count = SIZE - (items_per_size * num_sample_lines);		// count(�迭�ε��� ��ȣ)�� �ڿ��� 30��° ��ȣ�� �ٲٱ�

		for (int i = 0; i < num_sample_lines; i++)				// ������ 20�� ���
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

void SuffleBigArray(int* array, int SIZE)						// �迭 �����ֱ�
{
	int i1, i2, d;												// �������� ���� i1, i2, �׸��� �Űܴ��� �ӽ����庯�� d
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