#include "Thread.h"
#include <Windows.h>

#define RANDOMIZE() srand(time(NULL))

void Thread_EventHandler(TPE* pParam)						// 쓰레드에서 이벤트 처리하는 과정을 담는 함수
{
	Event* pEv;												// dequeue된 이벤트르 담는 변수

	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	PriQ* pPriQ_Event = pParam->pPriQ_Event;
	T_Stat_M* pThrdMon = pParam->pThrdMon;
	int maxRound = pParam->maxRound;
	int targetEventGen = pParam->targetEventGen;
	// 구조체 변수 pParam를 좀더 쓰기 쉬운 형태로 가공해서 지역변수처럼 사용한다.

	RANDOMIZE();

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)	// 쓰레드 모니터링이 종료된 상태라면 그대로 종료
			break;
		if ((pEv = dePriQ(pPriQ_Event)) != NULL)
		{
			pParam->pMTX_thrd_mon->lock();					// 이벤트를 기록하기전에 먼저 mutex로 쓰레드처리를 위해 LOCK을함
			QueryPerformanceCounter(&pEv->ev_t_handle);
			pEv->ev_handler = myAddr;
			pThrdMon->eventProcessed[pThrdMon->total_P_E] = *pEv;
			pThrdMon->num_P_E++;							// 처리된 이벤트 수 증가
			pThrdMon->total_P_E++;
			pParam->pMTX_thrd_mon->unlock();				// 처리가 끝나면 쓰레드 UNLOCK시킴
			free(pEv);										// dequeue에서 할당한 pEv를 해제함
		}
		Sleep(100 + rand() % 300);							// 바깥에서 안쪽으로 옮겨본다.
	}
}