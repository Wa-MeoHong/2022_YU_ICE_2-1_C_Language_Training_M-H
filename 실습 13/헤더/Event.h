

#ifndef EVENT_H
#define EVENT_H
#pragma warning(disable: 4996)			// scanf���� �ȶ߰� �ϴ� pragma���� 

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "SimParam.h"
#include "ConsoleDisplay.h"

typedef enum E_Stat 
{ GENERATED, ENQUEUED, PROCESSED, UNDEFINED 
} E_Stat;								// �̺�Ʈ ���� enum ������ ����

// �̺�Ʈ ����ü
typedef struct Event
{
	int ev_no;							// �̺�Ʈ�� ������
	int ev_gen_addr;
	int ev_han_addr;
	int ev_pri;
	LARGE_INTEGER t_gen;				// �̺�Ʈ�� ������ �ð� ������
	LARGE_INTEGER t_proc;				// �̺�Ʈ�� ó���� �ð� ������
	double elapsed;						// ���� - ó���Ǳ���� �ð� ����
	E_Stat ev_stat;						// ���� �̺�Ʈ ���� (����, ����, ó��, ���ǵ��� ����)
} Event;

void printEvent(Event* pEv);								// �̺�Ʈ ���
void printEvent_withTime(Event* pEvt);						// �̺�Ʈ ��� (�ð� ����)
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq);		// �̺�Ʈ ���� - ó������ �ɸ� �ð�

#endif // !EVENT_H
