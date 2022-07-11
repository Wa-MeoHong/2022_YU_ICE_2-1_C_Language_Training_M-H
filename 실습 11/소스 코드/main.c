/*
  ���ϸ� : "�ǽ�11_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- ȯ�� ť, ���� ����Ʈ�� ť�� �����ϰ�, �̺�Ʈ�� �߰�, ������ �ϸ� �������
	�޸𸮰� �����Ǵ��� Ȯ���غ��� ���α׷�

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 5�� 17��)
  ���� Update : Version 1.0.1, 2022�� 5�� 18��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/05/17		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/05/18		v1.0.1		  �ڵ� �ϼ�

===========================================================================================================
*/

#include "Event.h"
#include "CirQ_E.h"
#include "PriQ_E.h"
#include <conio.h>

#define OUTPUT "output.txt"
#define RANDOMIZE() srand((unsigned int)time(NULL))
#define INIT_PriQ_SIZE 1

int inputMENU(); // �޴� �Է¿� �Լ�
void test_FIFO_CirQ_Event(FILE* fout, int max_events_P_round);
void test_PriQ_Event(FILE* fout, int max_events_P_round);

int main(void)
{
	FILE* fout = NULL;
	int menu;
	int max_events_P_round;

	if ((fout = fopen(OUTPUT, "w")) == NULL) //��¿� ���� ����, ������ �޼��� ���
	{
		printf("ERROR! output.txt does not OPEN!!\n");
		exit(-1);
	}
	RANDOMIZE(); // ���� ������ ���� �õ� ����
	while (1)
	{
		if ((menu = inputMENU()) == 0) // �޴� �Է�, 0 �Է½� ������
			break;
		printf("Input Num_events per round : ");
		scanf("%d", &max_events_P_round);
		switch (menu)
		{
		case 1:
			test_FIFO_CirQ_Event(fout, max_events_P_round);	
			break;
		case 2:
			test_PriQ_Event(fout, max_events_P_round);
			break;
		default:
			break;
		}
		printf("-----------Press any key to go to menu--------------\n"); // ������ ���� ��, �޴��� ���ư����� Ű �Է�
		_getch();
		system("cls"); // �ܼ�â�� �ѹ� ���ٰ� �ٽ� while�� ÷���� ���ư��� �޴� ���
	}
	fclose(fout); // ���� �ݱ� 
	return 0;
}

int inputMENU() // �޴���¿� �Լ�, �Է��� �޴��� ��ȯ��Ŵ
{
	int menu;

	printf("====================================================\n");
	printf("           \t -Available Menu-\n");
	printf("\t     1. Test FIFO/CirQ Event.\n");
	printf("\t     2. Test FIFO/CirQ Event.\n");
	printf("====================================================\n");
	printf("Input menu (0 to Quit) : ");
	scanf("%d", &menu); // �޴� �Է�

	return menu;
}

