#include "Thread.h"

using namespace std;								// 네임스페이스 std 사용

void Thread_EventGenerator(T_P_Ev* pParam)			// 이벤트 생성기 쓰레드 함수
{
	Event* pEv; 

	// 초기값 설정
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

	pParam->pCS_main->lock();						// 문 걸어잠금
	printf("Thread_EventGenerator(%d) : targetEventGen(%d)\n", myGenAddr, target_E_G);
	pParam->pCS_main->unlock();						// 문 해제

	for (int round = 0; round < maxround; round++)
	{
		if (event_gen_count < target_E_G)
		{
			// 이벤트 생성 후 enqueue를 해준다.
			pEv = (Event*)calloc(1, sizeof(Event));
			pEv->ev_gen_addr = myGenAddr;
			pEv->ev_no = event_no = event_gen_count + (NUM_EV_PER_GEN * myGenAddr);
			pEv->ev_pri = rand() % NUM_PRIORITY;
			pEv->ev_han_addr = -1;					// 이 이벤트는 아직 핸들링 되지 않음
			QueryPerformanceCounter(&pEv->t_gen);	// 생성된 시간 측정
			pEvQ = (pEv->ev_pri < PRIORITY_THRESHOLD) ? priH_EvQ : priL_EvQ;
			while (enDLL_EvQ(pEvQ, pEv) == NULL)	// enqueue 작업
			{
				Sleep(100);
			}

			pParam->pCS_thrd_mon->lock();			// 쓰레드 락
			// 생성된 이벤트를 기록용 배열에 집어넣음
			pThrdMon->eventGen[myGenAddr]++;
			pThrdMon->ev_Generated[pThrdMon->total_G_E] = *pEv;
			pThrdMon->total_G_E++;
			pParam->pCS_thrd_mon->unlock();			// 쓰레드 언락
			event_gen_count++;
		}

		else
		{
			if (*(pThrdMon->pFlagThreadTerminated) == TERMINATE)
				break;								// 쓰레드가 종료상태이면 for문을 탈출한다.
		}
		Sleep(100 + rand() % 100);					// 슬립을 준다.
	}
}