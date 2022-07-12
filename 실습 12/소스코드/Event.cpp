#include "Event.h"

/*Event* genEvent(Event* pEv, int ev_no, int ev_genID, int ev_pri)		// 이벤트 생성
{
	pEv = (Event*)calloc(1, sizeof(Event));								// 동적 할당 
	if (pEv == NULL) //안되면 오류매세지 출력
	{
		printf("ERROR!! Not Generated Events in memory\n");
		return NULL;
	}
	pEv->ev_no = ev_no;													// 이벤트 넘버
	pEv->ev_gen = ev_genID;												// 생성 아이디
	pEv->ev_handler = -1;												// 핸들링 되어있는지 확인하는 변수 (-1: 아직 안됨)
	pEv->ev_pri = ev_pri;												// 남은 개수

	return pEv;															// 주소 반환, free는 후에 함
}
*/

void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)					// 생성-> 처리까지 걸린 시간 측정
{
	LONGLONG t_diff;
	t_diff = pEv->ev_t_handle.QuadPart - pEv->ev_t_gen.QuadPart;
	pEv->elap_time = (double)t_diff / freq.QuadPart; 
}

void printEvent_withTime(Event* pEv)									// 이벤트를 걸린 시간과 함께 출력
{
	printf("Ev(no: %3d, pri: %2d, elap_t : %6.0lf[ms]) ", pEv->ev_no, pEv->ev_pri, pEv->elap_time * 1000);
}

void printEvent(Event* pEv)												// 이벤트 출력 함수
{
	printf("Ev(no: %3d, pri: %2d, gen: %2d, proc: %2d) ", pEv->ev_no, pEv->ev_pri,\
		pEv->ev_gen, pEv->ev_handler);
}

/*
void fprintEvent(FILE* fout, Event* pEv)								// 이벤트 출력 함수 (파일)
{
	fprintf(fout, "Ev(no: %3d, pri: %2d, gen: %2d, proc: %2d) ", \
	pEv->ev_no, pEv->ev_pri, pEv->ev_gen, pEv->ev_handler);
}
*/