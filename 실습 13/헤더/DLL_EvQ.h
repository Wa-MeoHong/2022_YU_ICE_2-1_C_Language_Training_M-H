#ifndef LinkedList_QUEUE_H
#define LinkedList_QUEUE_H

#include <Windows.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include "Event.h"
#include "SimParam.h"

using namespace std;

// 자기 참조 구조체 형태의 노드 (DLLN)
typedef struct DLLN
{
	struct DLLN* next;							// 자기참조구조체포인터 next (다음 노드를 찍음)
	struct DLLN* prev;							// 자기참조 구조체 포인터 prev ( 이전 노드를 찍음)
	Event* pEv;									// DLLN안에 있는 이벤트 하나
} DLLN_Ev;

// 자기 참조 구조체 형태의 큐
typedef struct DLL_Event_Queue
{
	mutex cs_EvQ;								// 이 큐의 mutex (잠금이)
	int priority;								// 우선순위
	DLLN_Ev* front;								// 이 큐에서 가장 맨앞에 있는 자기참조 구조체
	DLLN_Ev* back;								// 이 큐에서 가장 맨 뒤에있는 자기참조 구조체
	int num_Ev;									// 이 큐에서 이벤트 개수
} DLL_EvQ;

void initDLL_EvQ(DLL_EvQ* pEvQ, int pri);		// 이벤트 큐 초기값 설정
Event* enDLL_EvQ(DLL_EvQ* pEvQ, Event* pEv);	// enqueue를 자기참조 구조체형으로 만듦
Event* deDLL_EvQ(DLL_EvQ* pEvQ);				// dequeue를 자기참조 구조체 형으로 만듦
void printDLL_EvQ(DLL_EvQ* pEvQ);				// 이벤트 큐 출력

#endif // !LinkedList_QUEUE_H
