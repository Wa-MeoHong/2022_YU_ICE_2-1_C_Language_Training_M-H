#include "CirQ_E.h"

CirQ* initCirQ(CirQ* pCirQ, int capacity)				// CirQ 구조체 자료형 초기값 설정
{
	Event* pEv;

	pEv = (Event*)calloc(capacity, sizeof(Event));		// 동적 할당

	if (pEv == NULL)									// 동적 할당 실패시 오류 메세지 출력
	{
		printf("ERROR!! Not Generated Events in memory\n");
		exit(-1);
	}

	//초기값 설정
	pCirQ->pEv = pEv;
	pCirQ->capacity = capacity;
	pCirQ->front = pCirQ->end = 0;
	pCirQ->num_elements = 0;
	return pCirQ;
}

void fprintCirQ(FILE* fout, CirQ* pCirQ)				// 환형큐 현황 파일 출력 함수
{
	Event ev;											// 이벤트 ( fprintEvent함수에서 쓰기 위한 변수)
	int index;											// 환형큐에서 이벤트의 순번

	fprintf(fout, " %2d Elements in CirQ_Event (index_front:%2d) :\n", pCirQ->num_elements, pCirQ->front);
	// 환형큐안에 있는 이벤트 개수, 환형 큐에서 맨 처음 이벤트의 인덱스 번호 출력 

	if (isCirQEmpty(pCirQ))								// 환형큐가 비어있는가? 비어있으면 출력
	{
		fprintf(fout, "pCirQ_Event is Empty"); 
	}
	else // 아니면
	{
		fprintf(fout, "\t");
		for (int i = 0; i < pCirQ->num_elements; i++)	// 환형 큐 안에 있는 이벤트에 대한 정보를 모두 출력
		{
			index = pCirQ->front + i;				// 환형큐 안에서 맨 첫번째 이벤트가 있는곳의 위치를 기준으로 인덱스 번호를 더하면서 위치 설정
			if (index >= pCirQ->capacity)			// 만약 인덱스 번호가 최대치(capacity)가 된다면
				// 이유는 capacity - 1까지 환형큐 배열이 생성되기 때문이다. 인덱스번호 == capacity 일 때, 나머지는 0이 된다.
				index %= pCirQ->capacity;			// 인덱스번호 0으로 초기화해준다.

			ev = pCirQ->pEv[index];					// 환형 큐 내의 이벤트들 중, 인덱스 번호에 맞는 이벤트를 가져옴
			fprintEvent(fout, &ev);					// 정보 출력
			if ((i + 1) % EVENT_PER_LINE == 0 && (i + 1) != pCirQ->num_elements) 
				fprintf(fout, "\n\t");				// 5번째 이벤트를 출력할때마다 줄바꿈을 함
		}
		fprintf(fout, "\n");						//모두 다 출력한 다음에 줄바꿈을 한번 해준다. (구분)
	}
}

bool isCirQFull(CirQ* pCirQ)					// 환형 큐의 이벤트 개수가 최대치(capacity)에 도달했는가?
{
	if (pCirQ->num_elements == pCirQ->capacity)
		return true;
	else
		return false;
}

bool isCirQEmpty(CirQ* pCirQ)					// 환형 큐의 이벤트 개수가 0개 인가?
{
	if (pCirQ->num_elements == 0)
		return true;
	else
		return false;
}

Event* enCirQ(CirQ* pCirQ, Event ev)				// 환형큐에서 이벤트 추가( FIFO이기 때문에 줄서는것 처럼 마지막에 추가됨)
{
	if (isCirQFull(pCirQ))				//환형 큐가 꽉 찼다면?
	{
		return NULL;					// enqueue 못함
	}
	//if에서 return을 취하기 때문에 따로 else는 안붙여도 됨. 왜냐하면 if문 만족시 함수가 끝남

	pCirQ->pEv[pCirQ->end] = ev; 
	// 환형 큐 안에서 마지막 번호(end = 존재하는 이벤트들 바로 다음번호)에 있는 위치에 이벤트를 생성
	pCirQ->num_elements++;						// 환형큐 내에 있는 이벤트 개수 갱신
	pCirQ->end++;								// end번호 갱신
	if (pCirQ->end == pCirQ->capacity)			// 만약 end번호가 capacity가 된다면( 환형 큐 내의 이벤트 인덱스 번호 0~capacity -1
	{
		pCirQ->end = pCirQ->end % pCirQ->capacity; // end가 0번으로 이동한다
	}

	return &(pCirQ->pEv[pCirQ->end]);			// 마지막 이벤트 주소 반환
}

Event* deCirQ(CirQ* pCirQ)							// 환형큐에서 이벤트 줄이기(FIFO이기 때문에 front가 뒤로 밀림)
{
	if (isCirQEmpty(pCirQ))						// 환형큐에 이벤트가 아예 없는가?
	{
		return NULL;							// 이벤트 줄이기가 불가능함
	}

	Event* pEv = &(pCirQ->pEv[pCirQ->front]);	// 맨 처음에 있는(front) 이벤트를 가져온다.
	pCirQ->front++;								// 이벤트 맨 처음 갱신
	if (pCirQ->front == pCirQ->capacity)		// 마찬가지로 capacity에 도달한다면
		pCirQ->front = pCirQ->front % pCirQ->capacity; // 0으로 만들어줌
	pCirQ->num_elements--;						// 이벤트 개수 갱신( 1개씩 줄어듦)

	return pEv;									// 아까 얻은 이벤트 반환
}

void delCirQ(CirQ* pCirQ)							// 환형 큐 동적할당 해제 함수 (모든 것이 끝난 후, 해제)
{
	if (pCirQ->pEv != NULL)						// 이벤트의 메모리주소가 존재한다면 pEv를 해제해줌
		free(pCirQ->pEv);						// 이유? Init에서 동적할당을 했기 때문
	pCirQ->pEv = NULL; 
	pCirQ->num_elements = 0;
	pCirQ->front = pCirQ->end = 0;
	pCirQ->num_elements = 0;
}