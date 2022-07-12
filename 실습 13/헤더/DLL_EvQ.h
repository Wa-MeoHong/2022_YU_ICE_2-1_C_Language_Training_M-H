#ifndef LinkedList_QUEUE_H
#define LinkedList_QUEUE_H

#include <Windows.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include "Event.h"
#include "SimParam.h"

using namespace std;

// �ڱ� ���� ����ü ������ ��� (DLLN)
typedef struct DLLN
{
	struct DLLN* next;							// �ڱ���������ü������ next (���� ��带 ����)
	struct DLLN* prev;							// �ڱ����� ����ü ������ prev ( ���� ��带 ����)
	Event* pEv;									// DLLN�ȿ� �ִ� �̺�Ʈ �ϳ�
} DLLN_Ev;

// �ڱ� ���� ����ü ������ ť
typedef struct DLL_Event_Queue
{
	mutex cs_EvQ;								// �� ť�� mutex (�����)
	int priority;								// �켱����
	DLLN_Ev* front;								// �� ť���� ���� �Ǿտ� �ִ� �ڱ����� ����ü
	DLLN_Ev* back;								// �� ť���� ���� �� �ڿ��ִ� �ڱ����� ����ü
	int num_Ev;									// �� ť���� �̺�Ʈ ����
} DLL_EvQ;

void initDLL_EvQ(DLL_EvQ* pEvQ, int pri);		// �̺�Ʈ ť �ʱⰪ ����
Event* enDLL_EvQ(DLL_EvQ* pEvQ, Event* pEv);	// enqueue�� �ڱ����� ����ü������ ����
Event* deDLL_EvQ(DLL_EvQ* pEvQ);				// dequeue�� �ڱ����� ����ü ������ ����
void printDLL_EvQ(DLL_EvQ* pEvQ);				// �̺�Ʈ ť ���

#endif // !LinkedList_QUEUE_H
