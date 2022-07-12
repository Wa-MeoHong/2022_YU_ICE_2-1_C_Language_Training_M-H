#ifndef THREAD_H
#define THREAD_H

#include "PriQ_E.h"
#include "SimulPara.h"
#define THREAD_RETURN_CODE 7

enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

// 스레드 상태 모니터링
typedef struct ThreadStatusMonitor 
{
	int num_G_E;								// 생성된 이벤트의 수
	int num_P_E;								// 처리된 이벤트의 수
	int total_G_E;								// 총 생성된 이벤트 수
	int total_P_E;								// 총 처리된 이벤트 수
	Event eventGenerated[TOTAL_NUM_EVENTS];		// used for monitoring only
	Event eventProcessed[TOTAL_NUM_EVENTS];		// used for monitoring only
	THREAD_FLAG* pFlagThreadTerminate;			// 현재상태
} T_Stat_M;

// 쓰레드 변수
typedef struct ThreadParam_Event
{
	mutex* pMTX_main;							// 메인 뮤텍스
	mutex* pMTX_thrd_mon;						// 스레드 뮤텍스 모니터링용
	PriQ* pPriQ_Event;							// 작업에 들어갈 큐
	ROLE role;									// 현재 스레드가 맡은 역할
	int myAddr;									// 현재 주소
	int maxRound;								// 최대 라운드
	int targetEventGen;							// 생성할 총 이벤트 개수
	T_Stat_M* pThrdMon;							// 스레드 상태
} TPE;

void Thread_EventGenerator(TPE* pParam);		// 이벤트 제너레이팅(생성)함수
void Thread_EventHandler(TPE* pParam);			// 이벤트 처리함수

#endif