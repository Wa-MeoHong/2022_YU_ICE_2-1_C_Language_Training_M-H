#include "Event.h"

/*Event* genEvent(Event* pEv, int ev_no, int ev_genID, int ev_pri)		// �̺�Ʈ ����
{
	pEv = (Event*)calloc(1, sizeof(Event));								// ���� �Ҵ� 
	if (pEv == NULL) //�ȵǸ� �����ż��� ���
	{
		printf("ERROR!! Not Generated Events in memory\n");
		return NULL;
	}
	pEv->ev_no = ev_no;													// �̺�Ʈ �ѹ�
	pEv->ev_gen = ev_genID;												// ���� ���̵�
	pEv->ev_handler = -1;												// �ڵ鸵 �Ǿ��ִ��� Ȯ���ϴ� ���� (-1: ���� �ȵ�)
	pEv->ev_pri = ev_pri;												// ���� ����

	return pEv;															// �ּ� ��ȯ, free�� �Ŀ� ��
}
*/

void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)					// ����-> ó������ �ɸ� �ð� ����
{
	LONGLONG t_diff;
	t_diff = pEv->ev_t_handle.QuadPart - pEv->ev_t_gen.QuadPart;
	pEv->elap_time = (double)t_diff / freq.QuadPart; 
}

void printEvent_withTime(Event* pEv)									// �̺�Ʈ�� �ɸ� �ð��� �Բ� ���
{
	printf("Ev(no: %3d, pri: %2d, elap_t : %6.0lf[ms]) ", pEv->ev_no, pEv->ev_pri, pEv->elap_time * 1000);
}

void printEvent(Event* pEv)												// �̺�Ʈ ��� �Լ�
{
	printf("Ev(no: %3d, pri: %2d, gen: %2d, proc: %2d) ", pEv->ev_no, pEv->ev_pri,\
		pEv->ev_gen, pEv->ev_handler);
}

/*
void fprintEvent(FILE* fout, Event* pEv)								// �̺�Ʈ ��� �Լ� (����)
{
	fprintf(fout, "Ev(no: %3d, pri: %2d, gen: %2d, proc: %2d) ", \
	pEv->ev_no, pEv->ev_pri, pEv->ev_gen, pEv->ev_handler);
}
*/