#include "Thread.h"

using namespace std;								// 네임스페이스 std 사용

void Thread_EventHandler(T_P_Ev* pParam)			// 이벤트 생성기 쓰레드 함수
{
	// 초기값 설정
	int myRole = pParam->myAddr;
	int myProcAddr = pParam->myAddr;
	Event* pEv;
	DLL_EvQ* priH_EvQ = pParam->EvQ_PriH;
	DLL_EvQ* priL_EvQ = pParam->EvQ_PriL;
	T_Stat* pThrdMon = pParam->pThrdMon;
	int maxround = pParam->maxRound;
	Event* evProc = pParam->pThrdMon->ev_Processed;
	int target_E_G = pParam->targetEventGen;
	LARGE_INTEGER freq = pParam->freq;				// 아까 잰 클럭을 가져옴

	pParam->pCS_main->lock();						// 문 걸어잠금
	printf("Thread_EventHandler(%d) : targetEventGen(%d)\n", myProcAddr, target_E_G);
	pParam->pCS_main->unlock();						// 문 해제

	for (int round = 0; round < maxround; round++)
	{
		if (*(pThrdMon->pFlagThreadTerminated) == TERMINATE)
			break;									// 쓰레드가 종료상태이면 for문을 탈출한다.

		while ((pEv = deDLL_EvQ(priH_EvQ)) != NULL) // 우선순위가 높은 큐부터 진행
		{
			pParam->pCS_thrd_mon->lock();
			pEv->ev_han_addr = myProcAddr;
			QueryPerformanceCounter(&pEv->t_proc);
			calc_elapsed_time(pEv, freq);
			pThrdMon->ev_Processed[pThrdMon->total_P_E] = *pEv;
			pThrdMon->eventProc[myProcAddr]++;
			pThrdMon->total_P_E++;
			pThrdMon->num_P_E_H++;
			free(pEv);								// 처리된 이벤트는 삭제된다. (값은 배열에 복사되어있으므로 괜찮음)
			pParam->pCS_thrd_mon->unlock();
			Sleep(100 + rand() % 200);				// 슬립 줌(쓰레드 시간 맞추기)
		}
		if ((pEv = deDLL_EvQ(priL_EvQ)) != NULL)	// 우선순위가 낮은 큐부터 진행
		{
			pParam->pCS_thrd_mon->lock();
			pEv->ev_han_addr = myProcAddr;
			QueryPerformanceCounter(&pEv->t_proc);
			calc_elapsed_time(pEv, freq);
			pThrdMon->ev_Processed[pThrdMon->total_P_E] = *pEv;
			pThrdMon->eventProc[myProcAddr]++;
			pThrdMon->total_P_E++;
			pThrdMon->num_P_E_L++;
			free(pEv);								// 처리된 이벤트는 삭제된다. (값은 배열에 복사되어있으므로 괜찮음)
			pParam->pCS_thrd_mon->unlock();
		}
		Sleep(100 + rand() % 200);					// 슬립 줌(쓰레드 시간 맞추기)
	}
}