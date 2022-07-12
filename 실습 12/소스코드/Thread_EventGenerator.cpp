#include "Thread.h"
#include <Windows.h>
#include <time.h>
#include "PriQ_E.h"
#include "Event.h"

#define RANDOMIZE() srand((unsigned int)time(NULL))					// RANDOM

void Thread_EventGenerator(TPE* pParam)							// 쓰레드에 생성된 이벤트를 집어넣음
{
	PriQ* pPriQ_Event = pParam->pPriQ_Event;					// 우선순위 큐를 변수로써 한번 지정하여 편하게 사용해본다.

	// 이벤트 초기값 설정시 사용한다. 변수를 보다 편리하게 사용함.
	int myRole = pParam->role;;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int event_gen_count = 0;
	T_Stat_M* pThrdMon = pParam->pThrdMon;						// 이 또한 편한 변수를 사용해본다.
	int targetEventGen = pParam->targetEventGen;				// 타겟된 이벤트
	Event* pEv;													// 이벤트 변수

	RANDOMIZE();												// rand() 시드를 위한 매크로

	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count >= targetEventGen)					// 생성된 이벤트 카운터가 targetEventGen가 넘어가면 
		{	if (*pThrdMon->pFlagThreadTerminate == TERMINATE)	// 쓰레드 모니터링이 종료된 상태라면 그대로 종료
				break;
			else
			{
				Sleep(500);
				continue;
			}
		}

		// 이벤트 생성 후, 초기값을 설정
		pEv = (Event*)calloc(1, sizeof(Event)); 
		pEv->ev_gen = myAddr;
		pEv->ev_handler = -1;
		pEv->ev_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;
		pEv->ev_pri = targetEventGen - event_gen_count - 1;
		QueryPerformanceCounter(&pEv->ev_t_gen);				// 이벤트가 생성된 시간 기록
		pThrdMon->eventGenerated[pThrdMon->total_G_E] = *pEv;

		// 우선순위 큐에 생성된 이벤트를 집어넣는다.
		while (enPriQ(pPriQ_Event, *pEv) == NULL)
		{
			Sleep(500);
		}

		free(pEv);												// 생성한 이벤트를 이제 동적할당 해제( 만들고 주소값과 다른 정보를 저장했기 떄문)
		pParam->pMTX_thrd_mon->lock();							// 이벤트를 기록하기전에 먼저 mutex로 쓰레드처리를 위해 LOCK을함
		pThrdMon->num_G_E++;									// 생성된 이벤트 수 증가
		pThrdMon->total_G_E++;
		pParam->pMTX_thrd_mon->unlock();						// 처리가 끝나면 쓰레드 UNLOCK시킴

		event_gen_count++;
		Sleep(10);
	}
}
