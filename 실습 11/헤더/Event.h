#ifndef EVENT_H
#define EVENT_H
#pragma warning(disable: 4996)						// scanf오류 안뜨게 하는 pragma정의 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>								// C에서 bool 자료형을 추가하는 헤더파일

//main.c에서 쓰는 define된 변수들
#define EVENT_GENERATOR 0
#define N_O_EVENTS 50							// 이벤트 최대 개수
#define MAX_ROUND 100

//Event.c에서 쓰는 define된 변수들
#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5
#define SIZE_DESCRIPTION 2048
#define INIT_PriQ_SIZE 1

// Event 구조체 선언
typedef struct EVENTS {
	int event_no;								// 이벤트 넘버
	int event_gen_addr;							// 이벤트 생성 주소
	int event_pri;								 // 이벤트 우선순위
} Event; 

Event* genEvent(Event* pEv, int ev_no, int ev_genID, int ev_pri);		// Event 생성 함수
void printEvent(Event* pEv);											// 이벤트 출력 함수
void fprintEvent(FILE* fout, Event* pEv);								// 파일 출력함수

#endif 