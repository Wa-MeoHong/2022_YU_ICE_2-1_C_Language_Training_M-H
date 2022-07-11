#include "Event.h"

Event* genEvent(Event* pEv, int ev_no, int ev_genID, int ev_pri)		// 이벤트 생성
{
	pEv = (Event*)calloc(1, sizeof(Event));					// 동적 할당 
	if (pEv == NULL)										// 안되면 오류매세지 출력
	{
		printf("ERROR!! Not Generated Events in memory\n");
		exit(-1);
	}
	
	// 초기값 설정
	pEv->event_no = ev_no;									// 이벤트 넘버
	pEv->event_gen_addr = ev_genID;							// 생성 아이디
	pEv->event_pri = ev_pri;								// 남은 개수

	return pEv;												// 주소 반환, free는 후에 함
}

void printEvent(Event* pEv)								// 이벤트 출력 함수
{
	printf("Ev(no: %3d, pri: %2d) ", pEv->event_no, pEv->event_pri);
}

void fprintEvent(FILE* fout, Event* pEv)				// 이벤트 출력 함수 (파일)
{
	fprintf(fout, "Ev(no:%3d, pri:%2d) ", pEv->event_no, pEv->event_pri);
}