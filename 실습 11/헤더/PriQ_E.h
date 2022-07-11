#ifndef PRIQ_E_H
#define PRIQ_E_H

#include "Event.h"
#include <string.h>

#define POS_ROOT 1
#define MAX_NAME_LEN 80

// 이진트리 이벤트 노드 구조체
typedef struct CBTN_Event{
	int priority;
	Event* pEv;
}CBTN_Event;

// 우선순위 큐 구조체
typedef struct PriorityQueue {
	char PriQ_Name[MAX_NAME_LEN];				// 큐 이름
	int priQ_capacity;							// 큐의 용량
	int priQ_size;								// 이진트리 사이즈(노드 개수)
	int pos_last;								// 마지막 노드
	CBTN_Event* pCBT_Ev;						// 이벤트
} PriQ;

bool hasLeftChild(int pos, PriQ* pPriQ_Ev);						// 부모노드가 왼쪽 자식노드를 가지고 있는가?
bool hasRightChild(int pos, PriQ* pPriQ_Ev);					// 부모노드가 오른쪽 자식노드를 가지고 있는가?
PriQ* initPriQ_Ev(PriQ* pPriQ_Ev, char* name, int capacity);	// PriQ 초기값 설정
void delPriQ_Ev(PriQ* pPriQ_Ev);								// 동적할당 해제 함수 
void enPriQ(PriQ* pPriQ_Ev, Event* pEv);						// 노드 추가 함수
Event* dePriQ(PriQ* pPriQ_Ev);									// 최상위 노드 삭제 함수
void fprintPriQ(FILE* fout, PriQ* pPriQ_Ev);					// 파일 출력 함수

#endif // !PRIQ_E_H