void test_FIFO_CirQ_Event(FILE* fout, int max_events_P_round)
{
	CirQ* pCirQ_Event;
	Event* pEv = NULL;
	Event Processed_Events[N_O_EVENTS];

	int total_P_E = 0; // processed �� �� events
	int total_G_E = 0; // generated �� �� events
	int num_events = 0;// �� ���� �� �̺�Ʈ ��( = max_events_P_round)
	int num_G_R = 0; // Generated �� Round ��
	int num_P_R = 0; // processed �� Round �� 

	pCirQ_Event = (CirQ*)calloc(1, sizeof(CirQ)); // ȯ�� ť ����
	fprintf(fout, "Testing Event Handling with FIFO Circular Queue\n");
	printf("Initializing FIFO CirQ of capacity (%d)\n", max_events_P_round);
	fprintf(fout,"Initializing FIFO CirQ of capacity (%d)\n", max_events_P_round);
	pCirQ_Event = initCirQ(pCirQ_Event, max_events_P_round);

	fprintf(fout, "\nEnqueuing Data into Event Circular queue: \n"); //���� �̺�Ʈ �߰����� �Ѵ�.
	for (int round = 0; round < MAX_ROUND; round++)
	{
		fprintf(fout, "Start of (%2d) ****\n", round); //���� ���
		if (total_G_E < N_O_EVENTS)
		{
			num_events = max_events_P_round;
			if (total_G_E + num_events > N_O_EVENTS)
				num_events = N_O_EVENTS - total_G_E; //���� ������ �̺�Ʈ�� �����Ѵٸ�, �� �̺�Ʈ���� ���� �������� ������
			fprintf(fout, "Generated and enque %2d events\n", num_events);
			num_G_R = 0; // Generated�� ���� ���� �ʱ�ȭ

			for (int i = 0; i < num_events; i++)
			{
				if (isCirQFull(pCirQ_Event)) // ���� ȯ�� ť�� ��á����
				{
					fprintf(fout, "   !!! CirQ_Event is full --> SKIP Generation and Enqueueing of Event. \n");
					break; // �� ��� �����Ѵ�.
				}
				pEv = genEvent(pEv, total_G_E, EVENT_GENERATOR, N_O_EVENTS - total_G_E - 1);
				// �̺�Ʈ�� ������
				fprintf(fout, ">>> Enqueue event = ");
				fprintEvent(fout, pEv); // ������ �̺�Ʈ ���
				enCirQ(pCirQ_Event, *pEv); // ���� �̺�Ʈ�� enqueue(�߰�)��
				fprintCirQ(fout, pCirQ_Event); // �̺�Ʈ1�� ���
				free(pEv); // �Ʊ� �̺�Ʈ �����ϱ� ���ؼ� ���� �ּҸ� ��������
				total_G_E++; // ������ �̺�Ʈ �� ����
				num_G_R++; 
			}

			fprintf(fout, "\nDequeuing Data from Event Circular queue: \n"); //���� Dequeue�� �Ѵ�. (������ �̺�Ʈ�� ����)
			num_events = max_events_P_round; // ������ 50���� �����߱� ����

			if ((total_P_E + num_events) > N_O_EVENTS)
				num_events = N_O_EVENTS - total_P_E; //���� �Ϸ�� �̺�Ʈ�� �����Ѵٸ�, �� �̺�Ʈ���� ���� �������� ������

			fprintf(fout, "Dequeue %2d events\n", num_events); // Dequeue �۾� ����
			num_P_R = 0; // �۾� �Ϸ�� round ���� �ʰ�ȭ
			for (int i = 0; i < num_events; i++) // �۾��ϴ� for ��
			{
				if (isCirQEmpty(pCirQ_Event)) // ���� Dequeue�� �̺�Ʈ���� ������
					break; // �ٷ� for�� Ż��
				pEv = deCirQ(pCirQ_Event); 
				if (pEv != NULL)
				{
					fprintf(fout, "<<< Dequeued event = "); // dequeue�� �̺�Ʈ ��� 
					fprintEvent(fout, pEv); // ���
					fprintf(fout, "\n"); //��ĭ ���
					Processed_Events[total_P_E] = *pEv; // processed�� �̺�Ʈ �ּҸ� ��� �迭�� ����
					total_P_E++; // Processed�� �̺�Ʈ ���� ����
					num_P_R++; // ���� UP
				}
				fprintCirQ(fout, pCirQ_Event);
			}
		}
		//Monitoring Simulation Status (�ùķ��̼� ���� ���¸� ��� )

		fprintf(fout, "Round(%2d): Generated_in_this_round(%3d), total_Generated_Events(%3d), ", round, num_G_R, total_G_E); 
		fprintf(fout, "processed_in_this_round(% 3d), total_processed_events(% 3d), ", num_P_R, total_P_E);
		fprintf(fout, "events_in_queue(%3d)\n\n", pCirQ_Event->num_elements);

		printf("Round(%2d): Generated_in_this_round(%3d), total_Generated_Events(%3d), ", round, num_G_R, total_G_E);
		printf("processed_in_this_round(% 3d), total_processed_events(% 3d), ", num_P_R, total_P_E);
		printf("events_in_queue(%3d)\n", pCirQ_Event->num_elements);

		if (total_P_E >= N_O_EVENTS)
			break;
		// ���� Processe�� �����ٸ�( ��� �̺�Ʈ���� Dequeue�ߴٸ�) �ݺ��� ����
	}

	printf("Processed Events : \n"); //Dequeue���� �Ϸ��� �̺�Ʈ���� ���� ����غ���.
	for (int i = 0; i < N_O_EVENTS; i++)
	{
		printf("Ev(id: %3d, pri: %3d), ", Processed_Events[i].event_no, Processed_Events[i].event_pri);
		if ((i + 1) % 5 == 0) //5��°���� �ٹٲ��� ����
			printf("\n");
	}
	printf("\n");
	delCirQ(pCirQ_Event); //���� ȯ�� ť ����� �������Ƿ� �����Ҵ� ����
}

