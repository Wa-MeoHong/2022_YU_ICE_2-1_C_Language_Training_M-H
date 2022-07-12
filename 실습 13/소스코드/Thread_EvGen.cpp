#include "Thread.h"

using namespace std;								// ���ӽ����̽� std ���

void Thread_EventGenerator(T_P_Ev* pParam)			// �̺�Ʈ ������ ������ �Լ�
{
	Event* pEv; 

	// �ʱⰪ ����
	int event_no = 0;
	int event_pri = 0;
	int event_gen_count = 0;
	int myRole = pParam->myAddr;
	int myGenAddr = pParam->myAddr;
	int target_E_G = pParam->targetEventGen;
	DLL_EvQ* pEvQ;
	DLL_EvQ* priH_EvQ = pParam->EvQ_PriH;
	DLL_EvQ* priL_EvQ = pParam->EvQ_PriL;
	T_Stat* pThrdMon = pParam->pThrdMon;
	int maxround = pParam->maxRound;

	pParam->pCS_main->lock();						// �� �ɾ����
	printf("Thread_EventGenerator(%d) : targetEventGen(%d)\n", myGenAddr, target_E_G);
	pParam->pCS_main->unlock();						// �� ����

	for (int round = 0; round < maxround; round++)
	{
		if (event_gen_count < target_E_G)
		{
			// �̺�Ʈ ���� �� enqueue�� ���ش�.
			pEv = (Event*)calloc(1, sizeof(Event));
			pEv->ev_gen_addr = myGenAddr;
			pEv->ev_no = event_no = event_gen_count + (NUM_EV_PER_GEN * myGenAddr);
			pEv->ev_pri = rand() % NUM_PRIORITY;
			pEv->ev_han_addr = -1;					// �� �̺�Ʈ�� ���� �ڵ鸵 ���� ����
			QueryPerformanceCounter(&pEv->t_gen);	// ������ �ð� ����
			pEvQ = (pEv->ev_pri < PRIORITY_THRESHOLD) ? priH_EvQ : priL_EvQ;
			while (enDLL_EvQ(pEvQ, pEv) == NULL)	// enqueue �۾�
			{
				Sleep(100);
			}

			pParam->pCS_thrd_mon->lock();			// ������ ��
			// ������ �̺�Ʈ�� ��Ͽ� �迭�� �������
			pThrdMon->eventGen[myGenAddr]++;
			pThrdMon->ev_Generated[pThrdMon->total_G_E] = *pEv;
			pThrdMon->total_G_E++;
			pParam->pCS_thrd_mon->unlock();			// ������ ���
			event_gen_count++;
		}

		else
		{
			if (*(pThrdMon->pFlagThreadTerminated) == TERMINATE)
				break;								// �����尡 ��������̸� for���� Ż���Ѵ�.
		}
		Sleep(100 + rand() % 100);					// ������ �ش�.
	}
}