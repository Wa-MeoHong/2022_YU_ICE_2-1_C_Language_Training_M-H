/*
  파일명 : "실습13_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 자기참조 구조체를 이용해서 우선순위 큐를 쓰레드를 멀티로 굴리는 프로그램

  프로그램 작성자 : 신대홍(2022년 5월 31일)
  최종 Update : Version 1.1.0, 2022년 6월 1일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/05/31		v1.0.0		  최초 작성
	신대홍		 2022/06/01		v1.1.0		  코드 완성

===========================================================================================================
*/

#include "Event.h"
#include "Thread.h"
#include "DLL_EvQ.h"
#include "ConsoleDisplay.h"
#include <time.h>
#define random() srand((unsigned int)time(NULL))

using namespace std;

int main(void)
{
	DLL_EvQ dll_EvQ_PriH, dll_EvQ_PriL;						// 우선순위 High, Low 이벤트 큐 두개
	Event* pEv;												// 이벤트 변수
	int myAddr = 0;
	//int ev_hand_add, ev_prior;							// 이벤트 핸들링 주소, 우선순위
	LARGE_INTEGER freq;										// 컴퓨터 클럭수 측정

	initDLL_EvQ(&dll_EvQ_PriH, 0);							// 이벤트 우선순위 큐 초기값 설정
	initDLL_EvQ(&dll_EvQ_PriL, 1);

	random();

	// 이벤트 쓰레드 파라미터 초기값 설정
	T_P_Ev thrdP_E_Gen[NUM_EVENT_GENERATORS];				// 이벤트 제너레이터 쓰레드 파라미터들
	T_P_Ev thrdP_E_Han[NUM_EVENT_HANDLERS];					// 이벤트 핸들러 쓰레드 파라미터

	thread thrd_evHans[NUM_EVENT_HANDLERS];					// 쓰레드 변수 (이벤트 핸들러 0번, 1번)
	thread thrd_evGens[NUM_EVENT_GENERATORS];				// 쓰레드 변수 (이벤트 제너레이터 0번, 1번, 2번)

	mutex cs_main, cs_thrd_mon;								// mutex 변수 메인용, 쓰레드 모니터링 용
	T_Stat thrdMon;											// 쓰레드 모니터링 변수

	HANDLE consHandler;										// 콘솔창 핸들링용 HANDLE 변수
	THREAD_FLAG eventThreadFlag = RUN;						// 쓰레드의 현재 상태
	int count, total_Event_Gen = 0, total_Event_Proc = 0;

	consHandler = initConsoleHandler();						// 콘솔창 초기값 설정
	QueryPerformanceFrequency(&freq);						// 시간을 재기위한 클럭 측정

	// 쓰레드 모니터링 변수 초기화
	thrdMon.pFlagThreadTerminated = &eventThreadFlag;		// 쓰레드 상태를 원본과 연동
	thrdMon.total_G_E = 0, thrdMon.total_P_E = 0; 
	thrdMon.num_P_E_H = 0, thrdMon.num_P_E_L = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.ev_Processed[ev].ev_no = -1;
		thrdMon.ev_Processed[ev].ev_pri = -1;
	}

	// 이벤트 핸들러 쓰레드 생성
	// 먼저 이벤트 핸들러 쓰레드들의 값을 초기화
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thrdMon.eventProc[p] = 0;							// 이벤트 핸들러 주소
		thrdP_E_Han[p].fout = NULL;							// 출력 파일 주소
		thrdP_E_Han[p].role = EVENT_HANDLER;				// 이 쓰레드의 역할은? 이벤트 핸들러
		thrdP_E_Han[p].myAddr = p;							// 이벤트 핸들러 번호
		thrdP_E_Han[p].pCS_main = &cs_main, thrdP_E_Han[p].pCS_thrd_mon = &cs_thrd_mon; // mutex를 연결
		thrdP_E_Han[p].EvQ_PriH = &dll_EvQ_PriH;			// 우선순위 높은 큐를 연결
		thrdP_E_Han[p].EvQ_PriL = &dll_EvQ_PriL;			// 우선순위 낮은 큐 연결
		thrdP_E_Han[p].maxRound = MAX_ROUND;				// 최대 라운드수 설정
		thrdP_E_Han[p].pThrdMon = &thrdMon;					// 쓰레드 모니터링 변수 연결
		thrdP_E_Han[p].freq = freq;							// 클럭 주파수 대입

		thrd_evHans[p] = thread(Thread_EventHandler, &thrdP_E_Han[p]); // 이벤트 처리기 쓰레드 생성( 번호에 맞게)
		printf("%d-th Thread_EventHandler is created and activated (id : %d)\n", p + 1, thrd_evHans[p].get_id());
		// 몇번째 이벤트 처리 쓰레드가 생성되었는지 출력
	}

	// 이벤트 제너레이터 쓰레드 생성
	// 먼저 이벤트 제너레이터 쓰레드들의 값을 초기화
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thrdMon.eventGen[g] = 0;							// 이벤트 핸들러 주소
		thrdP_E_Gen[g].fout = NULL;							// 출력 파일 주소
		thrdP_E_Gen[g].role = EVENT_GENERATOR;				// 이 쓰레드의 역할은? 이벤트 제너레이터
		thrdP_E_Gen[g].myAddr = g;							// 이벤트 제너레이터 번호
		thrdP_E_Gen[g].pCS_main = &cs_main, thrdP_E_Gen[g].pCS_thrd_mon = &cs_thrd_mon; // mutex를 연결
		thrdP_E_Gen[g].EvQ_PriH = &dll_EvQ_PriH;			// 우선순위 높은 큐를 연결
		thrdP_E_Gen[g].EvQ_PriL = &dll_EvQ_PriL;			// 우선순위 낮은 큐 연결
		thrdP_E_Gen[g].targetEventGen = NUM_EV_PER_GEN;
		thrdP_E_Gen[g].maxRound = MAX_ROUND;				// 최대 라운드수 설정
		thrdP_E_Gen[g].pThrdMon = &thrdMon;					// 쓰레드 모니터링 변수 연결
		thrdP_E_Gen[g].freq = freq;							// 클럭 주파수 대입

		thrd_evGens[g] = thread(Thread_EventGenerator, &thrdP_E_Gen[g]); // 이벤트 생성기 쓰레드 생성( 번호에 맞게)
		printf("%d-th Thread_EventGenerator is created and activated (id : %d)\n", g + 1, thrd_evGens[g].get_id());
		// 몇번째 이벤트 처리 쓰레드가 생성되었는지 출력
	}

	// 쓰레드 모니터링 (한번 돌때마다)
	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();										// mutex로 다른 쓰레드가 값을 침범하지 못하도록 막는다. (이벤트 배열들)
		system("cls");
		gotoxy(consHandler, 0, 0);							// 콘솔창을 초기화 시키기 위함
		printf("Thread monitoring by main() :: round(%2d): \n", round);
		cs_thrd_mon.lock();									// 쓰레드도 걸어잠근다.

		// 이벤트 생성기 쓰레드가 동작해서 이벤트가 생성된 상태를 출력
		for (int i = 0; i < NUM_EVENT_GENERATORS; i++)
		{
			printf("\tEvent_Gen[%d] generated %2d events.\n", i, thrdMon.eventGen[i]);
		}

		printf("Event_Generators have generated total %2d events\n", thrdMon.total_G_E);
		total_Event_Gen = thrdMon.total_G_E;
		printf("\nTotal Generated Events (current total %d events)\n\t", total_Event_Gen); // 총 몇개가 생성되었는가
		// 생성된 이벤트의 값 출력
		for (int ev = 0; ev < total_Event_Gen; ev++)
		{
			pEv = &thrdMon.ev_Generated[ev];				// 생성된 이벤트배열(각 쓰레드에서 생성한 이벤트들)을 가져옴
			if (pEv != NULL)								// 이벤트가 정상적으로 가져와졌으면
			{
				printEvent(pEv);							// 출력
				if ((ev + 1) % EVENT_PER_LINE == 0)			// 1줄당 이벤트가 다섯개씩 출력이 되면
					printf("\n\t");
			}
		}
		printf("\n"); 

		// 생성된 이벤트를 처리함 (이벤트 처리기 쓰레드 동작)
		printf("\nEvent_Handlers have processed total %2d events\n", thrdMon.total_P_E);
		printf("(Evnet_PriH (%2d), Event_PriL (%2d))\n", thrdMon.num_P_E_H, thrdMon.num_P_E_L);
		for (int i = 0; i < NUM_EVENT_HANDLERS; i++)
		{
			printf("\t Event_Proc[%d] processed %2d events\n", i, thrdMon.eventProc[i]);
		}
		printf("\nDLL_EvQ_PriH (%3d events):\n\t", dll_EvQ_PriH.num_Ev);
		printDLL_EvQ(&dll_EvQ_PriH);
		printf("\nDLL_EvQ_PriL (%3d events):\n\t", dll_EvQ_PriL.num_Ev);
		printDLL_EvQ(&dll_EvQ_PriL);
		printf("\n");
		total_Event_Proc = thrdMon.total_P_E;
		printf("\nTotal Processed Events (Current total %d events):\n\t", total_Event_Proc);

		count = 0;
		// 처리된 이벤트의 값 출력
		for (int ev = 0; ev < total_Event_Proc; ev++)
		{
			pEv = &thrdMon.ev_Processed[ev];				// 생성된 이벤트배열(각 쓰레드에서 생성한 이벤트들)을 가져옴
			if (pEv != NULL)								// 이벤트가 정상적으로 가져와졌으면
			{
				printEvent(pEv);							// 출력
				if ((ev + 1) % EVENT_PER_LINE == 0)			// 1줄당 이벤트가 다섯개씩 출력이 되면
					printf("\n\t");
			}
		}
		printf("\n");
		cs_thrd_mon.unlock();								// 쓰레드 잠금해제
		if (total_Event_Proc >= TOTAL_NUM_EVENTS)			// 모든 이벤트가 처리가 완료되었으면
		{
			printf("!!! TotalEventProcessed (%d) is reached to target TOTAL_NUM_EVENT(%d)\n",
				total_Event_Proc, TOTAL_NUM_EVENTS);
			eventThreadFlag = TERMINATE;					// 모든 쓰레드를 종료시키기 위해 eventThreadFlag를 종료상태로 전환한다.
			cs_main.unlock();								// 메인 쓰레드 언락
			break;											// 반복문 탈출
		}
		cs_main.unlock();									// 쓰레드 언락
		Sleep(100);
	}														// 이벤트 생성, 처리 반복문 

	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thrd_evHans[p].join();								// 이벤트 처리기 쓰레드 조인
	}
	printf("All threads of Event_Handlers are terminated !!\n");

	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thrd_evGens[g].join();								// 이벤트 생성기 쓰레드 조인
	}
	printf("All threads of Event_Generators are terminated !!\n");

	// 이벤트 생성~처리까지 걸린 시간 측정, 최대, 최소, 평균 시간 측정
	double min, max, avg, sum;
	int min_ev, max_ev;
	min = max = sum = thrdMon.ev_Processed[0].elapsed;
	min_ev = max_ev = 0;
	for (int i = 0; i < TOTAL_NUM_EVENTS; i++)
	{
		sum += thrdMon.ev_Processed[i].elapsed;
		if (min > thrdMon.ev_Processed[i].elapsed)
		{
			min = thrdMon.ev_Processed[i].elapsed;
			min_ev = i;
		}
		if (max < thrdMon.ev_Processed[i].elapsed)
		{
			max = thrdMon.ev_Processed[i].elapsed;
			max_ev = i;
		}
	}
	avg = sum / (double)TOTAL_NUM_EVENTS;
	
	//출력
	printf("Minimun Event Processing time: %8.2lf[ms] for", min * 1000);
	printEvent_withTime(&thrdMon.ev_Processed[min_ev]); printf("\n");
	printf("Maximun Event Processing time: %8.2lf[ms] for", max * 1000);
	printEvent_withTime(&thrdMon.ev_Processed[max_ev]); printf("\n");
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000, TOTAL_NUM_EVENTS);
	printf("\n");

	return 0;
}