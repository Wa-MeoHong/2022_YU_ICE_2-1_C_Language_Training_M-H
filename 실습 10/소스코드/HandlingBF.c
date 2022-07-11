#include "HandlingBF.h"

void DumpBinaryFile(FILE* fin, FILE* fout)							// ������ ���� ������ ���
{
	int read_bytes;											// ���� ����Ʈ 
	
	int cus_pos;

	fseek(fin, 0, SEEK_END);								// ������ ���� ã��
	cus_pos = ftell(fin);									// �� ����(�����Ʈ)���� �˾Ƴ�
	rewind(fin);											// ó������ ���ư���

	for (int addr = 0; addr < cus_pos; addr += BUFFER_LEN)	// addr�� �ּ�(�޸�, ù ������ 0���� ����)
	// �׸��� 16����Ʈ�� ���۸� �о���� ������ �޸� �ּҸ� 16�� �����ش�.
	{
		unsigned char buffer[BUFFER_LEN] = { '\0' };		// ���۹迭 16����Ʈ (����Ʈ�� ������ �����Ƿ� unsigned ��)
		read_bytes = fread(buffer, sizeof(unsigned char), BUFFER_LEN, fin);
															// fread�Լ� (1����Ʈ��, 16���� �о �迭�� ����)
		if (read_bytes <= 0)								// �о�� ����Ʈ�� ���ٸ�( ������ ���� �����ų� ��) ����
			break;

		fprintf(fout, "%08X: ", addr);						// ���� �ּ� ��� 
		for (int i = 0; i < BUFFER_LEN; i++)
		{
			if (i == (BUFFER_LEN / 2))						// i == 8, 8��° ����Ʈ�϶���
				fprintf(fout, " ");
			if (buffer[i] == '\0')							// ���� ���� ���ڰ� ��� ����� ���ڰ� ���ٸ�(NULL) 
			{
				fprintf(fout, "    ");						// ��ĭ�� �����
			}
			else
				fprintf(fout, "%02X ", buffer[i]);			// 1byte = 8bit, 16������ 4bit�� �ϳ��� ���ڷ� ǥ�� ���� ���� 2���ڷ� 1����Ʈ�� ǥ�� �� �� ����
		}
		
		// 16����Ʈ�� ��� �����͸� ���� ����ߴ�.
		fprintf(fout, " ");
		for (int j = 0; j < read_bytes; j++)
		{
			if (isprint(buffer[j]))							// ���۾ȿ� �ִ� �� ���ڰ� �ƽ�Ű���ڷ� ǥ���� �� �ִ°�(����)
				fprintf(fout, "%c", buffer[j]);				// ���� ���
			else
				fprintf(fout, ".");							// �ƽ�Ű���ڷ� ǥ�� �Ұ����� ����(\t, \n ��)�� .���� ǥ��
		}
		fprintf(fout, "\n");								// 16����Ʈ�� ���� ��� ������ ��������Ƿ� ���� ������ ���� ��ĭ ����
	}
	rewind(fin);											// ������ ���� ��, ����Ŀ���� ó������ ���ư���
}

void Waiting()												// ��ٸ��� �Լ�
{
	for (int i = 0; i < 3; i++)
	{
		printf(" .");										// . ����
		Sleep(1000);										// ��� 1�ʵ��� ���
	}
	printf("\n");											// ����
}