void test_PriQ_Event(FILE* fout, int max_events_P_round)
{
	PriQ* pPriQ_Ev = NULL;
	Event* pEv = NULL;
	Event Processed_event[N_O_EVENTS];
	int total_P_E = 0; // processed �� �� events
	int total_G_E = 0; // generated �� �� events
	int num_events = 0;// �� ���� �� �̺�Ʈ ��( = max_events_P_round)
	int num_G_R = 0; // Generated �� Round ��
	int num_P_R = 0; // processed �� Round �� 

	fprintf(fout, "Testing Event Handling with Priority Queue\n");
	pPriQ_Ev = (PriQ*)calloc(1, sizeof(PriQ)); // malloc���� calloc�� �����ϱ� ������ �̷��� �����ߴ�.
	if (pPriQ_Ev == NULL) // �����Ҵ��� ���� ������ ���� �޼��� ����� ����
	{
		printf("Error!! Not allocing for PriorityQueue_Event!\n");
		fclose(fout);
		exit(-1);
	}
	printf("Initializing PriorityQueue_Event of capacity (%d)\n", INIT_PriQ_SIZE);
	initPriQ_Ev(pPriQ_Ev, "PriorityQueue_Event", INIT_PriQ_SIZE); //�ʱⰪ ����

	for (int round = 0; round < MAX_ROUND; round++) //init �� enqueue�۾�
	{
		fprintf(fout, "\n*** Start of round(%2d)...\n", round);
		num_G_R = 0;
		if (total_G_E < N_O_EVENTS) // Generated�� �̺�Ʈ�� N_O_EVENTS( = 50)�� �ɶ�����
		{
			num_events = max_events_P_round;
			if ((total_G_E + num_events) >= N_O_EVENTS) // ���� Generated�� �̺�Ʈ�� �̹� � ������ ���
				num_events = N_O_EVENTS - total_G_E; // �� ���� �� ����ŭ�� Generate�Ѵ�.
			fprintf(fout, ">>> enque %2d events\n", num_events);
			for (int i = 0; i < num_events; i++)
			{
				pEv = genEvent(pEv, total_G_E, 0, N_O_EVENTS - total_G_E - 1); // �̺�Ʈ ����
				if (pEv == NULL) //�ȵǸ� ����
				{
					printf("Error in generation of event !! \n");
					fclose(fout);
					exit(-1);
				}
				fprintf(fout, "*** enque event : ");
				fprintEvent(fout, pEv); // ���Ͽ� ���
				enPriQ(pPriQ_Ev, pEv); // ����Ʈ�� ť�� �߰� �� �켱���� ������
				total_G_E++; // ������ �̺�Ʈ �� ����
				num_G_R++; // �� ����
				fprintPriQ(fout, pPriQ_Ev); //���
			}
		}
		fprintf(fout, "\n===========================================================================\n");
		fprintf(fout, "\nRemoving min data from Priority Queue . . . \n"); // Dequeue�۾�
		num_events = max_events_P_round;
		if ((total_P_E + num_events) > N_O_EVENTS)
			num_events = N_O_EVENTS - total_P_E;
		fprintf(fout, "<<< Dequeue %2d events\n", num_events);
		num_P_R = 0;
		for (int i = 0; i < num_events; i++)
		{
			pEv = dePriQ(pPriQ_Ev); // dequeue�� ��, �̺�Ʈ ��ȯ���� ��
			if (pEv == NULL) // ������ ���ٸ� ����
			{
				fprintf(fout, "   PriQ is empty\n");
				break;
			}

			fprintf(fout, " *** Dequeued Event : ");
			fprintEvent(fout, pEv); // ���
			Processed_event[total_P_E] = *pEv; // Processed�� �̺�Ʈ�� ���� �迭�� ����                                                               
			total_P_E++; // dequeue�� �̺�Ʈ �� ����
			num_P_R++; // �� ����
		}
		//Monitoring Simulation Status (�ùķ��̼� ���� ���¸� ��� )

		fprintf(fout, "Round(%2d): Generated_in_this_round(%3d), total_Generated_Events(%3d), ", round, num_G_R, total_G_E);
		fprintf(fout, "processed_in_this_round(% 3d), total_processed_events(% 3d), ", num_P_R, total_P_E);
		fprintf(fout, "events_in_queue(%3d)\n\n", pPriQ_Ev->priQ_size);

		printf("Round(%2d): Generated_in_this_round(%3d), total_Generated_Events(%3d), ", round, num_G_R, total_G_E);
		printf("processed_in_this_round(% 3d), total_processed_events(% 3d), ", num_P_R, total_P_E);
		printf("events_in_queue(%3d)\n", pPriQ_Ev->priQ_size);

		if (total_P_E >= N_O_EVENTS)
			break;
		// ���� Processe�� �����ٸ�( ��� �̺�Ʈ���� Dequeue�ߴٸ�) �ݺ��� ����
	}

	printf("Processed Events : \n"); //Dequeue���� �Ϸ��� �̺�Ʈ���� ���� ����غ���.
	for (int i = 0; i < N_O_EVENTS; i++)
	{
		printf("Ev(id: %3d, pri: %3d), ", Processed_event[i].event_no, Processed_event[i].event_pri);
		if ((i + 1) % 5 == 0) //5��°���� �ٹٲ��� ����
			printf("\n");
	}
	printf("\n");
	delPriQ_Ev(pPriQ_Ev); //���� �켱���� ť ����� �������Ƿ� �����Ҵ� ����

}