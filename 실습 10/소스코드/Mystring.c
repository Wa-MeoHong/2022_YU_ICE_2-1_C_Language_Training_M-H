#include "Mystring.h"

char** fGetWords(FILE* fin, int* num_words, int NOW, int LOW) 
// �ܾ��� ����, ������ ������ �޾�, �迭 ���� �Ҵ� ��, ���Ͽ��� ���ڿ��� �о�� �迭�� ����ִ� �Լ�
// NOW : Number Of Words, LOW : Length of Word
{
	char** Words = NULL;										// �����Ҵ��� ���� ������ ����
	char FileWord[MAX_WORD_LEN] = { 0 };						// ���Ͽ��� �о�� �ܾ �޴� �ӽ� ���ڿ�
	int count = 0;												// �ܾ� ���� ���� ��

	Words = (char**)calloc(NOW, sizeof(char*));					// �����Ҵ� 1. NOW�� ��ŭ�� �ܾ� �迭�� ����
	for (int i = 0; i < NOW; i++)
	{
		Words[i] = (char*)calloc(LOW, sizeof(char));			// �����Ҵ� 2. �ִ� LOW��ŭ�� ���ڸ� ���� �� �ְ� �� �ܾ�� ũ���Ҵ�
	}

	while(fscanf(fin, "%s", FileWord) != EOF)					// �о�� ���ڿ��� FileWord�� ����, ������ ���� �����ϱ� ������
	{
			strcpy(Words[count], FileWord);						// �׸��� �迭�� ���ڿ��� ��������
			count++;
	}
	*num_words = count;											// ���� �ܾ� ���� ��ȯ 
	return Words;												// ���� �Ҵ�� �迭 �ּ� ��ȯ
}

void DeleteWords(char** Words, int NOW)							// �����Ҵ� ���� �Լ�
{
	for (int i = 0; i < NOW; i++)						// �� �����Ҵ� ����
		free(Words[i]);
	free(Words);										// ��ü �����Ҵ� ����
}

void PrintWords(FILE* fout, char** Words, int NoW)				// �ܾ ���Ͽ� ����ϴ� �Լ�
{
	for (int i = 0; i < NoW; i++)							// �� �� ��ŭ
	{
		if (i % 10 == 0)
		{
			printf("\n");
			fprintf(fout, "\n");
		}
		printf("%18s", Words[i]);							// ���
		fprintf(fout, "%18s", Words[i]);					// ���Ͽ� ���
	}

	//�ܾ���� ��� �־��ٴ� �ܼ� �޼��� ���
	printf("\n");
	fprintf(fout, "\n");
	printf("\n Words has been entered into sorted_Words.txt File!\n");
	printf(" Please Check sorted_Words.txt File.\n\n");
}

void SelectionSortWords(char** Words, int num_words)			// �ܾ� ���� ���� �Լ�
{
	char temp[MAX_WORD_LEN] = { 0 };						// �ܾ �ٲٱ� ���� �ӽ� ���ڿ� �迭
	int sort_IDX = 0, min_IDX = 0;							// ���� ���� �ε���, �ּҰ� �ε���

	// ��������
	while (1) 
	{
		if (sort_IDX == num_words)							// ���� ���� �ε����� �ܾ��� ������ŭ �ߴٸ� ����
			break;
		strcpy(temp, Words[sort_IDX]);						// ���� ���� �ε����� �ִ� �ܾ ����
		min_IDX = sort_IDX;									// �ּҰ� �ε��� �ʱⰪ ����

		for (int i = sort_IDX + 1; i < num_words; i++)		// ���� �����ε��� + 1���� �ܾ�迭 ������
		{
			if (strcmp(temp, Words[i]) == 1)				// ���� �ܾ temp���� ũ�ٸ�( �ƽ�Ű�ڵ� ���� )
			{
				strcpy(temp, Words[i]);						// �ּҰ� �ܾ� ����
				min_IDX = i;								// �ּҰ� �ε��� ����
			}
		}

		//�� �ٲٱ�
		strcpy(Words[min_IDX], Words[sort_IDX]); 
		strcpy(Words[sort_IDX], temp);
		sort_IDX++;											// ���� �ε��� ����
	}
}
