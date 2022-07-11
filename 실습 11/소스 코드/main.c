/*
  파일명 : "실습11_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 환형 큐, 완전 이진트리 큐를 구성하고, 이벤트의 추가, 삭제를 하며 어떤식으로
	메모리가 관리되는지 확인해보는 프로그램

  프로그램 작성자 : 신대홍(2022년 5월 17일)
  최종 Update : Version 1.0.1, 2022년 5월 18일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/05/17		v1.0.0		  최초작성
	신대홍		 2022/05/18		v1.0.1		  코드 완성

===========================================================================================================
*/

#include "Event.h"
#include "CirQ_E.h"
#include "PriQ_E.h"
#include <conio.h>

#define OUTPUT "output.txt"
#define RANDOMIZE() srand((unsigned int)time(NULL))
#define INIT_PriQ_SIZE 1

int inputMENU(); // 메뉴 입력용 함수
void test_FIFO_CirQ_Event(FILE* fout, int max_events_P_round);
void test_PriQ_Event(FILE* fout, int max_events_P_round);

int main(void)
{
	FILE* fout = NULL;
	int menu;
	int max_events_P_round;

	if ((fout = fopen(OUTPUT, "w")) == NULL) //출력용 파일 열기, 에러면 메세지 출력
	{
		printf("ERROR! output.txt does not OPEN!!\n");
		exit(-1);
	}
	RANDOMIZE(); // 난수 생성을 위한 시드 생성
	while (1)
	{
		if ((menu = inputMENU()) == 0) // 메뉴 입력, 0 입력시 나가기
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
		printf("-----------Press any key to go to menu--------------\n"); // 동작을 끝낸 후, 메뉴로 돌아가기전 키 입력
		_getch();
		system("cls"); // 콘솔창을 한번 껏다가 다시 while문 첨으로 돌아가서 메뉴 출력
	}
	fclose(fout); // 파일 닫기 
	return 0;
}

int inputMENU() // 메뉴출력용 함수, 입력한 메뉴를 반환시킴
{
	int menu;

	printf("====================================================\n");
	printf("           \t -Available Menu-\n");
	printf("\t     1. Test FIFO/CirQ Event.\n");
	printf("\t     2. Test FIFO/CirQ Event.\n");
	printf("====================================================\n");
	printf("Input menu (0 to Quit) : ");
	scanf("%d", &menu); // 메뉴 입력

	return menu;
}

