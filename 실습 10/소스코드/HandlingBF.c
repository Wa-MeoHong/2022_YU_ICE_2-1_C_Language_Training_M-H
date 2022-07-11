#include "HandlingBF.h"

void DumpBinaryFile(FILE* fin, FILE* fout)							// 파일의 이진 데이터 출력
{
	int read_bytes;											// 읽은 바이트 
	
	int cus_pos;

	fseek(fin, 0, SEEK_END);								// 파일의 끝을 찾음
	cus_pos = ftell(fin);									// 총 몇자(몇바이트)인지 알아냄
	rewind(fin);											// 처음으로 돌아간다

	for (int addr = 0; addr < cus_pos; addr += BUFFER_LEN)	// addr는 주소(메모리, 첫 시작을 0으로 정함)
	// 그리고 16바이트씩 버퍼를 읽어오기 때문에 메모리 주소를 16씩 더해준다.
	{
		unsigned char buffer[BUFFER_LEN] = { '\0' };		// 버퍼배열 16바이트 (바이트는 음수가 없으므로 unsigned 씀)
		read_bytes = fread(buffer, sizeof(unsigned char), BUFFER_LEN, fin);
															// fread함수 (1바이트씩, 16개를 읽어서 배열에 저장)
		if (read_bytes <= 0)								// 읽어온 바이트가 없다면( 파일의 끝을 만났거나 등) 종료
			break;

		fprintf(fout, "%08X: ", addr);						// 파일 주소 출력 
		for (int i = 0; i < BUFFER_LEN; i++)
		{
			if (i == (BUFFER_LEN / 2))						// i == 8, 8번째 바이트일때는
				fprintf(fout, " ");
			if (buffer[i] == '\0')							// 만약 읽은 문자가 없어서 저장된 문자가 없다면(NULL) 
			{
				fprintf(fout, "    ");						// 빈칸을 출력함
			}
			else
				fprintf(fout, "%02X ", buffer[i]);			// 1byte = 8bit, 16진수는 4bit를 하나의 문자로 표현 가능 따라서 2글자로 1바이트를 표현 할 수 있음
		}
		
		// 16바이트에 담긴 데이터를 전부 출력했다.
		fprintf(fout, " ");
		for (int j = 0; j < read_bytes; j++)
		{
			if (isprint(buffer[j]))							// 버퍼안에 있는 그 문자가 아스키문자로 표현할 수 있는가(문자)
				fprintf(fout, "%c", buffer[j]);				// 문자 출력
			else
				fprintf(fout, ".");							// 아스키문자로 표현 불가능한 글자(\t, \n 등)은 .으로 표현
		}
		fprintf(fout, "\n");								// 16바이트에 대한 모든 정보를 출력했으므로 이제 다음을 위해 한칸 엔터
	}
	rewind(fin);											// 덤핑이 끝난 후, 파일커서가 처음으로 돌아간다
}

void Waiting()												// 기다리는 함수
{
	for (int i = 0; i < 3; i++)
	{
		printf(" .");										// . 붙임
		Sleep(1000);										// 잠시 1초동안 대기
	}
	printf("\n");											// 엔터
}