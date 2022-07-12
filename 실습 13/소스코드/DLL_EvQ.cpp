#include "DLL_EvQ.h"

void initDLL_EvQ(DLL_EvQ* pEvQ, int pri)			// �̺�Ʈ ť �ʱⰪ ����
{
	pEvQ->cs_EvQ.lock();							// �̺�Ʈ ť ���ؽ� ��
	pEvQ->priority = pri;
	pEvQ->front = pEvQ->back = NULL;
	pEvQ->num_Ev = 0;
	pEvQ->cs_EvQ.unlock();							// �̺�Ʈ ť ���ؽ� ���
}

bool isEmpty(DLL_EvQ* pEvQ)
{
	if (pEvQ->num_Ev == 0)							// ���� �̺�Ʈ ������ 0�����
		return true;
	else
		return false;
}

Event* enDLL_EvQ(DLL_EvQ* pEvQ, Event* pEv)			// enqueue�� �ڱ����� ����ü������ ����
{	
	DLLN_Ev* pLN_Ev;
	if (pEv == NULL)								// ���� ������� �̺�Ʈ�� ���ٸ�
	{
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ... \n");
		getc(stdin);
		return NULL;
	}

	pLN_Ev = (DLLN_Ev*)calloc(1, sizeof(DLLN_Ev));
	if (pLN_Ev == NULL)								// �̺�Ʈ ��尡 �����Ҵ� ���� �ʾҴٸ�
	{
		printf("Error in enDLL_EvQ :: memory allocation for new DLLN failed !!\n");
		printf("Press any key to continue ... \n");
		getc(stdin);
		return NULL;
	}

	pLN_Ev->pEv = pEv;								// ��忡 �̺�Ʈ ����
	pEvQ->cs_EvQ.lock();							// ���
	if (pEvQ->num_Ev == 0)							// ���� �̺�Ʈ ������ 0�����
	{
		pEvQ->front = pEvQ->back = pLN_Ev;			// �̺�Ʈ ť ��,�ڴ� �̺�Ʈ ���� ����( 1���ۿ� �����ϱ�)
		pLN_Ev->prev = pLN_Ev->next = NULL;			// �̺�Ʈ ��� �յڷ� �ƹ��� ������ NULL
		pEvQ->num_Ev = 1;							// �̺�Ʈ ������ 1��
	}
	else											// �̺�Ʈ ������ 1�� �̻�
	{
		pLN_Ev->prev = pEvQ->back;					// �̺�Ʈ ��尡 �߰��ɶ��� �� �ڿ� �ٱ� ������ �̺�Ʈ ť �ǵ� (back)���� ����
		pEvQ->back->next = pLN_Ev;					// ���� �̺�Ʈ ť�� �ǵڿ� ���ο� �̺�Ʈ ��带 �̾��ش�. (next)
		pEvQ->back = pLN_Ev;						// ���ο� �̺�Ʈ ���� �̺�Ʈ ť�� back�� ����
		pLN_Ev->next = NULL;						// �� �� �̺�Ʈ ����� �״����� ���� ������ NULL
		pEvQ->num_Ev++;								// �̺�Ʈ ���� ����
	}
	pEvQ->cs_EvQ.unlock();							// �������
	return pLN_Ev->pEv;								// �̺�Ʈ�� ��ȯ( �߰��� �̺�Ʈ����� �̺�Ʈ )
}

Event* deDLL_EvQ(DLL_EvQ* pEvQ)						// dequeue�� �ڱ����� ����ü ������ ����
{
	Event* pEv;										// ó���� �̺�Ʈ
	DLLN_Ev* pLN_Ev_OldFront;						// ó���� �̺�Ʈ ��� (ť�� �� �պκ�)

	pEvQ->cs_EvQ.lock();							// ���
	if (pEvQ->num_Ev <= 0)							// ���� �̺�Ʈ ������ 0����� (ó���� �̺�Ʈ�� ����) 
	{
		pEvQ->cs_EvQ.unlock();						// �̺�Ʈ ������� �� �ٷ� Ż��
		return NULL;
	}
	else
	{
		pLN_Ev_OldFront = pEvQ->front;				// Dequeue �ϱ� �� �̺�Ʈ ť�� �� ó�� ��� �����͸� ����(��ȯ�� ���ؼ�)
		pEv = pEvQ->front->pEv;						// ó���� �̺�Ʈ�� ���� ����( ��ȯ�� ����)
		pEvQ->front = pEvQ->front->next;			// �̺�Ʈ ť�� front ������ ���(next)�� front�� �缳��
		if (pEvQ->front != NULL)					// �̺�Ʈ ť front �缳���� �Ǿ�����
			pEvQ->front->prev = NULL;				// �̺�Ʈ ť front�� �� �� �̺�Ʈ�� �����Ƿ� NULL�� ����
		pEvQ->num_Ev--;
		free(pLN_Ev_OldFront);						// ������ �̺�Ʈ ���� free���ָ鼭 ����
		pEvQ->cs_EvQ.unlock();
		return pEv;									// ����
	}
}

void printDLL_EvQ(DLL_EvQ* pEvQ)					// �̺�Ʈ ť ���
{
	int index = 0;
	int count;
	Event* pEv;
	DLLN_Ev* pLN_Ev;
	if (pEvQ == NULL)								// ���� ����� �̺�Ʈ ť�� ���ٸ�
	{
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ... \n");
		getc(stdin);
		return;
	}
	if (pEvQ->num_Ev <= 0)							// �̺�Ʈ ť�� ��� �̺�Ʈ�� ���ٸ�
		return;
	// ���
	pLN_Ev = pEvQ->front;							// �̺�Ʈ ť�� �� ó���� ��带 �ʱⰪ���� ������
	count = 0;
	while (pLN_Ev != NULL)
	{
		pEv = pLN_Ev->pEv;							// �̺�Ʈ ������ �̺�Ʈ�� �����ͼ�
		if (pEv == NULL)							// �̺�Ʈ�� ���ٸ�
			break;
		printEvent(pEv); printf(" ");				// �̺�Ʈ ���
		count++;
		if ((count % EVENT_PER_LINE) == 0)			// 5�� ����� �� ���� ����
			printf("\n\t");
		pLN_Ev = pLN_Ev->next;						// ���� ��带 ���� 
	}
}