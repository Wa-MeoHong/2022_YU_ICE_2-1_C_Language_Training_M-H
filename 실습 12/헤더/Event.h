#ifndef EVENT_H
#define EVENT_H
#pragma warning(disable: 4996)									// scanf오류 안뜨게 하는 pragma정의 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5

enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED }; 
// 이벤트 상태 enum 열겨형 자료형

typedef struct Events
{
	int ev_no; int ev_gen; int ev_handler; int ev_pri;			// 이벤트의 구조들 
	LARGE_INTEGER ev_t_gen; 
	LARGE_INTEGER ev_t_handle; 
	double elap_time;											// 이벤트의 생성, 활용된 시간을 측정하는 것들
	EventStatus eventStatus;									// 현재 이벤트의 상태
} Event;

//Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri);		// 이벤트 생성 함수
void printEvent(Event* pEv);												// 이벤트 출력 함수
//void fprintEvent(FILE* fout, Event* pEv);									// 이벤트 파일 출력 함수
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq);						// 시간 계산 함수
void printEvent_withTime(Event* pEv);										// 시간과 함께 이벤트 출력
#endif