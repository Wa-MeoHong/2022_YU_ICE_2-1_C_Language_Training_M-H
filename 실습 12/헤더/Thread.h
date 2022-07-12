#ifndef THREAD_H
#define THREAD_H

#include "PriQ_E.h"
#include "SimulPara.h"
#define THREAD_RETURN_CODE 7

enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

// ������ ���� ����͸�
typedef struct ThreadStatusMonitor 
{
	int num_G_E;								// ������ �̺�Ʈ�� ��
	int num_P_E;								// ó���� �̺�Ʈ�� ��
	int total_G_E;								// �� ������ �̺�Ʈ ��
	int total_P_E;								// �� ó���� �̺�Ʈ ��
	Event eventGenerated[TOTAL_NUM_EVENTS];		// used for monitoring only
	Event eventProcessed[TOTAL_NUM_EVENTS];		// used for monitoring only
	THREAD_FLAG* pFlagThreadTerminate;			// �������
} T_Stat_M;

// ������ ����
typedef struct ThreadParam_Event
{
	mutex* pMTX_main;							// ���� ���ؽ�
	mutex* pMTX_thrd_mon;						// ������ ���ؽ� ����͸���
	PriQ* pPriQ_Event;							// �۾��� �� ť
	ROLE role;									// ���� �����尡 ���� ����
	int myAddr;									// ���� �ּ�
	int maxRound;								// �ִ� ����
	int targetEventGen;							// ������ �� �̺�Ʈ ����
	T_Stat_M* pThrdMon;							// ������ ����
} TPE;

void Thread_EventGenerator(TPE* pParam);		// �̺�Ʈ ���ʷ�����(����)�Լ�
void Thread_EventHandler(TPE* pParam);			// �̺�Ʈ ó���Լ�

#endif