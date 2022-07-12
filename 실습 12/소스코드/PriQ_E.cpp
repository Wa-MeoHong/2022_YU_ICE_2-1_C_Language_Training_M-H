#include "PriQ_E.h"

bool hasLeftChild(int pos, PriQ* pPriQ_Ev)						// �θ��尡 ���� �ڽĳ�带 ������ �ִ°�?
{
	if (pos * 2 <= pPriQ_Ev->priQ_size)
		return true;
	else
		return false;
}

bool hasRightChild(int pos, PriQ* pPriQ_Ev)						// �θ��尡 ������ �ڽĳ�带 ������ �ִ°�?
{
	if (pos * 2 + 1 <= pPriQ_Ev->priQ_size)
		return true;
	else
		return false;
}

PriQ* initPriQ_Ev(PriQ* pPriQ_Ev, const char* name, int capacity = 1) // PriQ �ʱⰪ ����
{
	pPriQ_Ev->cs_PriQ.lock();

	strcpy(pPriQ_Ev->PriQ_Name, name);						// ����Ʈ�� ť�� �̸�
	pPriQ_Ev->priQ_capacity = capacity;						// �뷮 
	pPriQ_Ev->pCBT_Ev = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event)); // �����Ҵ����� �� �ּ�
	pPriQ_Ev->priQ_size = 0;								// ����Ʈ�� ������(��� ����)
	pPriQ_Ev->pos_last = 0;									// ���� ������ ���

	pPriQ_Ev->cs_PriQ.unlock();
	return pPriQ_Ev;
}

Event* enPriQ(PriQ* pPriQ_Ev, Event Ev)						// ��� �߰� �Լ�
{
	int pos, pos_Parent;									// pos = �߰��� ����� ��ġ, pos_Parent
	CBTN_Event CBTN_Ev_tmp;									// ��� �߰� ��, �켱������ �ٲٱ� ���� ����

	pPriQ_Ev->cs_PriQ.lock();								// ������ ��� 
	if (pPriQ_Ev->priQ_size >= pPriQ_Ev->priQ_capacity)		// ���� �뷮���� size�� �� ������
	{
		CBTN_Event* newCBT_E;
		int newCapacity;
		// ���Ӱ� �뷮�� Ȯ���Ѵ�. (2�� ũ���)

		newCapacity = 2 * pPriQ_Ev->priQ_capacity;			// ���ο� �뷮 ����
		newCBT_E = (CBTN_Event*)calloc((newCapacity + 1), sizeof(CBTN_Event)); // �����Ҵ�
		if (newCBT_E == NULL)
		{
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!\n");
			exit(-1);
		}

		for (int pos = 1; pos <= pPriQ_Ev->priQ_size; pos++)
		{
			newCBT_E[pos] = pPriQ_Ev->pCBT_Ev[pos];
		} //��� ������ ���Ӱ� ���� Ʈ���� �������ش�.
		free(pPriQ_Ev->pCBT_Ev);							// ������ ����Ʈ��ť�� �����Ҵ� ����
		pPriQ_Ev->pCBT_Ev = newCBT_E;						// ���Ӱ� ���� ����Ʈ��ť�� �ּҸ� ��ȯ
		pPriQ_Ev->priQ_capacity = newCapacity;				// �뷮�� ���Ӱ� ����
	}

	pos = pPriQ_Ev->pos_last = ++pPriQ_Ev->priQ_size;		// ���� ��尡 �߰��ʿ� ���� pos(������ ��� ��ġ)�� ����
	pPriQ_Ev->pCBT_Ev[pos].priority = Ev.ev_pri;			// priority�� �߰�����
	pPriQ_Ev->pCBT_Ev[pos].Ev = Ev;							// �̺�Ʈ �޸� �ּҵ� ����

	while (pos != POS_ROOT)									// �߰��� ����� �켱������ ���� ���� ������ ���� ��ġ ������
	{
		pos_Parent = pos / 2; // �ڽĳ�� = �θ��� * 2�̱� ����, ���� �ڽĳ�尡 �θ� *2 +1 �̿���, �������꿡 ���� �θ��尡 ����
		if (pPriQ_Ev->pCBT_Ev[pos].priority > pPriQ_Ev->pCBT_Ev[pos_Parent].priority)
		{
			break;											// ���� �θ��尡 �ڽĳ�庸�� �켱������ �۴ٸ�? �������� �ʴ´�
		}
		else							// �ƴϸ� �ٲ��ش�. (��������? �߰��� ����� ��ġ�� �ֻ��� ���(1)�� �ɶ�����
		{
			CBTN_Ev_tmp = pPriQ_Ev->pCBT_Ev[pos_Parent];	// ��� �ӽú����� �̿��� ����
			pPriQ_Ev->pCBT_Ev[pos_Parent] = pPriQ_Ev->pCBT_Ev[pos];
			pPriQ_Ev->pCBT_Ev[pos] = CBTN_Ev_tmp;
			pos = pos_Parent;
		}
	}
	pPriQ_Ev->cs_PriQ.unlock();								// ������ ��� ���� 
	return &(pPriQ_Ev->pCBT_Ev[pPriQ_Ev->pos_last].Ev);		// ��ȯ
}

