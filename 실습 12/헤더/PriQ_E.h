#ifndef PRIQ_E_H
#define PRIQ_E_H

#include "Event.h"
#include <string.h>
#include <mutex>								// mutex가 C++에서만 되기 때문에 namespace를 사용해야함 (class개념)
using namespace std;

#define POS_ROOT 1								// 최우선 노드
#define MAX_NAME_LEN 80

// 완전이진트리 구조체
typedef struct CBTN_Event 
{
	int priority;								// 우선 순위
	Event Ev;									// 이벤트 활용자
} BTE; 

// 우선순위 큐 구조체 선언
typedef struct PriorityQueue 
{
	mutex cs_PriQ;								// 뮤텍스 활용자
	char PriQ_Name[MAX_NAME_LEN];				// 이름
	int priQ_capacity;							// 용량
	int priQ_size;								// 이벤트 끝부분
	int pos_last;								// 마지막위치
	BTE* pCBT_Ev;								// 완전이진트리 위치포인터
} PriQ; 

PriQ* initPriQ_Ev(PriQ* pPriQ_Ev, const char* name, int capacity);			// PriQ 초기값 설정
Event* enPriQ(PriQ* pPriQ_Ev, Event Ev);									// 노드 추가 함수
Event* dePriQ(PriQ* pPriQ_Ev);												// 최상위 노드 삭제 함수
void printPriQ(PriQ* pPriQ_Ev);												// 출력함수
//void fprintPriQ(FILE* fout, PriQ* pPriQ_Ev);								// 파일 출력 함수
void delPriQ_Ev(PriQ* pPriQ_Ev);											// 동적할당 해제 함수 

#endif // !PRIQ_E_H
