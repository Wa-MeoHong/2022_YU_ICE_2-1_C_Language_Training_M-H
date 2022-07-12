#include "Event.h"

void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)		// ����-> ó������ �ɸ� �ð� ����
{
	LONGLONG t_diff;										// LONGLONG �ڷ��� = 64��Ʈ �Ǽ��� �ڷ���
	t_diff = pEv->t_proc.QuadPart - pEv->t_gen.QuadPart;
	pEv->elapsed = (double)t_diff / freq.QuadPart;
}

void printEvent_withTime(Event* pEvt)						// �̺�Ʈ�� �ɸ� �ð��� �Բ� ���
{
	printf("Ev(no: %3d, pri: %2d, elap_t : %6.0lf[ms]) ", pEvt->ev_no, pEvt->ev_pri, pEvt->elapsed * 1000);
}

void printEvent(Event* pEv)									// �̺�Ʈ ��� �Լ�
{
	printf("Ev(no: %3d, pri: %2d, gen: %2d, proc: %2d) ", pEv->ev_no, pEv->ev_pri, pEv->ev_gen_addr, pEv->ev_han_addr);
}