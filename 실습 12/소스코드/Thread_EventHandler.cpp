#include "Thread.h"
#include <Windows.h>

#define RANDOMIZE() srand(time(NULL))

void Thread_EventHandler(TPE* pParam)						// �����忡�� �̺�Ʈ ó���ϴ� ������ ��� �Լ�
{
	Event* pEv;												// dequeue�� �̺�Ʈ�� ��� ����

	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	PriQ* pPriQ_Event = pParam->pPriQ_Event;
	T_Stat_M* pThrdMon = pParam->pThrdMon;
	int maxRound = pParam->maxRound;
	int targetEventGen = pParam->targetEventGen;
	// ����ü ���� pParam�� ���� ���� ���� ���·� �����ؼ� ��������ó�� ����Ѵ�.

	RANDOMIZE();

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)	// ������ ����͸��� ����� ���¶�� �״�� ����
			break;
		if ((pEv = dePriQ(pPriQ_Event)) != NULL)
		{
			pParam->pMTX_thrd_mon->lock();					// �̺�Ʈ�� ����ϱ����� ���� mutex�� ������ó���� ���� LOCK����
			QueryPerformanceCounter(&pEv->ev_t_handle);
			pEv->ev_handler = myAddr;
			pThrdMon->eventProcessed[pThrdMon->total_P_E] = *pEv;
			pThrdMon->num_P_E++;							// ó���� �̺�Ʈ �� ����
			pThrdMon->total_P_E++;
			pParam->pMTX_thrd_mon->unlock();				// ó���� ������ ������ UNLOCK��Ŵ
			free(pEv);										// dequeue���� �Ҵ��� pEv�� ������
		}
		Sleep(100 + rand() % 300);							// �ٱ����� �������� �Űܺ���.
	}
}