Event* dePriQ(PriQ* pPriQ_Ev)								// �ֻ��� ��� ���� �Լ�
{
	Event* pEv;												// ������ ��带 ���� �ӽú���
	CBTN_Event CBTN_Ev_tmp;
	int pos, pos_last, pos_child;							// ������ ����

	if (pPriQ_Ev->priQ_size <= 0)							// ���� size�� 0���϶�� 
	{
		return NULL;										// Priority Queue �� �������. ���� �� ������ ����
	}

	pPriQ_Ev->cs_PriQ.lock();
	pEv = (Event*)calloc(1, sizeof(Event)); 

	*pEv = pPriQ_Ev->pCBT_Ev[POS_ROOT].Ev;					// ���� �ֻ�����ġ�� �ִ� ����� ��ġ�� ������
	pos_last = pPriQ_Ev->priQ_size;							// ����������� �ε��� ��ġ�� ��������
	--pPriQ_Ev->priQ_size;									// ��� ������ 1�� �پ��� ������ ������ 1�� ����
	if (pPriQ_Ev->priQ_size > 0)
	{
		pPriQ_Ev->pCBT_Ev[POS_ROOT] = pPriQ_Ev->pCBT_Ev[pos_last]; // �ֻ��� ��忡 ������ ������ ��带 �ٿ��ֱ�
		pos_last--;											// ���� ������ ����� ��ġ�� ����,

		// ���� �ֻ��� ��忡�� �켱���� ������
		pos = POS_ROOT;										// �ֻ��� ��Ʈ�� �Ʒ��� ������. ���� 1���� ����
		while (hasLeftChild(pos, pPriQ_Ev))					// �ڽĳ�尡 �ִ�? �Ʒ��� ������.
		{
			pos_child = pos * 2;							// �ڽĳ���� ��ġ ���� (�ڽ� ��� = �θ��� *2 (����))
			if (hasRightChild(pos, pPriQ_Ev))				// ���� �����ʳ�嵵 ������
			{
				if (pPriQ_Ev->pCBT_Ev[pos_child].priority > pPriQ_Ev->pCBT_Ev[pos_child + 1].priority)
					pos_child = pos * 2 + 1; 
				// ���� ������ �ڽĳ�尡 ���� �ڽĳ�庸�� �켱������ ���ٸ� ���� �ڽĳ��� ���������� ����
			}

			// ����, �θ�,�ڽĳ�尣 �켱���� Ȯ�� �� ������
			if (pPriQ_Ev->pCBT_Ev[pos_child].priority < pPriQ_Ev->pCBT_Ev[pos].priority) // ���� �ڽ��� �θ𺸴� �켱������ ���ٸ�
			{
				CBTN_Ev_tmp = pPriQ_Ev->pCBT_Ev[pos];		// ��ü
				pPriQ_Ev->pCBT_Ev[pos] = pPriQ_Ev->pCBT_Ev[pos_child];
				pPriQ_Ev->pCBT_Ev[pos_child] = CBTN_Ev_tmp;
			}
			else											// �ƴϸ� �ٷ� while�� ����
			{
				break;
			}
			pos = pos_child;								// �ٽ� �����Ǹ����� ���( �ֻ��� ��Ʈ���ٰ� ����������) ��ġ ã��
		}
	}
	pPriQ_Ev->cs_PriQ.unlock();								// ������ ��� ����
	return pEv;												// ��ȯ
}

