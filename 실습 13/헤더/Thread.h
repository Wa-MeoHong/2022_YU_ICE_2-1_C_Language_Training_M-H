#ifndef THREAD_H
#define THREAD_H

#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include "Event.h"
#include "SimParam.h"
#include "DLL_EvQ.h"

using namespace std;			// c++���� ���Ǵ� mutex, thread�� ���ӽ����̽��� ����Ѵ�. ���� �������ָ� std�� ���� �ʿ� ����

typedef enum ROLE {	EVENT_GENERATOR, EVENT_HANDLER } ROLE;				// �������� ������ enum���� ����
typedef enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE } THREAD_FLAG;	// ������ ���� 

// ������ ���� ����͸� ����ü
typedef struct ThreadStatMon 
{
	int eventGen[NUM_EVENT_GENERATORS];					// ���ʷ����� ���̵�� �̺�Ʈ�� � �����Ǿ��°�
	int eventProc[NUM_EVENT_HANDLERS];					// �ڵ鷯 ���̵�
	int total_G_E;										// �� ������ �̺�Ʈ ���� (total generated events)
	int total_P_E;										// �� ó���� �̺�Ʈ ���� (total processed events)
	int num_P_E_H;						// �켱���� ���� �̺�Ʈ�� �� ó���� �̺�Ʈ �� ( Number of Processed Event in High Priority)
	int num_P_E_L;						// �켱���� ���� �̺�Ʈ�� �� ó���� �̺�Ʈ �� ( Number of Processed Event in Low Priority)
	THREAD_FLAG* pFlagThreadTerminated; // �̺�Ʈ�� terminated(����) �Ǿ����� Ȯ��
	Event ev_Generated[TOTAL_NUM_EVENTS];				// ������ �̺�Ʈ�� ��� �迭
	Event ev_Processed[TOTAL_NUM_EVENTS];				// ó���� �̺�Ʈ�� ��� �迭
} T_Stat; 

// �������� �Ķ���� ����ü
typedef struct ThreadParam_Event 
{
	FILE* fout;											// ��¿� ���� ����
	mutex* pCS_main;									// �����Լ��� �� mutex
	mutex* pCS_thrd_mon;								// �����忡 �� mutex
	DLL_EvQ* EvQ_PriH;									// �켱������ ���� ť�� ������( �����忡 ��� �ϱ� ����)
	DLL_EvQ* EvQ_PriL;									// �켱������ ���� ť�� ������( �� ���� ����)
	ROLE role;											// �� �������� ���� ( �̺�Ʈ ������, �̺�Ʈ ó���� )
	int myAddr;
	int maxRound;
	int targetEventGen; 
	LARGE_INTEGER freq;									// ��ǻ�� CPU�� Ŭ�� �� ����
	T_Stat* pThrdMon;									// �������� ���� 
} T_P_Ev;

void Thread_EventGenerator(T_P_Ev* pParam);				// �̺�Ʈ ������ ������ �Լ�
void Thread_EventHandler(T_P_Ev* pParam);				// �̺�Ʈ ó���� ������ �Լ�

#endif // !THREAD_H
