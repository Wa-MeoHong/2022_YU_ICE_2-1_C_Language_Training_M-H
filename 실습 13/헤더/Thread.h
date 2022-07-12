#ifndef THREAD_H
#define THREAD_H

#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include "Event.h"
#include "SimParam.h"
#include "DLL_EvQ.h"

using namespace std;			// c++에서 사용되는 mutex, thread는 네임스페이스를 사용한다. 먼저 선언해주면 std를 붙일 필요 없음

typedef enum ROLE {	EVENT_GENERATOR, EVENT_HANDLER } ROLE;				// 쓰레드의 역할을 enum으로 정의
typedef enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE } THREAD_FLAG;	// 쓰레드 상태 

// 쓰레드 상태 모니터링 구조체
typedef struct ThreadStatMon 
{
	int eventGen[NUM_EVENT_GENERATORS];					// 제너레이터 아이디당 이벤트가 몇개 생성되었는가
	int eventProc[NUM_EVENT_HANDLERS];					// 핸들러 아이디
	int total_G_E;										// 총 생성된 이벤트 개수 (total generated events)
	int total_P_E;										// 총 처리된 이벤트 개수 (total processed events)
	int num_P_E_H;						// 우선순위 높은 이벤트들 중 처리된 이벤트 수 ( Number of Processed Event in High Priority)
	int num_P_E_L;						// 우선순위 낮은 이벤트들 중 처리된 이벤트 수 ( Number of Processed Event in Low Priority)
	THREAD_FLAG* pFlagThreadTerminated; // 이벤트가 terminated(종료) 되었는지 확인
	Event ev_Generated[TOTAL_NUM_EVENTS];				// 생성된 이벤트를 담는 배열
	Event ev_Processed[TOTAL_NUM_EVENTS];				// 처리된 이벤트를 담는 배열
} T_Stat; 

// 쓰레드의 파라미터 구조체
typedef struct ThreadParam_Event 
{
	FILE* fout;											// 출력용 파일 열기
	mutex* pCS_main;									// 메인함수에 쓸 mutex
	mutex* pCS_thrd_mon;								// 쓰레드에 쓸 mutex
	DLL_EvQ* EvQ_PriH;									// 우선순위가 높은 큐를 가져옴( 쓰레드에 담게 하기 위함)
	DLL_EvQ* EvQ_PriL;									// 우선순위가 낮은 큐를 가져옴( 이 또한 동일)
	ROLE role;											// 이 쓰레드의 역할 ( 이벤트 생성기, 이벤트 처리기 )
	int myAddr;
	int maxRound;
	int targetEventGen; 
	LARGE_INTEGER freq;									// 컴퓨터 CPU의 클럭 수 측정
	T_Stat* pThrdMon;									// 쓰레드의 상태 
} T_P_Ev;

void Thread_EventGenerator(T_P_Ev* pParam);				// 이벤트 생성기 쓰레드 함수
void Thread_EventHandler(T_P_Ev* pParam);				// 이벤트 처리기 쓰레드 함수

#endif // !THREAD_H
