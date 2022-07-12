/*
  ���ϸ� : "�ǽ�12_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- �켱���� ť(Priority Queue)�� ��Ƽ������� �̺�Ʈ�� ����, ó���ϴ� ���α׷�

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 5�� 25��)
  ���� Update : Version 1.0.0, 2022�� 5�� 25��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/05/25		v1.0.0		  �����ۼ�

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

	initPriQ_Ev(&priQ_Event, "PriQ_Event", 1);				// ó�� PriQ_Event �ʱⰪ ����

	TPE thrdParam_Ev_Gen, thrdParam_EvHndl;
	mutex cs_main, cs_thrd_mon;								// �ܼ� ǥ�ÿ�, ������ ����͸���
	T_Stat_M thrdMon;
	HANDLE consHndlr;
	THREAD_FLAG evThread_Flag = RUN;

	int count, num_E_G, num_P_E;
	LARGE_INTEGER freq;	

	consHndlr = initConsoleHandler();						// �ܼ� �ڵ鷯 �ʱⰪ ����

	thrdMon.pFlagThreadTerminate = &evThread_Flag;
	thrdMon.total_G_E = 0; thrdMon.total_P_E = 0;

	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].ev_no = -1;				// ���μ��� ���� ���� �ֵ��� -1�� �����.
		thrdMon.eventProcessed[ev].ev_pri = -1; 
	}

	QueryPerformanceFrequency(&freq);						// �ð��� �궧 ���(1�ʿ� Ŭ���� ��� �߻��ϴ����� ����)
	thrdMon.num_P_E = 0;									// Thread Monitoring �ʱⰪ ���� 
	thrdParam_EvHndl.role = EVENT_HANDLER;
	thrdParam_EvHndl.myAddr = 1;							// link address
	thrdParam_EvHndl.pMTX_main = &cs_main; 
	thrdParam_EvHndl.pMTX_thrd_mon = &cs_thrd_mon;
	thrdParam_EvHndl.pPriQ_Event = &priQ_Event;
	thrdParam_EvHndl.maxRound = MAX_ROUND;
	thrdParam_EvHndl.pThrdMon = &thrdMon;
		
	thread thrd_ev_handler(Thread_EventHandler, &thrdParam_EvHndl); // �̺�Ʈ �ڵ鷯�Լ� ������ ����     

	cs_main.lock();											// �߰� �߰� mutex�� ���ؼ� ������ ���� �Ǵ�.
	printf("Thread_EventHandler is created and activated ...\n");
	cs_main.unlock();

	thrdMon.num_G_E = 0;									// ������ �Ķ���� �ʱ�ȭ
	thrdParam_Ev_Gen.role = EVENT_GENERATOR;
	thrdParam_Ev_Gen.myAddr = 0;							// my Address
	thrdParam_Ev_Gen.pMTX_main = &cs_main;
	thrdParam_Ev_Gen.pMTX_thrd_mon = &cs_thrd_mon;
	thrdParam_Ev_Gen.pPriQ_Event = &priQ_Event;
	thrdParam_Ev_Gen.targetEventGen = NUM_EVENTS_PER_GEN;	// �̰� �߰�
	thrdParam_Ev_Gen.maxRound = MAX_ROUND;
	thrdParam_Ev_Gen.pThrdMon = &thrdMon;

	thread thrd_ev_generator(Thread_EventGenerator, &thrdParam_Ev_Gen); // �̺�Ʈ ���ʷ����� �Լ� ������
	cs_main.lock();
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();

	//���� Thread_EventGenerator�� Thread_EventHandler�� ���ķ� main.cpp�� ���ÿ� �����

	for (int round = 0; round < MAX_ROUND; round++) 
	{
		// �̺�Ʈ ���ʷ����Ϳ� �ڵ鷯�� ���ÿ� ���ķ� �۾���
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
			pEv = &thrdMon.eventGenerated[i];				// ���࿡ �̺�Ʈ ���ʷ����Ͱ� ��ó ������ ���� ���� ���� 
			if (pEv != NULL)
			{
				printEvent(pEv);
				if (((i + 1) % EVENT_PER_LINE) == 0)
					printf("\n\t");
			} // ����� ���Ѵ�.
		}

		// �켱���� ť ������ ���
		printf("\n");
		printf("Event_Gen generated %2d events\n", thrdMon.num_G_E);
		printf("Event_Handler processed %2d events\n", thrdMon.num_P_E);
		printf("\nPriQ_Event ::"); printPriQ(&priQ_Event);
		printf("\nEvents processed : \n\t");

		count = 0;

		num_P_E = thrdMon.total_P_E;						// ���μ��̵� �̺�Ʈ ��
		for (int i = 0; i < num_P_E; i++)
		{
			pEv = &thrdMon.eventProcessed[i];
			if (pEv != NULL)
			{
				calc_elapsed_time(pEv, freq);
				printEvent_withTime(pEv);					// ���μ��̵� �̺�Ʈ �� ���
				if (((i + 1) % EVENT_PER_LINE) == 0)
					printf("\n\t");
			}
		}
		printf("\n");

		if (num_P_E >= TOTAL_NUM_EVENTS)					// 50�� �̺�Ʈ ���� ���μ����� �� �ϸ�
		{
			evThread_Flag = TERMINATE;						// terminated �� ����
			break;
		}
		Sleep(100);
	}
	
	double min, max, avg, sum;								// �ð��� �ִ�, �ּ�, ���, ��
	int min_ev, max_ev;										// �ּҽð��� �ɸ� �̺�Ʈ, �ִ�ð��� �ɸ� �̺�Ʈ

	min = max = sum = thrdMon.eventProcessed[0].elap_time;	// �ʱⰪ 
	min_ev = max_ev = 0;									// �ʱⰪ ����
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++)				// �ð��� �ִ밪, �ּڰ�, ����� ���ϱ� ���� �հ踦 ����
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
	avg = sum / TOTAL_NUM_EVENTS;							// �ð� ���

	// ���
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