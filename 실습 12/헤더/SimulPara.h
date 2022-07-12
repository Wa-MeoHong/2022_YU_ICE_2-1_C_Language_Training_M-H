#ifndef SIMULATION_PARAMETERS_H 
#define SIMULATION_PARAMETERS_H
// 쓰레드 파라미터 시뮬레이터에 필요한 define된 상수들 헤더파일

#define NUM_EVENT_GENERATORS 1							// 제너레이터 수
#define NUM_EVENTS_PER_GEN 50							// 이벤트 생성 한게
#define NUM_EVENT_HANDLERS 1 

#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)	// 49

#define PRI_QUEUE_CAPACITY 1
#define PLUS_INF INT_MAX
#define MAX_ROUND 1000									// MAX_ROUND 가 50이 아닌 이유 : 제너레이터 하면서 값이 없을 수 있음.

#endif