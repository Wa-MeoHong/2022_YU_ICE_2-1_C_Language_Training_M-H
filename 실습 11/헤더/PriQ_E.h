#ifndef PRIQ_E_H
#define PRIQ_E_H

#include "Event.h"
#include <string.h>

#define POS_ROOT 1
#define MAX_NAME_LEN 80

// ����Ʈ�� �̺�Ʈ ��� ����ü
typedef struct CBTN_Event{
	int priority;
	Event* pEv;
}CBTN_Event;

// �켱���� ť ����ü
typedef struct PriorityQueue {
	char PriQ_Name[MAX_NAME_LEN];				// ť �̸�
	int priQ_capacity;							// ť�� �뷮
	int priQ_size;								// ����Ʈ�� ������(��� ����)
	int pos_last;								// ������ ���
	CBTN_Event* pCBT_Ev;						// �̺�Ʈ
} PriQ;

bool hasLeftChild(int pos, PriQ* pPriQ_Ev);						// �θ��尡 ���� �ڽĳ�带 ������ �ִ°�?
bool hasRightChild(int pos, PriQ* pPriQ_Ev);					// �θ��尡 ������ �ڽĳ�带 ������ �ִ°�?
PriQ* initPriQ_Ev(PriQ* pPriQ_Ev, char* name, int capacity);	// PriQ �ʱⰪ ����
void delPriQ_Ev(PriQ* pPriQ_Ev);								// �����Ҵ� ���� �Լ� 
void enPriQ(PriQ* pPriQ_Ev, Event* pEv);						// ��� �߰� �Լ�
Event* dePriQ(PriQ* pPriQ_Ev);									// �ֻ��� ��� ���� �Լ�
void fprintPriQ(FILE* fout, PriQ* pPriQ_Ev);					// ���� ��� �Լ�

#endif // !PRIQ_E_H
