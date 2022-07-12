#include "DLL_EvQ.h"

void initDLL_EvQ(DLL_EvQ* pEvQ, int pri)			// 이벤트 큐 초기값 설정
{
	pEvQ->cs_EvQ.lock();							// 이벤트 큐 뮤텍스 락
	pEvQ->priority = pri;
	pEvQ->front = pEvQ->back = NULL;
	pEvQ->num_Ev = 0;
	pEvQ->cs_EvQ.unlock();							// 이벤트 큐 뮤텍스 언락
}

bool isEmpty(DLL_EvQ* pEvQ)
{
	if (pEvQ->num_Ev == 0)							// 현재 이벤트 개수가 0개라면
		return true;
	else
		return false;
}

Event* enDLL_EvQ(DLL_EvQ* pEvQ, Event* pEv)			// enqueue를 자기참조 구조체형으로 만듦
{	
	DLLN_Ev* pLN_Ev;
	if (pEv == NULL)								// 만약 집어넣을 이벤트가 없다면
	{
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ... \n");
		getc(stdin);
		return NULL;
	}

	pLN_Ev = (DLLN_Ev*)calloc(1, sizeof(DLLN_Ev));
	if (pLN_Ev == NULL)								// 이벤트 노드가 동적할당 되지 않았다면
	{
		printf("Error in enDLL_EvQ :: memory allocation for new DLLN failed !!\n");
		printf("Press any key to continue ... \n");
		getc(stdin);
		return NULL;
	}

	pLN_Ev->pEv = pEv;								// 노드에 이벤트 대입
	pEvQ->cs_EvQ.lock();							// 잠금
	if (pEvQ->num_Ev == 0)							// 현재 이벤트 개수가 0개라면
	{
		pEvQ->front = pEvQ->back = pLN_Ev;			// 이벤트 큐 앞,뒤는 이벤트 노드와 연결( 1개밖에 없으니까)
		pLN_Ev->prev = pLN_Ev->next = NULL;			// 이벤트 노드 앞뒤로 아무도 없으니 NULL
		pEvQ->num_Ev = 1;							// 이벤트 개수는 1개
	}
	else											// 이벤트 개수가 1개 이상
	{
		pLN_Ev->prev = pEvQ->back;					// 이벤트 노드가 추가될때는 맨 뒤에 붙기 떄문에 이벤트 큐 맨뒤 (back)으로 설정
		pEvQ->back->next = pLN_Ev;					// 원래 이벤트 큐의 맨뒤와 새로운 이벤트 노드를 이어준다. (next)
		pEvQ->back = pLN_Ev;						// 새로운 이벤트 노드로 이벤트 큐의 back을 갱신
		pLN_Ev->next = NULL;						// 맨 끝 이벤트 노드의 그다음은 없기 때문에 NULL
		pEvQ->num_Ev++;								// 이벤트 개수 갱신
	}
	pEvQ->cs_EvQ.unlock();							// 잠금해제
	return pLN_Ev->pEv;								// 이벤트를 반환( 추가한 이벤트노드의 이벤트 )
}

Event* deDLL_EvQ(DLL_EvQ* pEvQ)						// dequeue를 자기참조 구조체 형으로 만듦
{
	Event* pEv;										// 처리할 이벤트
	DLLN_Ev* pLN_Ev_OldFront;						// 처리된 이벤트 노드 (큐의 맨 앞부분)

	pEvQ->cs_EvQ.lock();							// 잠금
	if (pEvQ->num_Ev <= 0)							// 현재 이벤트 개수가 0개라면 (처리할 이벤트가 없음) 
	{
		pEvQ->cs_EvQ.unlock();						// 이벤트 잠금해제 후 바로 탈출
		return NULL;
	}
	else
	{
		pLN_Ev_OldFront = pEvQ->front;				// Dequeue 하기 전 이벤트 큐의 맨 처음 노드 데이터를 복사(반환을 위해서)
		pEv = pEvQ->front->pEv;						// 처리한 이벤트를 따로 저장( 반환을 위해)
		pEvQ->front = pEvQ->front->next;			// 이벤트 큐의 front 다음의 노드(next)를 front로 재설정
		if (pEvQ->front != NULL)					// 이벤트 큐 front 재설정이 되었으면
			pEvQ->front->prev = NULL;				// 이벤트 큐 front의 그 전 이벤트는 없으므로 NULL로 설정
		pEvQ->num_Ev--;
		free(pLN_Ev_OldFront);						// 이전의 이벤트 노드는 free해주면서 없앰
		pEvQ->cs_EvQ.unlock();
		return pEv;									// 리턴
	}
}

void printDLL_EvQ(DLL_EvQ* pEvQ)					// 이벤트 큐 출력
{
	int index = 0;
	int count;
	Event* pEv;
	DLLN_Ev* pLN_Ev;
	if (pEvQ == NULL)								// 만약 출력할 이벤트 큐가 없다면
	{
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ... \n");
		getc(stdin);
		return;
	}
	if (pEvQ->num_Ev <= 0)							// 이벤트 큐에 담긴 이벤트가 없다면
		return;
	// 출력
	pLN_Ev = pEvQ->front;							// 이벤트 큐의 맨 처음의 노드를 초기값으로 가져옴
	count = 0;
	while (pLN_Ev != NULL)
	{
		pEv = pLN_Ev->pEv;							// 이벤트 노드안의 이벤트를 가져와서
		if (pEv == NULL)							// 이벤트가 없다면
			break;
		printEvent(pEv); printf(" ");				// 이벤트 출력
		count++;
		if ((count % EVENT_PER_LINE) == 0)			// 5개 출력할 때 마다 엔터
			printf("\n\t");
		pLN_Ev = pLN_Ev->next;						// 다음 노드를 찍음 
	}
}