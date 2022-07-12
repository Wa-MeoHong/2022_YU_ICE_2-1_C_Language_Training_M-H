#ifndef EVENT_H
#define EVENT_H
#pragma warning(disable: 4996)									// scanf���� �ȶ߰� �ϴ� pragma���� 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5

enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED }; 
// �̺�Ʈ ���� enum ������ �ڷ���

typedef struct Events
{
	int ev_no; int ev_gen; int ev_handler; int ev_pri;			// �̺�Ʈ�� ������ 
	LARGE_INTEGER ev_t_gen; 
	LARGE_INTEGER ev_t_handle; 
	double elap_time;											// �̺�Ʈ�� ����, Ȱ��� �ð��� �����ϴ� �͵�
	EventStatus eventStatus;									// ���� �̺�Ʈ�� ����
} Event;

//Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri);		// �̺�Ʈ ���� �Լ�
void printEvent(Event* pEv);												// �̺�Ʈ ��� �Լ�
//void fprintEvent(FILE* fout, Event* pEv);									// �̺�Ʈ ���� ��� �Լ�
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq);						// �ð� ��� �Լ�
void printEvent_withTime(Event* pEv);										// �ð��� �Բ� �̺�Ʈ ���
#endif