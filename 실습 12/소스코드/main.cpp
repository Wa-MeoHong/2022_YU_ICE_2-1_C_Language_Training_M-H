/*
  파일명 : "실습12_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 우선순위 큐(Priority Queue)를 멀티쓰레드로 이벤트를 생성, 처리하는 프로그램

  프로그램 작성자 : 신대홍(2022년 5월 25일)
  최종 Update : Version 1.0.0, 2022년 5월 25일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/05/25		v1.0.0		  최초작성

===========================================================================================================
*/

#include "Event.h"
#include "PriQ_E.h"
#include "Thread.h"
#include "ConsoleDisplay.h"
#include <thread>
#include <iostream>

using namespace std;

int main(void) 
{
	PriQ priQ_Event; 
	Event* pEv;
	int myAddr = 0;

	initPriQ_Ev(&priQ_Event, "PriQ_Event", 1);				// 처음 PriQ_Event 초기값 설정

	TPE thrdParam_Ev_Gen, thrdParam_EvHndl;
	mutex cs_main, cs_thrd_mon;								// 콘솔 표시용, 쓰레드 모니터링용
	T_Stat_M thrdMon;
	HANDLE consHndlr;
	THREAD_FLAG evThread_Flag = RUN;

	int count, num_E_G, num_P_E;
	LARGE_INTEGER freq;	

	consHndlr = initConsoleHandler();						// 콘솔 핸들러 초기값 설정

	thrdMon.pFlagThreadTerminate = &evThread_Flag;
	thrdMon.total_G_E = 0; thrdMon.total_P_E = 0;

	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].ev_no = -1;				// 프로세스 되지 않은 애들은 -1로 만든다.
		thrdMon.eventProcessed[ev].ev_pri = -1; 
	}

	QueryPerformanceFrequency(&freq);						// 시간을 잴때 사용(1초에 클럭이 몇번 발생하는지를 측정)
	thrdMon.num_P_E = 0;									// Thread Monitoring 초기값 설정 
	thrdParam_EvHndl.role = EVENT_HANDLER;
	thrdParam_EvHndl.myAddr = 1;							// link address
	thrdParam_EvHndl.pMTX_main = &cs_main; 
	thrdParam_EvHndl.pMTX_thrd_mon = &cs_thrd_mon;
	thrdParam_EvHndl.pPriQ_Event = &priQ_Event;
	thrdParam_EvHndl.maxRound = MAX_ROUND;
	thrdParam_EvHndl.pThrdMon = &thrdMon;
		
	thread thrd_ev_handler(Thread_EventHandler, &thrdParam_EvHndl); // 이벤트 핸들러함수 쓰레드 생성     

	cs_main.lock();											// 중간 중간 mutex를 통해서 쓰레드 락을 건다.
	printf("Thread_EventHandler is created and activated ...\n");
	cs_main.unlock();

	thrdMon.num_G_E = 0;									// 쓰레드 파라미터 초기화
	thrdParam_Ev_Gen.role = EVENT_GENERATOR;
	thrdParam_Ev_Gen.myAddr = 0;							// my Address
	thrdParam_Ev_Gen.pMTX_main = &cs_main;
	thrdParam_Ev_Gen.pMTX_thrd_mon = &cs_thrd_mon;
	thrdParam_Ev_Gen.pPriQ_Event = &priQ_Event;
	thrdParam_Ev_Gen.targetEventGen = NUM_EVENTS_PER_GEN;	// 이거 추가
	thrdParam_Ev_Gen.maxRound = MAX_ROUND;
	thrdParam_Ev_Gen.pThrdMon = &thrdMon;

	thread thrd_ev_generator(Thread_EventGenerator, &thrdParam_Ev_Gen); // 이벤트 제너레이터 함수 쓰레드
	cs_main.lock();
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();

	//이제 Thread_EventGenerator와 Thread_EventHandler는 병렬로 main.cpp와 동시에 진행됨

	for (int round = 0; round < MAX_ROUND; round++) 
	{
		// 이벤트 제너레이터와 핸들러가 동시에 병렬로 작업중
		system("cls");
		gotoxy(consHndlr, 0, 0);
		printf("Thread monitoring by main() ::\n");
		printf("\tround(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n", \
			round, thrdMon.total_G_E, thrdMon.total_P_E);
		printf("\nEvents generated: \n\t");
		count = 0;
		num_E_G = thrdMon.total_G_E;
		for (int i = 0; i < num_E_G; i++)
		{
			pEv = &thrdMon.eventGenerated[i];				// 만약에 이벤트 제너레이터가 미처 생성을 하지 못한 경우는 
			if (pEv != NULL)
			{
				printEvent(pEv);
				if (((i + 1) % EVENT_PER_LINE) == 0)
					printf("\n\t");
			} // 출력을 안한다.
		}

		// 우선순위 큐 나머지 출력
		printf("\n");
		printf("Event_Gen generated %2d events\n", thrdMon.num_G_E);
		printf("Event_Handler processed %2d events\n", thrdMon.num_P_E);
		printf("\nPriQ_Event ::"); printPriQ(&priQ_Event);
		printf("\nEvents processed : \n\t");

		count = 0;

		num_P_E = thrdMon.total_P_E;						// 프로세싱된 이벤트 수
		for (int i = 0; i < num_P_E; i++)
		{
			pEv = &thrdMon.eventProcessed[i];
			if (pEv != NULL)
			{
				calc_elapsed_time(pEv, freq);
				printEvent_withTime(pEv);					// 프로세싱된 이벤트 수 출력
				if (((i + 1) % EVENT_PER_LINE) == 0)
					printf("\n\t");
			}
		}
		printf("\n");

		if (num_P_E >= TOTAL_NUM_EVENTS)					// 50개 이벤트 전부 프로세스를 다 하면
		{
			evThread_Flag = TERMINATE;						// terminated 를 설정
			break;
		}
		Sleep(100);
	}
	
	double min, max, avg, sum;								// 시간의 최대, 최소, 평균, 합
	int min_ev, max_ev;										// 최소시간이 걸린 이벤트, 최대시간이 걸린 이벤트

	min = max = sum = thrdMon.eventProcessed[0].elap_time;	// 초기값 
	min_ev = max_ev = 0;									// 초기값 설정
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++)				// 시간의 최대값, 최솟값, 평균을 구하기 위한 합계를 구함
	{
		sum += thrdMon.eventProcessed[i].elap_time;
		if (min > thrdMon.eventProcessed[i].elap_time)
		{
			min = thrdMon.eventProcessed[i].elap_time;
			min_ev = i;
		}
		if (max < thrdMon.eventProcessed[i].elap_time)
		{
			max = thrdMon.eventProcessed[i].elap_time;
			max_ev = i;
		}
	}
	avg = sum / TOTAL_NUM_EVENTS;							// 시간 평균

	// 출력
	printf("Minimum event processing time: %8.2lf[ms] for ", min * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[min_ev]); printf("\n");
	printf("Maximum event processing time: %8.2lf[ms] for ", max * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[max_ev]); printf("\n");
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000, TOTAL_NUM_EVENTS);
	printf("\n");

	thrd_ev_generator.join();
	printf("Thread_EventGenerator is terminated !!\n");
	thrd_ev_handler.join();
	printf("Thread_EventHandler is terminated !!\n");

	delPriQ_Ev(&priQ_Event);
}