#include "PriQ_E.h"

bool hasLeftChild(int pos, PriQ* pPriQ_Ev)			// �θ��尡 ���� �ڽĳ�带 ������ �ִ°�?
{
	if (pos * 2 <= pPriQ_Ev->priQ_size)
		return true;
	else
		return false;
}

bool hasRightChild(int pos, PriQ* pPriQ_Ev)			// �θ��尡 ������ �ڽĳ�带 ������ �ִ°�?
{
	if (pos * 2 + 1 <= pPriQ_Ev->priQ_size)
		return true;
	else
		return false;
}

PriQ* initPriQ_Ev(PriQ* pPriQ_Ev, char* name, int capacity) // PriQ �ʱⰪ ����
{
	if (capacity == 0)						// capacity = ����Ʈ�� ť�� �ִ� �뷮
	{
		capacity = 1;
	}

	strcpy(pPriQ_Ev->PriQ_Name, name);		// ����Ʈ�� ť�� �̸�
	pPriQ_Ev->priQ_capacity = capacity;		// �뷮 
	pPriQ_Ev->pCBT_Ev = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event)); // �����Ҵ����� �� �ּ�
	pPriQ_Ev->priQ_size = 0;				// ����Ʈ�� ������(��� ����)
	pPriQ_Ev->pos_last = 0;					// ���� ������ ���

	return pPriQ_Ev;
}

void delPriQ_Ev(PriQ* pPriQ_Ev)						// �����Ҵ� ���� �Լ� 
{
	CBTN_Event* pCBTN_Ev;
	for (int i = 0; i < pPriQ_Ev->priQ_size; i++)
	{
		pCBTN_Ev = &(pPriQ_Ev->pCBT_Ev)[i];
		if (pCBTN_Ev != NULL)				// ���� �����Ҵ�� �̺�Ʈ �ּҰ� �����Ѵٸ�
		{
			if (pCBTN_Ev->pEv != NULL)
				free(pCBTN_Ev->pEv);		//�����Ҵ� ����
			free(pCBTN_Ev);					// �����Ҵ� ����
		}
	}
}

void enPriQ(PriQ* pPriQ_Ev, Event* pEv)				// ��� �߰� �Լ�
{
	int pos, pos_Parent;					// pos = �߰��� ����� ��ġ, pos_Parent
	CBTN_Event CBTN_Ev_tmp;					// ��� �߰� ��, �켱������ �ٲٱ� ���� ����

	if (pPriQ_Ev->priQ_size >= pPriQ_Ev->priQ_capacity) // ���� �뷮���� size�� �� ������
	{
		CBTN_Event* newCBT_E;
		int newCapacity;
		// ���Ӱ� �뷮�� Ȯ���Ѵ�. (2�� ũ���)

		newCapacity = 2 * pPriQ_Ev->priQ_capacity;		// ���ο� �뷮 ����
		// �����Ҵ�
		newCBT_E = (CBTN_Event*)calloc((newCapacity + 1), sizeof(CBTN_Event)); 
		if (newCBT_E == NULL)
		{
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!\n");
			exit(-1);
		}

		// ��� ������ ���Ӱ� ���� Ʈ���� �������ش�.
		for (int pos = 1; pos <= pPriQ_Ev->priQ_size; pos++)
		{
			newCBT_E[pos] = pPriQ_Ev->pCBT_Ev[pos];
		}
		free(pPriQ_Ev->pCBT_Ev);					// ������ ����Ʈ��ť�� �����Ҵ� ����
		pPriQ_Ev->pCBT_Ev = newCBT_E;				// ���Ӱ� ���� ����Ʈ��ť�� �ּҸ� ��ȯ
		pPriQ_Ev->priQ_capacity = newCapacity;		// �뷮�� ���Ӱ� ����
	}

	pos = ++(pPriQ_Ev->priQ_size);						// ���� ��尡 �߰��ʿ� ���� pos(������ ��� ��ġ)�� ����
	pPriQ_Ev->pCBT_Ev[pos].priority = pEv->event_pri;	// priority�� �߰�����
	pPriQ_Ev->pCBT_Ev[pos].pEv = pEv;					// �̺�Ʈ �޸� �ּҵ� ����

	while (pos != POS_ROOT)							// �߰��� ����� �켱������ ���� ���� ������ ���� ��ġ ������
	{
		pos_Parent = pos / 2;						// �ڽĳ�� = �θ��� * 2�̱� ����, ���� �ڽĳ�尡 �θ� *2 +1 �̿���, �������꿡 ���� �θ��尡 ����
		
		// ���� �θ��尡 �ڽĳ�庸�� �켱������ �۴ٸ�? �������� �ʴ´�
		if (pPriQ_Ev->pCBT_Ev[pos].priority >= pPriQ_Ev->pCBT_Ev[pos_Parent].priority)
		{
			break; 
		}
		else // �ƴϸ� �ٲ��ش�. (��������? �߰��� ����� ��ġ�� �ֻ��� ���(1)�� �ɶ�����)
		{
			CBTN_Ev_tmp = pPriQ_Ev->pCBT_Ev[pos_Parent];	// ��� �ӽú����� �̿��� ����
			pPriQ_Ev->pCBT_Ev[pos_Parent] = pPriQ_Ev->pCBT_Ev[pos];
			pPriQ_Ev->pCBT_Ev[pos] = CBTN_Ev_tmp;
			pos = pos_Parent;
		}
	}
}

