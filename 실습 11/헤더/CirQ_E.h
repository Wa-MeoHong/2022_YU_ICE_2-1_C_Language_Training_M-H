#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "Event.h"

// ȯ�� ť ����ü
typedef struct Circle_Queue {
	Event* pEv;
	int capacity;
	int front;
	int end;
	int num_elements;
} CirQ; 

CirQ* initCirQ(CirQ* pCirQ, int capacity);				// CirQ ����ü �ڷ��� �ʱⰪ ����
void fprintCirQ(FILE* fout, CirQ* pCirQ);				// ȯ��ť ��Ȳ ���� ��� �Լ�
bool isCirQFull(CirQ* pCirQ);							// ȯ�� ť�� �̺�Ʈ ������ �ִ�ġ(capacity)�� �����ߴ°�?
bool isCirQEmpty(CirQ* pCirQ);							// ȯ�� ť�� �̺�Ʈ ������ 0�� �ΰ�?
Event* enCirQ(CirQ* pCirQ, Event ev);					// ȯ��ť���� �̺�Ʈ �߰�( FIFO�̱� ������ �ټ��°� ó�� �������� �߰���)
Event* deCirQ(CirQ* pCirQ);								// ȯ��ť���� �̺�Ʈ ���̱�(FIFO�̱� ������ front�� �ڷ� �и�)
void delCirQ(CirQ* pCirQ);								// ȯ�� ť �����Ҵ� ���� �Լ� (��� ���� ���� ��, ����)

#endif 