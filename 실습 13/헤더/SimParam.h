#ifndef SIMULATION_PARAMETER_H
#define SIMULATION_PARAMETER_H

#define NUM_EVENT_GENERATORS 3										// �̺�Ʈ ���ʷ����� ������ ����
#define NUM_EV_PER_GEN 20											// ������ ������� �����ϴ� �̺�Ʈ ����
#define NUM_EVENT_HANDLERS 2										// �̺�Ʈ �ڵ鷯 ������ ����
#define TOTAL_NUM_EVENTS (NUM_EV_PER_GEN * NUM_EVENT_GENERATORS)	// �� ������� ����� �̺�Ʈ ���� * ������ ����
#define PLUS_INF INT_MAX
#define MAX_ROUND 100												// ���带 �ִ� ��� �����°�

#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3										// 0 ~ 2 : high priority, 3 ~ 9 : low priority
#define EVENT_PER_LINE 5											// �� �ٴ� ����ϴ� �̺�Ʈ ����

#endif // !SIMULATION_PARAMETER_H