Event* dePriQ(PriQ* pPriQ_Ev)							// �ֻ��� ��� ���� �Լ�
{
	Event* pEv;									// ������ ��带 ���� �ӽú���
	CBTN_Event CBTN_Ev_tmp;
	int pos, pos_last, pos_child;				// ������ ����

	if (pPriQ_Ev->priQ_size <= 0)				// ���� size�� 0���϶�� 
	{
		return NULL;							// Priority Queue �� �������. ���� �� ������ ����
	}

	pEv = pPriQ_Ev->pCBT_Ev[1].pEv;				// ���� �ֻ�����ġ�� �ִ� ����� ��ġ�� ������
	pos_last = pPriQ_Ev->priQ_size;				// ����������� �ε��� ��ġ�� ��������
	--pPriQ_Ev->priQ_size;						// ��� ������ 1�� �پ��� ������ ������ 1�� ����
	if (pPriQ_Ev->priQ_size > 0)
	{
		pPriQ_Ev->pCBT_Ev[POS_ROOT] = pPriQ_Ev->pCBT_Ev[pos_last]; //�ֻ��� ��忡 ������ ������ ��带 �ٿ��ֱ�
		pos_last--;								// ���� ������ ����� ��ġ�� ����

		// ���� �ֻ��� ��忡�� �켱���� ������
		pos = POS_ROOT;							// �ֻ��� ��Ʈ�� �Ʒ��� ������. ���� 1���� ����
		while (hasLeftChild(pos, pPriQ_Ev))		// �ڽĳ�尡 �ִ�? �Ʒ��� ������.
		{
			pos_child = pos * 2;				// �ڽĳ���� ��ġ ���� (�ڽ� ��� = �θ��� *2 (����))
			if (hasRightChild)					// ���� �����ʳ�嵵 ������
			{
				if (pPriQ_Ev->pCBT_Ev[pos_child].priority > pPriQ_Ev->pCBT_Ev[pos_child + 1].priority)
					pos_child = pos * 2 + 1;	// ���� ������ �ڽĳ�尡 ���� �ڽĳ�庸�� �켱������ ���ٸ� ���� �ڽĳ��� ���������� ����
			}

			// ����, �θ�,�ڽĳ�尣 �켱���� Ȯ�� �� ������
			if (pPriQ_Ev->pCBT_Ev[pos_child].priority < pPriQ_Ev->pCBT_Ev[pos].priority)
			//���� �ڽ��� �θ𺸴� �켱������ ���ٸ� ��ü
			{
				CBTN_Ev_tmp = pPriQ_Ev->pCBT_Ev[pos]; 
				pPriQ_Ev->pCBT_Ev[pos] = pPriQ_Ev->pCBT_Ev[pos_child];
				pPriQ_Ev->pCBT_Ev[pos_child] = CBTN_Ev_tmp;
			}
			else								// �ƴϸ� �ٷ� while�� ����
			{
				break;
			}
			pos = pos_child;					// �ٽ� �����Ǹ����� ���( �ֻ��� ��Ʈ���ٰ� ����������) ��ġ ã��
		}
	}
	return pEv;									// ��ȯ
}

void fprintPriQ(FILE* fout, PriQ* pPriQ_Ev)					// ���� ��� �Լ�
{
	int pos = 1, count = 1, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;

	if (pPriQ_Ev->priQ_size == 0)				// ���� size�� 0 �̶��(��尡 ���ٸ�)
	{
		fprintf(fout, "PriorityQueue_Event is empty !!\n");
		exit(-1);
	} // �ٷ� ����

	fprintf(fout, "\n CompBinTree :\n");			// ����Ʈ�� ���Ͽ� ���
	while (count <= pPriQ_Ev->priQ_size)
	{
		fprintf(fout, " level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count)		// ���� level_count �� ���ΰ����� ���� �ʾ�����.
		{
			pEv = pPriQ_Ev->pCBT_Ev[pos].pEv;		// �̺�Ʈ �ּ� ����
			eventPriority = pPriQ_Ev->pCBT_Ev[pos].priority; // �̺�Ʈ �켱���� ����
			fprintEvent(fout, pEv);					// ���
			pos++;
			count++;								// count(��� ���)
			if (count > pPriQ_Ev->priQ_size)		// ���� count �� size�� �ѱ�� ��
				break;
			count_per_line++; 
			if ((count_per_line % EVENT_PER_LINE) == 0) //���� 5���� ��µǾ��ٸ�
			{
				if (count_per_line < level_count)	// �� ��µ��� �ʾҴ�. 
					fprintf(fout, "\n\t");
				else								// �����ٸ�
					fprintf(fout, "\n");
			}
		}
		if ((count_per_line % EVENT_PER_LINE) != 0)
			fprintf(fout, "\n");
		level++;									// �ڽĳ��������� ���ٷ� ������
		level_count *= 2;							// �ڽĳ����� ���������� ������ 2���� ������ ������.
	}
	fprintf(fout, "\n");
}