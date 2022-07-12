#include "PriQ_E.h"

bool hasLeftChild(int pos, PriQ* pPriQ_Ev)						// 부모노드가 왼쪽 자식노드를 가지고 있는가?
{
	if (pos * 2 <= pPriQ_Ev->priQ_size)
		return true;
	else
		return false;
}

bool hasRightChild(int pos, PriQ* pPriQ_Ev)						// 부모노드가 오른쪽 자식노드를 가지고 있는가?
{
	if (pos * 2 + 1 <= pPriQ_Ev->priQ_size)
		return true;
	else
		return false;
}

PriQ* initPriQ_Ev(PriQ* pPriQ_Ev, const char* name, int capacity = 1) // PriQ 초기값 설정
{
	pPriQ_Ev->cs_PriQ.lock();

	strcpy(pPriQ_Ev->PriQ_Name, name);						// 이진트리 큐의 이름
	pPriQ_Ev->priQ_capacity = capacity;						// 용량 
	pPriQ_Ev->pCBT_Ev = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event)); // 동적할당해준 후 주소
	pPriQ_Ev->priQ_size = 0;								// 이진트리 사이즈(노드 개수)
	pPriQ_Ev->pos_last = 0;									// 가장 마지막 노드

	pPriQ_Ev->cs_PriQ.unlock();
	return pPriQ_Ev;
}

Event* enPriQ(PriQ* pPriQ_Ev, Event Ev)						// 노드 추가 함수
{
	int pos, pos_Parent;									// pos = 추가된 노드의 위치, pos_Parent
	CBTN_Event CBTN_Ev_tmp;									// 노드 추가 후, 우선순위를 바꾸기 위한 변수

	pPriQ_Ev->cs_PriQ.lock();								// 쓰레드 잠금 
	if (pPriQ_Ev->priQ_size >= pPriQ_Ev->priQ_capacity)		// 만약 용량보다 size가 더 많을때
	{
		CBTN_Event* newCBT_E;
		int newCapacity;
		// 새롭게 용량를 확장한다. (2배 크기로)

		newCapacity = 2 * pPriQ_Ev->priQ_capacity;			// 새로운 용량 설정
		newCBT_E = (CBTN_Event*)calloc((newCapacity + 1), sizeof(CBTN_Event)); // 동적할당
		if (newCBT_E == NULL)
		{
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!\n");
			exit(-1);
		}

		for (int pos = 1; pos <= pPriQ_Ev->priQ_size; pos++)
		{
			newCBT_E[pos] = pPriQ_Ev->pCBT_Ev[pos];
		} //모든 노드들을 새롭게 만든 트리에 복사해준다.
		free(pPriQ_Ev->pCBT_Ev);							// 기존의 이진트리큐를 동적할당 해제
		pPriQ_Ev->pCBT_Ev = newCBT_E;						// 새롭게 만든 이진트리큐의 주소를 반환
		pPriQ_Ev->priQ_capacity = newCapacity;				// 용량도 새롭게 갱신
	}

	pos = pPriQ_Ev->pos_last = ++pPriQ_Ev->priQ_size;		// 이제 노드가 추가됨에 따라 pos(마지막 노드 위치)를 갱신
	pPriQ_Ev->pCBT_Ev[pos].priority = Ev.ev_pri;			// priority를 추가해줌
	pPriQ_Ev->pCBT_Ev[pos].Ev = Ev;							// 이벤트 메모리 주소도 갱신

	while (pos != POS_ROOT)									// 추가된 노드의 우선순위에 따라 버블 정렬을 통한 위치 재정립
	{
		pos_Parent = pos / 2; // 자식노드 = 부모노드 * 2이기 때문, 만약 자식노드가 부모 *2 +1 이여도, 내림연산에 의해 부모노드가 같음
		if (pPriQ_Ev->pCBT_Ev[pos].priority > pPriQ_Ev->pCBT_Ev[pos_Parent].priority)
		{
			break;											// 만약 부모노드가 자식노드보다 우선순위가 작다면? 변경하지 않는다
		}
		else							// 아니면 바꿔준다. (언제까지? 추가된 노드의 위치가 최상위 노드(1)이 될때까지
		{
			CBTN_Ev_tmp = pPriQ_Ev->pCBT_Ev[pos_Parent];	// 노드 임시변수를 이용해 정렬
			pPriQ_Ev->pCBT_Ev[pos_Parent] = pPriQ_Ev->pCBT_Ev[pos];
			pPriQ_Ev->pCBT_Ev[pos] = CBTN_Ev_tmp;
			pos = pos_Parent;
		}
	}
	pPriQ_Ev->cs_PriQ.unlock();								// 쓰레드 잠금 해제 
	return &(pPriQ_Ev->pCBT_Ev[pPriQ_Ev->pos_last].Ev);		// 반환
}

