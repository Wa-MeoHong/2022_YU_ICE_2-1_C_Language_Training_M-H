#ifndef SIMULATION_PARAMETERS_H 
#define SIMULATION_PARAMETERS_H
// ������ �Ķ���� �ùķ����Ϳ� �ʿ��� define�� ����� �������

#define NUM_EVENT_GENERATORS 1							// ���ʷ����� ��
#define NUM_EVENTS_PER_GEN 50							// �̺�Ʈ ���� �Ѱ�
#define NUM_EVENT_HANDLERS 1 

#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)	// 49

#define PRI_QUEUE_CAPACITY 1
#define PLUS_INF INT_MAX
#define MAX_ROUND 1000									// MAX_ROUND �� 50�� �ƴ� ���� : ���ʷ����� �ϸ鼭 ���� ���� �� ����.

#endif