#ifndef HANDLINGBF_H
#define HANDLINGBF_H

#include <stdio.h> 
#include <ctype.h>									// �������� ������ �ʿ�

#define OUTPUT "Output.txt"
#define BUFFER_LEN 16
#define MAX_FILE_SIZE 500							// �ִ� 500 ����Ʈ������ ���

void DumpBinaryFile(FILE* fin, FILE* fout);			// ������ ���� ������ ���
void Waiting();										// ��ٸ��� �Լ�..

#endif
