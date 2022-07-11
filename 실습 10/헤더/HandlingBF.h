#ifndef HANDLINGBF_H
#define HANDLINGBF_H

#include <stdio.h> 
#include <ctype.h>									// 이진파일 읽을때 필요

#define OUTPUT "Output.txt"
#define BUFFER_LEN 16
#define MAX_FILE_SIZE 500							// 최대 500 바이트까지만 출력

void DumpBinaryFile(FILE* fin, FILE* fout);			// 파일의 이진 데이터 출력
void Waiting();										// 기다리는 함수..

#endif
