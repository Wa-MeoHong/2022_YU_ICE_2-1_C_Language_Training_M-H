#ifndef SIMULATION_PARAMETER_H
#define SIMULATION_PARAMETER_H

#define NUM_EVENT_GENERATORS 3										// 이벤트 제너레이터 쓰레드 개수
#define NUM_EV_PER_GEN 20											// 생성기 쓰레드당 생성하는 이벤트 개수
#define NUM_EVENT_HANDLERS 2										// 이벤트 핸들러 쓰레드 개수
#define TOTAL_NUM_EVENTS (NUM_EV_PER_GEN * NUM_EVENT_GENERATORS)	// 한 쓰레드당 만드는 이벤트 개수 * 쓰레드 개수
#define PLUS_INF INT_MAX
#define MAX_ROUND 100												// 라운드를 최대 몇번 돌리는가

#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3										// 0 ~ 2 : high priority, 3 ~ 9 : low priority
#define EVENT_PER_LINE 5											// 한 줄당 출력하는 이벤트 개수

#endif // !SIMULATION_PARAMETER_H