Event* dePriQ(PriQ* pPriQ_Ev)								// 최상위 노드 삭제 함수
{
	Event* pEv;												// 삭제할 노드를 담을 임시변수
	CBTN_Event CBTN_Ev_tmp;
	int pos, pos_last, pos_child;							// 노드관련 변수

	if (pPriQ_Ev->priQ_size <= 0)							// 만약 size가 0이하라면 
	{
		return NULL;										// Priority Queue 가 비어있음. 따라서 할 이유가 없음
	}

	pPriQ_Ev->cs_PriQ.lock();
	pEv = (Event*)calloc(1, sizeof(Event)); 

	*pEv = pPriQ_Ev->pCBT_Ev[POS_ROOT].Ev;					// 가장 최상위위치에 있는 노드의 위치를 가져옴
	pos_last = pPriQ_Ev->priQ_size;							// 마지막노드의 인덱스 위치를 복사해줌
	--pPriQ_Ev->priQ_size;									// 노드 개수가 1개 줄었기 때문에 사이즈 1개 빼기
	if (pPriQ_Ev->priQ_size > 0)
	{
		pPriQ_Ev->pCBT_Ev[POS_ROOT] = pPriQ_Ev->pCBT_Ev[pos_last]; // 최상위 노드에 기존의 마지막 노드를 붙여넣기
		pos_last--;											// 이제 마지막 노드의 위치를 갱신,

		// 이제 최상위 노드에서 우선순위 재정립
		pos = POS_ROOT;										// 최상위 비트를 아래로 내릴것. 따라서 1부터 시작
		while (hasLeftChild(pos, pPriQ_Ev))					// 자식노드가 있다? 아래를 진행함.
		{
			pos_child = pos * 2;							// 자식노드의 위치 얻음 (자식 노드 = 부모노드 *2 (왼쪽))
			if (hasRightChild(pos, pPriQ_Ev))				// 만약 오른쪽노드도 있으면
			{
				if (pPriQ_Ev->pCBT_Ev[pos_child].priority > pPriQ_Ev->pCBT_Ev[pos_child + 1].priority)
					pos_child = pos * 2 + 1; 
				// 만약 오른쪽 자식노드가 왼쪽 자식노드보다 우선순위가 높다면 비교할 자식노드는 오른쪽으로 갱신
			}

			// 이제, 부모,자식노드간 우선순위 확인 후 재정립
			if (pPriQ_Ev->pCBT_Ev[pos_child].priority < pPriQ_Ev->pCBT_Ev[pos].priority) // 만약 자식이 부모보다 우선순위가 높다면
			{
				CBTN_Ev_tmp = pPriQ_Ev->pCBT_Ev[pos];		// 교체
				pPriQ_Ev->pCBT_Ev[pos] = pPriQ_Ev->pCBT_Ev[pos_child];
				pPriQ_Ev->pCBT_Ev[pos_child] = CBTN_Ev_tmp;
			}
			else											// 아니면 바로 while문 종료
			{
				break;
			}
			pos = pos_child;								// 다시 기존의마지막 노드( 최상위 비트갔다가 내려오는중) 위치 찾음
		}
	}
	pPriQ_Ev->cs_PriQ.unlock();								// 쓰레드 잠금 해제
	return pEv;												// 반환
}

void printPriQ(PriQ* pPriQ_Ev)								// 출력 함수
{
	int pos = 1, count = 1;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;

	if (pPriQ_Ev->priQ_size == 0)							// 만약 size가 0 이라면(노드가 없다면)
	{
		printf("PriorityQueue_Event is empty !!\n");
		return;
	} // 바로 끝냄

	printf("\n CompBinTree :\n");							// 이진트리 파일에 출력
	while (count <= pPriQ_Ev->priQ_size)
	{
		printf(" level%2d : ", level);
		for (int i = 0; i < level_count; i++)				// 만약 level_count 가 라인개수를 넘지 않았을때.
		{
			pEv = &(pPriQ_Ev->pCBT_Ev[pos].Ev);				// 이벤트 주소 복사
			eventPriority = pEv->ev_pri;					// 이벤트 우선순위 복사
			printEvent(pEv);								// 출력
			pos++;
			if ((count % EVENT_PER_LINE) == 0)				// 만약 5개가 출력되었다면
				printf("\n");
			count++;
			if (count > pPriQ_Ev->priQ_size)				// 만약 count 가 size를 넘기면 끝
				break;
		}
		printf("\n");
		level++;											// 자식노드방향으로 밑줄로 내려감
		level_count *= 2;									// 자식노드들은 내려갈수록 개수가 2개씩 곱으로 증가함.
	}
	printf("\n");
}

/*void fprintPriQ(FILE* fout, PriQ* pPriQ_Ev)				// 파일 출력 함수
{
	int pos = 1, count = 1;
	int eventpriority;
	int level = 0, level_count = 1;
	event* pev;

	if (ppriq_ev->priq_size == 0)							// 만약 size가 0 이라면(노드가 없다면)
	{
		fprintf(fout, "priorityqueue_event is empty !!\n");
		return;
	} // 바로 끝냄

	fprintf(fout, "\n compbintree :\n");					// 이진트리 파일에 출력
	while (count <= ppriq_ev->priq_size)
	{
		fprintf(fout, " level%2d : ", level);
		for(int i = 0; i < level_count; i++)				// 만약 level_count 가 라인개수를 넘지 않았을때.
		{
			pev = &(ppriq_ev->pcbt_ev[pos].ev);				// 이벤트 주소 복사
			eventpriority = pev->ev_pri;					// 이벤트 우선순위 복사
			fprintevent(fout, pev);							// 출력
			pos++;
			if ((count % event_per_line) == 0)				// 만약 5개가 출력되었다면
				fprintf(fout, "\n");
			count++;
			if (count > ppriq_ev->priq_size)				// 만약 count 가 size를 넘기면 끝
				break;
		}
		fprintf(fout, "\n");
		level++;											// 자식노드방향으로 밑줄로 내려감
		level_count *= 2;									// 자식노드들은 내려갈수록 개수가 2개씩 곱으로 증가함.
	}
	fprintf(fout, "\n");
}*/

void delPriQ_Ev(PriQ* pPriQ_Ev)								// 동적할당 해제 함수 
{
	pPriQ_Ev->cs_PriQ.lock();								// 뮤텍스 닫기
	if (pPriQ_Ev->pCBT_Ev != NULL)
		free(pPriQ_Ev->pCBT_Ev);
	pPriQ_Ev->cs_PriQ.unlock();								// 뮤텍스 열기
}