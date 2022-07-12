#include "Thread.h"

using namespace std;								// ���ӽ����̽� std ���

void Thread_EventHandler(T_P_Ev* pParam)			// �̺�Ʈ ������ ������ �Լ�
{
	// �ʱⰪ ����
	int myRole = pParam->myAddr;
	int myProcAddr = pParam->myAddr;
	Event* pEv;
	DLL_EvQ* priH_EvQ = pParam->EvQ_PriH;
	DLL_EvQ* priL_EvQ = pParam->EvQ_PriL;
	T_Stat* pThrdMon = pParam->pThrdMon;
	int maxround = pParam->maxRound;
	Event* evProc = pParam->pThrdMon->ev_Processed;
	int target_E_G = pParam->targetEventGen;
	LARGE_INTEGER freq = pParam->freq;				// �Ʊ� �� Ŭ���� ������

	pParam->pCS_main->lock();						// �� �ɾ����
	printf("Thread_EventHandler(%d) : targetEventGen(%d)\n", myProcAddr, target_E_G);
	pParam->pCS_main->unlock();						// �� ����

	for (int round = 0; round < maxround; round++)
	{
		if (*(pThrdMon->pFlagThreadTerminated) == TERMINATE)
			break;									// �����尡 ��������̸� for���� Ż���Ѵ�.

		while ((pEv = deDLL_EvQ(priH_EvQ)) != NULL) // �켱������ ���� ť���� ����
		{
			pParam->pCS_thrd_mon->lock();
			pEv->ev_han_addr = myProcAddr;
			QueryPerformanceCounter(&pEv->t_proc);
			calc_elapsed_time(pEv, freq);
			pThrdMon->ev_Processed[pThrdMon->total_P_E] = *pEv;
			pThrdMon->eventProc[myProcAddr]++;
			pThrdMon->total_P_E++;
			pThrdMon->num_P_E_H++;
			free(pEv);								// ó���� �̺�Ʈ�� �����ȴ�. (���� �迭�� ����Ǿ������Ƿ� ������)
			pParam->pCS_thrd_mon->unlock();
			Sleep(100 + rand() % 200);				// ���� ��(������ �ð� ���߱�)
		}
		if ((pEv = deDLL_EvQ(priL_EvQ)) != NULL)	// �켱������ ���� ť���� ����
		{
			pParam->pCS_thrd_mon->lock();
			pEv->ev_han_addr = myProcAddr;
			QueryPerformanceCounter(&pEv->t_proc);
			calc_elapsed_time(pEv, freq);
			pThrdMon->ev_Processed[pThrdMon->total_P_E] = *pEv;
			pThrdMon->eventProc[myProcAddr]++;
			pThrdMon->total_P_E++;
			pThrdMon->num_P_E_L++;
			free(pEv);								// ó���� �̺�Ʈ�� �����ȴ�. (���� �迭�� ����Ǿ������Ƿ� ������)
			pParam->pCS_thrd_mon->unlock();
		}
		Sleep(100 + rand() % 200);					// ���� ��(������ �ð� ���߱�)
	}
}