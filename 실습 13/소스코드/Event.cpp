#include "Event.h"

void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)		// 생성-> 처리까지 걸린 시간 측정
{
	LONGLONG t_diff;										// LONGLONG 자료형 = 64비트 실수형 자료형
	t_diff = pEv->t_proc.QuadPart - pEv->t_gen.QuadPart;
	pEv->elapsed = (double)t_diff / freq.QuadPart;
}

void printEvent_withTime(Event* pEvt)						// 이벤트를 걸린 시간과 함께 출력
{
	printf("Ev(no: %3d, pri: %2d, elap_t : %6.0lf[ms]) ", pEvt->ev_no, pEvt->ev_pri, pEvt->elapsed * 1000);
}

void printEvent(Event* pEv)									// 이벤트 출력 함수
{
	printf("Ev(no: %3d, pri: %2d, gen: %2d, proc: %2d) ", pEv->ev_no, pEv->ev_pri, pEv->ev_gen_addr, pEv->ev_han_addr);
}