#include "CirQ_E.h"

CirQ* initCirQ(CirQ* pCirQ, int capacity)				// CirQ ����ü �ڷ��� �ʱⰪ ����
{
	Event* pEv;

	pEv = (Event*)calloc(capacity, sizeof(Event));		// ���� �Ҵ�

	if (pEv == NULL)									// ���� �Ҵ� ���н� ���� �޼��� ���
	{
		printf("ERROR!! Not Generated Events in memory\n");
		exit(-1);
	}

	//�ʱⰪ ����
	pCirQ->pEv = pEv;
	pCirQ->capacity = capacity;
	pCirQ->front = pCirQ->end = 0;
	pCirQ->num_elements = 0;
	return pCirQ;
}

void fprintCirQ(FILE* fout, CirQ* pCirQ)				// ȯ��ť ��Ȳ ���� ��� �Լ�
{
	Event ev;											// �̺�Ʈ ( fprintEvent�Լ����� ���� ���� ����)
	int index;											// ȯ��ť���� �̺�Ʈ�� ����

	fprintf(fout, " %2d Elements in CirQ_Event (index_front:%2d) :\n", pCirQ->num_elements, pCirQ->front);
	// ȯ��ť�ȿ� �ִ� �̺�Ʈ ����, ȯ�� ť���� �� ó�� �̺�Ʈ�� �ε��� ��ȣ ��� 

	if (isCirQEmpty(pCirQ))								// ȯ��ť�� ����ִ°�? ��������� ���
	{
		fprintf(fout, "pCirQ_Event is Empty"); 
	}
	else // �ƴϸ�
	{
		fprintf(fout, "\t");
		for (int i = 0; i < pCirQ->num_elements; i++)	// ȯ�� ť �ȿ� �ִ� �̺�Ʈ�� ���� ������ ��� ���
		{
			index = pCirQ->front + i;				// ȯ��ť �ȿ��� �� ù��° �̺�Ʈ�� �ִ°��� ��ġ�� �������� �ε��� ��ȣ�� ���ϸ鼭 ��ġ ����
			if (index >= pCirQ->capacity)			// ���� �ε��� ��ȣ�� �ִ�ġ(capacity)�� �ȴٸ�
				// ������ capacity - 1���� ȯ��ť �迭�� �����Ǳ� �����̴�. �ε�����ȣ == capacity �� ��, �������� 0�� �ȴ�.
				index %= pCirQ->capacity;			// �ε�����ȣ 0���� �ʱ�ȭ���ش�.

			ev = pCirQ->pEv[index];					// ȯ�� ť ���� �̺�Ʈ�� ��, �ε��� ��ȣ�� �´� �̺�Ʈ�� ������
			fprintEvent(fout, &ev);					// ���� ���
			if ((i + 1) % EVENT_PER_LINE == 0 && (i + 1) != pCirQ->num_elements) 
				fprintf(fout, "\n\t");				// 5��° �̺�Ʈ�� ����Ҷ����� �ٹٲ��� ��
		}
		fprintf(fout, "\n");						//��� �� ����� ������ �ٹٲ��� �ѹ� ���ش�. (����)
	}
}

bool isCirQFull(CirQ* pCirQ)					// ȯ�� ť�� �̺�Ʈ ������ �ִ�ġ(capacity)�� �����ߴ°�?
{
	if (pCirQ->num_elements == pCirQ->capacity)
		return true;
	else
		return false;
}

bool isCirQEmpty(CirQ* pCirQ)					// ȯ�� ť�� �̺�Ʈ ������ 0�� �ΰ�?
{
	if (pCirQ->num_elements == 0)
		return true;
	else
		return false;
}

Event* enCirQ(CirQ* pCirQ, Event ev)				// ȯ��ť���� �̺�Ʈ �߰�( FIFO�̱� ������ �ټ��°� ó�� �������� �߰���)
{
	if (isCirQFull(pCirQ))				//ȯ�� ť�� �� á�ٸ�?
	{
		return NULL;					// enqueue ����
	}
	//if���� return�� ���ϱ� ������ ���� else�� �Ⱥٿ��� ��. �ֳ��ϸ� if�� ������ �Լ��� ����

	pCirQ->pEv[pCirQ->end] = ev; 
	// ȯ�� ť �ȿ��� ������ ��ȣ(end = �����ϴ� �̺�Ʈ�� �ٷ� ������ȣ)�� �ִ� ��ġ�� �̺�Ʈ�� ����
	pCirQ->num_elements++;						// ȯ��ť ���� �ִ� �̺�Ʈ ���� ����
	pCirQ->end++;								// end��ȣ ����
	if (pCirQ->end == pCirQ->capacity)			// ���� end��ȣ�� capacity�� �ȴٸ�( ȯ�� ť ���� �̺�Ʈ �ε��� ��ȣ 0~capacity -1
	{
		pCirQ->end = pCirQ->end % pCirQ->capacity; // end�� 0������ �̵��Ѵ�
	}

	return &(pCirQ->pEv[pCirQ->end]);			// ������ �̺�Ʈ �ּ� ��ȯ
}

Event* deCirQ(CirQ* pCirQ)							// ȯ��ť���� �̺�Ʈ ���̱�(FIFO�̱� ������ front�� �ڷ� �и�)
{
	if (isCirQEmpty(pCirQ))						// ȯ��ť�� �̺�Ʈ�� �ƿ� ���°�?
	{
		return NULL;							// �̺�Ʈ ���̱Ⱑ �Ұ�����
	}

	Event* pEv = &(pCirQ->pEv[pCirQ->front]);	// �� ó���� �ִ�(front) �̺�Ʈ�� �����´�.
	pCirQ->front++;								// �̺�Ʈ �� ó�� ����
	if (pCirQ->front == pCirQ->capacity)		// ���������� capacity�� �����Ѵٸ�
		pCirQ->front = pCirQ->front % pCirQ->capacity; // 0���� �������
	pCirQ->num_elements--;						// �̺�Ʈ ���� ����( 1���� �پ��)

	return pEv;									// �Ʊ� ���� �̺�Ʈ ��ȯ
}

void delCirQ(CirQ* pCirQ)							// ȯ�� ť �����Ҵ� ���� �Լ� (��� ���� ���� ��, ����)
{
	if (pCirQ->pEv != NULL)						// �̺�Ʈ�� �޸��ּҰ� �����Ѵٸ� pEv�� ��������
		free(pCirQ->pEv);						// ����? Init���� �����Ҵ��� �߱� ����
	pCirQ->pEv = NULL; 
	pCirQ->num_elements = 0;
	pCirQ->front = pCirQ->end = 0;
	pCirQ->num_elements = 0;
}