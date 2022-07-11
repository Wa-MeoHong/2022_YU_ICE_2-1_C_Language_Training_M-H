#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "Event.h"

// 환형 큐 구조체
typedef struct Circle_Queue {
	Event* pEv;
	int capacity;
	int front;
	int end;
	int num_elements;
} CirQ; 

CirQ* initCirQ(CirQ* pCirQ, int capacity);				// CirQ 구조체 자료형 초기값 설정
void fprintCirQ(FILE* fout, CirQ* pCirQ);				// 환형큐 현황 파일 출력 함수
bool isCirQFull(CirQ* pCirQ);							// 환형 큐의 이벤트 개수가 최대치(capacity)에 도달했는가?
bool isCirQEmpty(CirQ* pCirQ);							// 환형 큐의 이벤트 개수가 0개 인가?
Event* enCirQ(CirQ* pCirQ, Event ev);					// 환형큐에서 이벤트 추가( FIFO이기 때문에 줄서는것 처럼 마지막에 추가됨)
Event* deCirQ(CirQ* pCirQ);								// 환형큐에서 이벤트 줄이기(FIFO이기 때문에 front가 뒤로 밀림)
void delCirQ(CirQ* pCirQ);								// 환형 큐 동적할당 해제 함수 (모든 것이 끝난 후, 해제)

#endif 