void printPriQ(PriQ* pPriQ_Ev)								// ��� �Լ�
{
	int pos = 1, count = 1;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;

	if (pPriQ_Ev->priQ_size == 0)							// ���� size�� 0 �̶��(��尡 ���ٸ�)
	{
		printf("PriorityQueue_Event is empty !!\n");
		return;
	} // �ٷ� ����

	printf("\n CompBinTree :\n");							// ����Ʈ�� ���Ͽ� ���
	while (count <= pPriQ_Ev->priQ_size)
	{
		printf(" level%2d : ", level);
		for (int i = 0; i < level_count; i++)				// ���� level_count �� ���ΰ����� ���� �ʾ�����.
		{
			pEv = &(pPriQ_Ev->pCBT_Ev[pos].Ev);				// �̺�Ʈ �ּ� ����
			eventPriority = pEv->ev_pri;					// �̺�Ʈ �켱���� ����
			printEvent(pEv);								// ���
			pos++;
			if ((count % EVENT_PER_LINE) == 0)				// ���� 5���� ��µǾ��ٸ�
				printf("\n");
			count++;
			if (count > pPriQ_Ev->priQ_size)				// ���� count �� size�� �ѱ�� ��
				break;
		}
		printf("\n");
		level++;											// �ڽĳ��������� ���ٷ� ������
		level_count *= 2;									// �ڽĳ����� ���������� ������ 2���� ������ ������.
	}
	printf("\n");
}

/*void fprintPriQ(FILE* fout, PriQ* pPriQ_Ev)				// ���� ��� �Լ�
{
	int pos = 1, count = 1;
	int eventpriority;
	int level = 0, level_count = 1;
	event* pev;

	if (ppriq_ev->priq_size == 0)							// ���� size�� 0 �̶��(��尡 ���ٸ�)
	{
		fprintf(fout, "priorityqueue_event is empty !!\n");
		return;
	} // �ٷ� ����

	fprintf(fout, "\n compbintree :\n");					// ����Ʈ�� ���Ͽ� ���
	while (count <= ppriq_ev->priq_size)
	{
		fprintf(fout, " level%2d : ", level);
		for(int i = 0; i < level_count; i++)				// ���� level_count �� ���ΰ����� ���� �ʾ�����.
		{
			pev = &(ppriq_ev->pcbt_ev[pos].ev);				// �̺�Ʈ �ּ� ����
			eventpriority = pev->ev_pri;					// �̺�Ʈ �켱���� ����
			fprintevent(fout, pev);							// ���
			pos++;
			if ((count % event_per_line) == 0)				// ���� 5���� ��µǾ��ٸ�
				fprintf(fout, "\n");
			count++;
			if (count > ppriq_ev->priq_size)				// ���� count �� size�� �ѱ�� ��
				break;
		}
		fprintf(fout, "\n");
		level++;											// �ڽĳ��������� ���ٷ� ������
		level_count *= 2;									// �ڽĳ����� ���������� ������ 2���� ������ ������.
	}
	fprintf(fout, "\n");
}*/

void delPriQ_Ev(PriQ* pPriQ_Ev)								// �����Ҵ� ���� �Լ� 
{
	pPriQ_Ev->cs_PriQ.lock();								// ���ؽ� �ݱ�
	if (pPriQ_Ev->pCBT_Ev != NULL)
		free(pPriQ_Ev->pCBT_Ev);
	pPriQ_Ev->cs_PriQ.unlock();								// ���ؽ� ����
}