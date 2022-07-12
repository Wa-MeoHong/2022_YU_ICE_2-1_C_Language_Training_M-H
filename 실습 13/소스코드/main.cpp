/*
  ���ϸ� : "�ǽ�13_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- �ڱ����� ����ü�� �̿��ؼ� �켱���� ť�� �����带 ��Ƽ�� ������ ���α׷�

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 5�� 31��)
  ���� Update : Version 1.1.0, 2022�� 6�� 1��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/05/31		v1.0.0		  ���� �ۼ�
	�Ŵ�ȫ		 2022/06/01		v1.1.0		  �ڵ� �ϼ�

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
	DLL_EvQ dll_EvQ_PriH, dll_EvQ_PriL;						// �켱���� High, Low �̺�Ʈ ť �ΰ�
	Event* pEv;												// �̺�Ʈ ����
	int myAddr = 0;
	//int ev_hand_add, ev_prior;							// �̺�Ʈ �ڵ鸵 �ּ�, �켱����
	LARGE_INTEGER freq;										// ��ǻ�� Ŭ���� ����

	initDLL_EvQ(&dll_EvQ_PriH, 0);							// �̺�Ʈ �켱���� ť �ʱⰪ ����
	initDLL_EvQ(&dll_EvQ_PriL, 1);

	random();

	// �̺�Ʈ ������ �Ķ���� �ʱⰪ ����
	T_P_Ev thrdP_E_Gen[NUM_EVENT_GENERATORS];				// �̺�Ʈ ���ʷ����� ������ �Ķ���͵�
	T_P_Ev thrdP_E_Han[NUM_EVENT_HANDLERS];					// �̺�Ʈ �ڵ鷯 ������ �Ķ����

	thread thrd_evHans[NUM_EVENT_HANDLERS];					// ������ ���� (�̺�Ʈ �ڵ鷯 0��, 1��)
	thread thrd_evGens[NUM_EVENT_GENERATORS];				// ������ ���� (�̺�Ʈ ���ʷ����� 0��, 1��, 2��)

	mutex cs_main, cs_thrd_mon;								// mutex ���� ���ο�, ������ ����͸� ��
	T_Stat thrdMon;											// ������ ����͸� ����

	HANDLE consHandler;										// �ܼ�â �ڵ鸵�� HANDLE ����
	THREAD_FLAG eventThreadFlag = RUN;						// �������� ���� ����
	int count, total_Event_Gen = 0, total_Event_Proc = 0;

	consHandler = initConsoleHandler();						// �ܼ�â �ʱⰪ ����
	QueryPerformanceFrequency(&freq);						// �ð��� ������� Ŭ�� ����

	// ������ ����͸� ���� �ʱ�ȭ
	thrdMon.pFlagThreadTerminated = &eventThreadFlag;		// ������ ���¸� ������ ����
	thrdMon.total_G_E = 0, thrdMon.total_P_E = 0; 
	thrdMon.num_P_E_H = 0, thrdMon.num_P_E_L = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.ev_Processed[ev].ev_no = -1;
		thrdMon.ev_Processed[ev].ev_pri = -1;
	}

	// �̺�Ʈ �ڵ鷯 ������ ����
	// ���� �̺�Ʈ �ڵ鷯 ��������� ���� �ʱ�ȭ
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thrdMon.eventProc[p] = 0;							// �̺�Ʈ �ڵ鷯 �ּ�
		thrdP_E_Han[p].fout = NULL;							// ��� ���� �ּ�
		thrdP_E_Han[p].role = EVENT_HANDLER;				// �� �������� ������? �̺�Ʈ �ڵ鷯
		thrdP_E_Han[p].myAddr = p;							// �̺�Ʈ �ڵ鷯 ��ȣ
		thrdP_E_Han[p].pCS_main = &cs_main, thrdP_E_Han[p].pCS_thrd_mon = &cs_thrd_mon; // mutex�� ����
		thrdP_E_Han[p].EvQ_PriH = &dll_EvQ_PriH;			// �켱���� ���� ť�� ����
		thrdP_E_Han[p].EvQ_PriL = &dll_EvQ_PriL;			// �켱���� ���� ť ����
		thrdP_E_Han[p].maxRound = MAX_ROUND;				// �ִ� ����� ����
		thrdP_E_Han[p].pThrdMon = &thrdMon;					// ������ ����͸� ���� ����
		thrdP_E_Han[p].freq = freq;							// Ŭ�� ���ļ� ����

		thrd_evHans[p] = thread(Thread_EventHandler, &thrdP_E_Han[p]); // �̺�Ʈ ó���� ������ ����( ��ȣ�� �°�)
		printf("%d-th Thread_EventHandler is created and activated (id : %d)\n", p + 1, thrd_evHans[p].get_id());
		// ���° �̺�Ʈ ó�� �����尡 �����Ǿ����� ���
	}

	// �̺�Ʈ ���ʷ����� ������ ����
	// ���� �̺�Ʈ ���ʷ����� ��������� ���� �ʱ�ȭ
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thrdMon.eventGen[g] = 0;							// �̺�Ʈ �ڵ鷯 �ּ�
		thrdP_E_Gen[g].fout = NULL;							// ��� ���� �ּ�
		thrdP_E_Gen[g].role = EVENT_GENERATOR;				// �� �������� ������? �̺�Ʈ ���ʷ�����
		thrdP_E_Gen[g].myAddr = g;							// �̺�Ʈ ���ʷ����� ��ȣ
		thrdP_E_Gen[g].pCS_main = &cs_main, thrdP_E_Gen[g].pCS_thrd_mon = &cs_thrd_mon; // mutex�� ����
		thrdP_E_Gen[g].EvQ_PriH = &dll_EvQ_PriH;			// �켱���� ���� ť�� ����
		thrdP_E_Gen[g].EvQ_PriL = &dll_EvQ_PriL;			// �켱���� ���� ť ����
		thrdP_E_Gen[g].targetEventGen = NUM_EV_PER_GEN;
		thrdP_E_Gen[g].maxRound = MAX_ROUND;				// �ִ� ����� ����
		thrdP_E_Gen[g].pThrdMon = &thrdMon;					// ������ ����͸� ���� ����
		thrdP_E_Gen[g].freq = freq;							// Ŭ�� ���ļ� ����

		thrd_evGens[g] = thread(Thread_EventGenerator, &thrdP_E_Gen[g]); // �̺�Ʈ ������ ������ ����( ��ȣ�� �°�)
		printf("%d-th Thread_EventGenerator is created and activated (id : %d)\n", g + 1, thrd_evGens[g].get_id());
		// ���° �̺�Ʈ ó�� �����尡 �����Ǿ����� ���
	}

	// ������ ����͸� (�ѹ� ��������)
	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();										// mutex�� �ٸ� �����尡 ���� ħ������ ���ϵ��� ���´�. (�̺�Ʈ �迭��)
		system("cls");
		gotoxy(consHandler, 0, 0);							// �ܼ�â�� �ʱ�ȭ ��Ű�� ����
		printf("Thread monitoring by main() :: round(%2d): \n", round);
		cs_thrd_mon.lock();									// �����嵵 �ɾ���ٴ�.

		// �̺�Ʈ ������ �����尡 �����ؼ� �̺�Ʈ�� ������ ���¸� ���
		for (int i = 0; i < NUM_EVENT_GENERATORS; i++)
		{
			printf("\tEvent_Gen[%d] generated %2d events.\n", i, thrdMon.eventGen[i]);
		}

		printf("Event_Generators have generated total %2d events\n", thrdMon.total_G_E);
		total_Event_Gen = thrdMon.total_G_E;
		printf("\nTotal Generated Events (current total %d events)\n\t", total_Event_Gen); // �� ��� �����Ǿ��°�
		// ������ �̺�Ʈ�� �� ���
		for (int ev = 0; ev < total_Event_Gen; ev++)
		{
			pEv = &thrdMon.ev_Generated[ev];				// ������ �̺�Ʈ�迭(�� �����忡�� ������ �̺�Ʈ��)�� ������
			if (pEv != NULL)								// �̺�Ʈ�� ���������� ������������
			{
				printEvent(pEv);							// ���
				if ((ev + 1) % EVENT_PER_LINE == 0)			// 1�ٴ� �̺�Ʈ�� �ټ����� ����� �Ǹ�
					printf("\n\t");
			}
		}
		printf("\n"); 

		// ������ �̺�Ʈ�� ó���� (�̺�Ʈ ó���� ������ ����)
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
		// ó���� �̺�Ʈ�� �� ���
		for (int ev = 0; ev < total_Event_Proc; ev++)
		{
			pEv = &thrdMon.ev_Processed[ev];				// ������ �̺�Ʈ�迭(�� �����忡�� ������ �̺�Ʈ��)�� ������
			if (pEv != NULL)								// �̺�Ʈ�� ���������� ������������
			{
				printEvent(pEv);							// ���
				if ((ev + 1) % EVENT_PER_LINE == 0)			// 1�ٴ� �̺�Ʈ�� �ټ����� ����� �Ǹ�
					printf("\n\t");
			}
		}
		printf("\n");
		cs_thrd_mon.unlock();								// ������ �������
		if (total_Event_Proc >= TOTAL_NUM_EVENTS)			// ��� �̺�Ʈ�� ó���� �Ϸ�Ǿ�����
		{
			printf("!!! TotalEventProcessed (%d) is reached to target TOTAL_NUM_EVENT(%d)\n",
				total_Event_Proc, TOTAL_NUM_EVENTS);
			eventThreadFlag = TERMINATE;					// ��� �����带 �����Ű�� ���� eventThreadFlag�� ������·� ��ȯ�Ѵ�.
			cs_main.unlock();								// ���� ������ ���
			break;											// �ݺ��� Ż��
		}
		cs_main.unlock();									// ������ ���
		Sleep(100);
	}														// �̺�Ʈ ����, ó�� �ݺ��� 

	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thrd_evHans[p].join();								// �̺�Ʈ ó���� ������ ����
	}
	printf("All threads of Event_Handlers are terminated !!\n");

	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thrd_evGens[g].join();								// �̺�Ʈ ������ ������ ����
	}
	printf("All threads of Event_Generators are terminated !!\n");

	// �̺�Ʈ ����~ó������ �ɸ� �ð� ����, �ִ�, �ּ�, ��� �ð� ����
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
	
	//���
	printf("Minimun Event Processing time: %8.2lf[ms] for", min * 1000);
	printEvent_withTime(&thrdMon.ev_Processed[min_ev]); printf("\n");
	printf("Maximun Event Processing time: %8.2lf[ms] for", max * 1000);
	printEvent_withTime(&thrdMon.ev_Processed[max_ev]); printf("\n");
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000, TOTAL_NUM_EVENTS);
	printf("\n");

	return 0;
}