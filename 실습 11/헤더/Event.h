#ifndef EVENT_H
#define EVENT_H
#pragma warning(disable: 4996)						// scanf���� �ȶ߰� �ϴ� pragma���� 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>								// C���� bool �ڷ����� �߰��ϴ� �������

//main.c���� ���� define�� ������
#define EVENT_GENERATOR 0
#define N_O_EVENTS 50							// �̺�Ʈ �ִ� ����
#define MAX_ROUND 100

//Event.c���� ���� define�� ������
#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5
#define SIZE_DESCRIPTION 2048
#define INIT_PriQ_SIZE 1

// Event ����ü ����
typedef struct EVENTS {
	int event_no;								// �̺�Ʈ �ѹ�
	int event_gen_addr;							// �̺�Ʈ ���� �ּ�
	int event_pri;								 // �̺�Ʈ �켱����
} Event; 

Event* genEvent(Event* pEv, int ev_no, int ev_genID, int ev_pri);		// Event ���� �Լ�
void printEvent(Event* pEv);											// �̺�Ʈ ��� �Լ�
void fprintEvent(FILE* fout, Event* pEv);								// ���� ����Լ�

#endif 