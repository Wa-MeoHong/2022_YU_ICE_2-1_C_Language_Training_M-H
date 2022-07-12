#ifndef PRIQ_E_H
#define PRIQ_E_H

#include "Event.h"
#include <string.h>
#include <mutex>								// mutex�� C++������ �Ǳ� ������ namespace�� ����ؾ��� (class����)
using namespace std;

#define POS_ROOT 1								// �ֿ켱 ���
#define MAX_NAME_LEN 80

// ��������Ʈ�� ����ü
typedef struct CBTN_Event 
{
	int priority;								// �켱 ����
	Event Ev;									// �̺�Ʈ Ȱ����
} BTE; 

// �켱���� ť ����ü ����
typedef struct PriorityQueue 
{
	mutex cs_PriQ;								// ���ؽ� Ȱ����
	char PriQ_Name[MAX_NAME_LEN];				// �̸�
	int priQ_capacity;							// �뷮
	int priQ_size;								// �̺�Ʈ ���κ�
	int pos_last;								// ��������ġ
	BTE* pCBT_Ev;								// ��������Ʈ�� ��ġ������
} PriQ; 

PriQ* initPriQ_Ev(PriQ* pPriQ_Ev, const char* name, int capacity);			// PriQ �ʱⰪ ����
Event* enPriQ(PriQ* pPriQ_Ev, Event Ev);									// ��� �߰� �Լ�
Event* dePriQ(PriQ* pPriQ_Ev);												// �ֻ��� ��� ���� �Լ�
void printPriQ(PriQ* pPriQ_Ev);												// ����Լ�
//void fprintPriQ(FILE* fout, PriQ* pPriQ_Ev);								// ���� ��� �Լ�
void delPriQ_Ev(PriQ* pPriQ_Ev);											// �����Ҵ� ���� �Լ� 

#endif // !PRIQ_E_H
