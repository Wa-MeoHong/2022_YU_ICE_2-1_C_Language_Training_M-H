

#ifndef EVENT_H
#define EVENT_H
#pragma warning(disable: 4996)			// scanf오류 안뜨게 하는 pragma정의 

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "SimParam.h"
#include "ConsoleDisplay.h"

typedef enum E_Stat 
{ GENERATED, ENQUEUED, PROCESSED, UNDEFINED 
} E_Stat;								// 이벤트 상태 enum 열거형 변수

// 이벤트 구조체
typedef struct Event
{
	int ev_no;							// 이벤트의 정보들
	int ev_gen_addr;
	int ev_han_addr;
	int ev_pri;
	LARGE_INTEGER t_gen;				// 이벤트가 생성된 시간 측정용
	LARGE_INTEGER t_proc;				// 이벤트가 처리된 시간 측정용
	double elapsed;						// 생성 - 처리되기까지 시간 측정
	E_Stat ev_stat;						// 현재 이벤트 상태 (생성, 삽입, 처리, 정의되지 않음)
} Event;

void printEvent(Event* pEv);								// 이벤트 출력
void printEvent_withTime(Event* pEvt);						// 이벤트 출력 (시간 포함)
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq);		// 이벤트 생성 - 처리까지 걸린 시간

#endif // !EVENT_H
