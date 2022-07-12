#include "Thread.h"
#include <Windows.h>
#include <time.h>
#include "PriQ_E.h"
#include "Event.h"

#define RANDOMIZE() srand((unsigned int)time(NULL))					// RANDOM

void Thread_EventGenerator(TPE* pParam)							// �����忡 ������ �̺�Ʈ�� �������
{
	PriQ* pPriQ_Event = pParam->pPriQ_Event;					// �켱���� ť�� �����ν� �ѹ� �����Ͽ� ���ϰ� ����غ���.

	// �̺�Ʈ �ʱⰪ ������ ����Ѵ�. ������ ���� ���ϰ� �����.
	int myRole = pParam->role;;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int event_gen_count = 0;
	T_Stat_M* pThrdMon = pParam->pThrdMon;						// �� ���� ���� ������ ����غ���.
	int targetEventGen = pParam->targetEventGen;				// Ÿ�ٵ� �̺�Ʈ
	Event* pEv;													// �̺�Ʈ ����

	RANDOMIZE();												// rand() �õ带 ���� ��ũ��

	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count >= targetEventGen)					// ������ �̺�Ʈ ī���Ͱ� targetEventGen�� �Ѿ�� 
		{	if (*pThrdMon->pFlagThreadTerminate == TERMINATE)	// ������ ����͸��� ����� ���¶�� �״�� ����
				break;
			else
			{
				Sleep(500);
				continue;
			}
		}

		// �̺�Ʈ ���� ��, �ʱⰪ�� ����
		pEv = (Event*)calloc(1, sizeof(Event)); 
		pEv->ev_gen = myAddr;
		pEv->ev_handler = -1;
		pEv->ev_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;
		pEv->ev_pri = targetEventGen - event_gen_count - 1;
		QueryPerformanceCounter(&pEv->ev_t_gen);				// �̺�Ʈ�� ������ �ð� ���
		pThrdMon->eventGenerated[pThrdMon->total_G_E] = *pEv;

		// �켱���� ť�� ������ �̺�Ʈ�� ����ִ´�.
		while (enPriQ(pPriQ_Event, *pEv) == NULL)
		{
			Sleep(500);
		}

		free(pEv);												// ������ �̺�Ʈ�� ���� �����Ҵ� ����( ����� �ּҰ��� �ٸ� ������ �����߱� ����)
		pParam->pMTX_thrd_mon->lock();							// �̺�Ʈ�� ����ϱ����� ���� mutex�� ������ó���� ���� LOCK����
		pThrdMon->num_G_E++;									// ������ �̺�Ʈ �� ����
		pThrdMon->total_G_E++;
		pParam->pMTX_thrd_mon->unlock();						// ó���� ������ ������ UNLOCK��Ŵ

		event_gen_count++;
		Sleep(10);
	}
}
