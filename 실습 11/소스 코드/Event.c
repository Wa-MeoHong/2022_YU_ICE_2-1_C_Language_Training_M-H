#include "Event.h"

Event* genEvent(Event* pEv, int ev_no, int ev_genID, int ev_pri)		// �̺�Ʈ ����
{
	pEv = (Event*)calloc(1, sizeof(Event));					// ���� �Ҵ� 
	if (pEv == NULL)										// �ȵǸ� �����ż��� ���
	{
		printf("ERROR!! Not Generated Events in memory\n");
		exit(-1);
	}
	
	// �ʱⰪ ����
	pEv->event_no = ev_no;									// �̺�Ʈ �ѹ�
	pEv->event_gen_addr = ev_genID;							// ���� ���̵�
	pEv->event_pri = ev_pri;								// ���� ����

	return pEv;												// �ּ� ��ȯ, free�� �Ŀ� ��
}

void printEvent(Event* pEv)								// �̺�Ʈ ��� �Լ�
{
	printf("Ev(no: %3d, pri: %2d) ", pEv->event_no, pEv->event_pri);
}

void fprintEvent(FILE* fout, Event* pEv)				// �̺�Ʈ ��� �Լ� (����)
{
	fprintf(fout, "Ev(no:%3d, pri:%2d) ", pEv->event_no, pEv->event_pri);
}