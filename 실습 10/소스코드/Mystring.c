#include "Mystring.h"

char** fGetWords(FILE* fin, int* num_words, int NOW, int LOW) 
// 단어의 개수, 문자의 개수를 받아, 배열 동적 할당 후, 파일에서 문자열을 읽어와 배열에 집어넣는 함수
// NOW : Number Of Words, LOW : Length of Word
{
	char** Words = NULL;										// 동적할당할 이중 포인터 변수
	char FileWord[MAX_WORD_LEN] = { 0 };						// 파일에서 읽어온 단어를 받는 임시 문자열
	int count = 0;												// 단어 개수 세기 용

	Words = (char**)calloc(NOW, sizeof(char*));					// 동적할당 1. NOW개 만큼의 단어 배열을 만듦
	for (int i = 0; i < NOW; i++)
	{
		Words[i] = (char*)calloc(LOW, sizeof(char));			// 동적할당 2. 최대 LOW만큼의 문자를 담을 수 있게 한 단어당 크기할당
	}

	while(fscanf(fin, "%s", FileWord) != EOF)					// 읽어온 문자열을 FileWord에 담음, 파일의 끝에 도달하기 전까지
	{
			strcpy(Words[count], FileWord);						// 그리고 배열에 문자열을 복사해줌
			count++;
	}
	*num_words = count;											// 실제 단어 개수 반환 
	return Words;												// 동적 할당된 배열 주소 반환
}

void DeleteWords(char** Words, int NOW)							// 동적할당 해제 함수
{
	for (int i = 0; i < NOW; i++)						// 행 동적할당 해제
		free(Words[i]);
	free(Words);										// 전체 동적할당 해제
}

void PrintWords(FILE* fout, char** Words, int NoW)				// 단어를 파일에 출력하는 함수
{
	for (int i = 0; i < NoW; i++)							// 줄 수 만큼
	{
		if (i % 10 == 0)
		{
			printf("\n");
			fprintf(fout, "\n");
		}
		printf("%18s", Words[i]);							// 출력
		fprintf(fout, "%18s", Words[i]);					// 파일에 출력
	}

	//단어들을 모두 넣었다는 콘솔 메세지 출력
	printf("\n");
	fprintf(fout, "\n");
	printf("\n Words has been entered into sorted_Words.txt File!\n");
	printf(" Please Check sorted_Words.txt File.\n\n");
}

void SelectionSortWords(char** Words, int num_words)			// 단어 선택 정렬 함수
{
	char temp[MAX_WORD_LEN] = { 0 };						// 단어를 바꾸기 위한 임시 문자열 배열
	int sort_IDX = 0, min_IDX = 0;							// 정렬 기준 인덱스, 최소값 인덱스

	// 선택정렬
	while (1) 
	{
		if (sort_IDX == num_words)							// 만약 정렬 인덱스가 단어의 개수만큼 했다면 중지
			break;
		strcpy(temp, Words[sort_IDX]);						// 정렬 기준 인덱스에 있는 단어를 복사
		min_IDX = sort_IDX;									// 최소값 인덱스 초기값 설정

		for (int i = sort_IDX + 1; i < num_words; i++)		// 정렬 기준인덱스 + 1부터 단어배열 끝까지
		{
			if (strcmp(temp, Words[i]) == 1)				// 만약 단어가 temp보다 크다면( 아스키코드 기준 )
			{
				strcpy(temp, Words[i]);						// 최소값 단어 갱신
				min_IDX = i;								// 최소값 인덱스 갱신
			}
		}

		//값 바꾸기
		strcpy(Words[min_IDX], Words[sort_IDX]); 
		strcpy(Words[sort_IDX], temp);
		sort_IDX++;											// 정렬 인덱스 증가
	}
}