void test_FIFO_CirQ_Event(FILE* fout, int max_events_P_round)
{
	CirQ* pCirQ_Event;
	Event* pEv = NULL;
	Event Processed_Events[N_O_EVENTS];

	int total_P_E = 0; // processed 된 총 events
	int total_G_E = 0; // generated 된 총 events
	int num_events = 0;// 한 라운드 당 이벤트 수( = max_events_P_round)
	int num_G_R = 0; // Generated 된 Round 수
	int num_P_R = 0; // processed 된 Round 수 

	pCirQ_Event = (CirQ*)calloc(1, sizeof(CirQ)); // 환형 큐 생성
	fprintf(fout, "Testing Event Handling with FIFO Circular Queue\n");
	printf("Initializing FIFO CirQ of capacity (%d)\n", max_events_P_round);
	fprintf(fout,"Initializing FIFO CirQ of capacity (%d)\n", max_events_P_round);
	pCirQ_Event = initCirQ(pCirQ_Event, max_events_P_round);

	fprintf(fout, "\nEnqueuing Data into Event Circular queue: \n"); //먼저 이벤트 추가부터 한다.
	for (int round = 0; round < MAX_ROUND; round++)
	{
		fprintf(fout, "Start of (%2d) ****\n", round); //파일 출력
		if (total_G_E < N_O_EVENTS)
		{
			num_events = max_events_P_round;
			if (total_G_E + num_events > N_O_EVENTS)
				num_events = N_O_EVENTS - total_G_E; //만약 생성된 이벤트가 존재한다면, 그 이벤트들을 빼고 나머지만 만들면됨
			fprintf(fout, "Generated and enque %2d events\n", num_events);
			num_G_R = 0; // Generated된 라운드 개수 초기화

			for (int i = 0; i < num_events; i++)
			{
				if (isCirQFull(pCirQ_Event)) // 만약 환형 큐가 꽉찼으면
				{
					fprintf(fout, "   !!! CirQ_Event is full --> SKIP Generation and Enqueueing of Event. \n");
					break; // 그 즉시 종료한다.
				}
				pEv = genEvent(pEv, total_G_E, EVENT_GENERATOR, N_O_EVENTS - total_G_E - 1);
				// 이벤트를 생성함
				fprintf(fout, ">>> Enqueue event = ");
				fprintEvent(fout, pEv); // 생성된 이벤트 출력
				enCirQ(pCirQ_Event, *pEv); // 이제 이벤트를 enqueue(추가)함
				fprintCirQ(fout, pCirQ_Event); // 이벤트1개 출력
				free(pEv); // 아까 이벤트 생성하기 위해서 만든 주소를 해제해줌
				total_G_E++; // 생성된 이벤트 수 갱신
				num_G_R++; 
			}

			fprintf(fout, "\nDequeuing Data from Event Circular queue: \n"); //이제 Dequeue를 한다. (생성한 이벤트를 제거)
			num_events = max_events_P_round; // 위에서 50개를 생성했기 때문

			if ((total_P_E + num_events) > N_O_EVENTS)
				num_events = N_O_EVENTS - total_P_E; //만약 완료된 이벤트가 존재한다면, 그 이벤트들을 빼고 나머지만 만들면됨

			fprintf(fout, "Dequeue %2d events\n", num_events); // Dequeue 작업 시작
			num_P_R = 0; // 작업 완료된 round 개수 초가화
			for (int i = 0; i < num_events; i++) // 작업하는 for 문
			{
				if (isCirQEmpty(pCirQ_Event)) // 만약 Dequeue할 이벤트마저 없으면
					break; // 바로 for문 탈출
				pEv = deCirQ(pCirQ_Event); 
				if (pEv != NULL)
				{
					fprintf(fout, "<<< Dequeued event = "); // dequeue한 이벤트 출력 
					fprintEvent(fout, pEv); // 출력
					fprintf(fout, "\n"); //한칸 띄움
					Processed_Events[total_P_E] = *pEv; // processed된 이벤트 주소를 담는 배열에 담음
					total_P_E++; // Processed된 이벤트 개수 갱신
					num_P_R++; // 라운드 UP
				}
				fprintCirQ(fout, pCirQ_Event);
			}
		}
		//Monitoring Simulation Status (시뮬레이션 중인 상태를 출력 )

		fprintf(fout, "Round(%2d): Generated_in_this_round(%3d), total_Generated_Events(%3d), ", round, num_G_R, total_G_E); 
		fprintf(fout, "processed_in_this_round(% 3d), total_processed_events(% 3d), ", num_P_R, total_P_E);
		fprintf(fout, "events_in_queue(%3d)\n\n", pCirQ_Event->num_elements);

		printf("Round(%2d): Generated_in_this_round(%3d), total_Generated_Events(%3d), ", round, num_G_R, total_G_E);
		printf("processed_in_this_round(% 3d), total_processed_events(% 3d), ", num_P_R, total_P_E);
		printf("events_in_queue(%3d)\n", pCirQ_Event->num_elements);

		if (total_P_E >= N_O_EVENTS)
			break;
		// 만약 Processe가 끝났다면( 모든 이벤트들을 Dequeue했다면) 반복문 중지
	}

	printf("Processed Events : \n"); //Dequeue까지 완료한 이벤트들을 이제 출력해본다.
	for (int i = 0; i < N_O_EVENTS; i++)
	{
		printf("Ev(id: %3d, pri: %3d), ", Processed_Events[i].event_no, Processed_Events[i].event_pri);
		if ((i + 1) % 5 == 0) //5번째마다 줄바꿈을 실행
			printf("\n");
	}
	printf("\n");
	delCirQ(pCirQ_Event); //이제 환형 큐 사용이 끝났으므로 동적할당 해제
}

void test_PriQ_Event(FILE* fout, int max_events_P_round)
{
	PriQ* pPriQ_Ev = NULL;
	Event* pEv = NULL;
	Event Processed_event[N_O_EVENTS];
	int total_P_E = 0; // processed 된 총 events
	int total_G_E = 0; // generated 된 총 events
	int num_events = 0;// 한 라운드 당 이벤트 수( = max_events_P_round)
	int num_G_R = 0; // Generated 된 Round 수
	int num_P_R = 0; // processed 된 Round 수 

	fprintf(fout, "Testing Event Handling with Priority Queue\n");
	pPriQ_Ev = (PriQ*)calloc(1, sizeof(PriQ)); // malloc보다 calloc이 안전하기 때문에 이렇게 정의했다.
	if (pPriQ_Ev == NULL) // 동적할당이 되지 않으면 오류 메세지 출력후 종료
	{
		printf("Error!! Not allocing for PriorityQueue_Event!\n");
		fclose(fout);
		exit(-1);
	}
	printf("Initializing PriorityQueue_Event of capacity (%d)\n", INIT_PriQ_SIZE);
	initPriQ_Ev(pPriQ_Ev, "PriorityQueue_Event", INIT_PriQ_SIZE); //초기값 설정

	for (int round = 0; round < MAX_ROUND; round++) //init 후 enqueue작업
	{
		fprintf(fout, "\n*** Start of round(%2d)...\n", round);
		num_G_R = 0;
		if (total_G_E < N_O_EVENTS) // Generated된 이벤트가 N_O_EVENTS( = 50)이 될때까지
		{
			num_events = max_events_P_round;
			if ((total_G_E + num_events) >= N_O_EVENTS) // 만약 Generated된 이벤트가 이미 몇개 존재할 경우
				num_events = N_O_EVENTS - total_G_E; // 그 수를 뺀 수만큼만 Generate한다.
			fprintf(fout, ">>> enque %2d events\n", num_events);
			for (int i = 0; i < num_events; i++)
			{
				pEv = genEvent(pEv, total_G_E, 0, N_O_EVENTS - total_G_E - 1); // 이벤트 생성
				if (pEv == NULL) //안되면 종료
				{
					printf("Error in generation of event !! \n");
					fclose(fout);
					exit(-1);
				}
				fprintf(fout, "*** enque event : ");
				fprintEvent(fout, pEv); // 파일에 출력
				enPriQ(pPriQ_Ev, pEv); // 이진트리 큐에 추가 및 우선순위 재정렬
				total_G_E++; // 생성된 이벤트 수 증가
				num_G_R++; // 수 증가
				fprintPriQ(fout, pPriQ_Ev); //출력
			}
		}
		fprintf(fout, "\n===========================================================================\n");
		fprintf(fout, "\nRemoving min data from Priority Queue . . . \n"); // Dequeue작업
		num_events = max_events_P_round;
		if ((total_P_E + num_events) > N_O_EVENTS)
			num_events = N_O_EVENTS - total_P_E;
		fprintf(fout, "<<< Dequeue %2d events\n", num_events);
		num_P_R = 0;
		for (int i = 0; i < num_events; i++)
		{
			pEv = dePriQ(pPriQ_Ev); // dequeue한 후, 이벤트 반환받은 것
			if (pEv == NULL) // 받은게 없다면 종료
			{
				fprintf(fout, "   PriQ is empty\n");
				break;
			}

			fprintf(fout, " *** Dequeued Event : ");
			fprintEvent(fout, pEv); // 출력
			Processed_event[total_P_E] = *pEv; // Processed된 이벤트를 따로 배열에 저장                                                               
			total_P_E++; // dequeue한 이벤트 수 증가
			num_P_R++; // 수 증가
		}
		//Monitoring Simulation Status (시뮬레이션 중인 상태를 출력 )

		fprintf(fout, "Round(%2d): Generated_in_this_round(%3d), total_Generated_Events(%3d), ", round, num_G_R, total_G_E);
		fprintf(fout, "processed_in_this_round(% 3d), total_processed_events(% 3d), ", num_P_R, total_P_E);
		fprintf(fout, "events_in_queue(%3d)\n\n", pPriQ_Ev->priQ_size);

		printf("Round(%2d): Generated_in_this_round(%3d), total_Generated_Events(%3d), ", round, num_G_R, total_G_E);
		printf("processed_in_this_round(% 3d), total_processed_events(% 3d), ", num_P_R, total_P_E);
		printf("events_in_queue(%3d)\n", pPriQ_Ev->priQ_size);

		if (total_P_E >= N_O_EVENTS)
			break;
		// 만약 Processe가 끝났다면( 모든 이벤트들을 Dequeue했다면) 반복문 중지
	}

	printf("Processed Events : \n"); //Dequeue까지 완료한 이벤트들을 이제 출력해본다.
	for (int i = 0; i < N_O_EVENTS; i++)
	{
		printf("Ev(id: %3d, pri: %3d), ", Processed_event[i].event_no, Processed_event[i].event_pri);
		if ((i + 1) % 5 == 0) //5번째마다 줄바꿈을 실행
			printf("\n");
	}
	printf("\n");
	delPriQ_Ev(pPriQ_Ev); //이제 우선순위 큐 사용이 끝났으므로 동적할당 해제

}