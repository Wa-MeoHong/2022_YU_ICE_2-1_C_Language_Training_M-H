#ifndef Big_ARRAY_H
#define Big_ARRAY_H
#pragma warning(disable: 4996) // scanf���� �ȶ߰� �ϴ� pragma���� 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Small_SIZE 100
#define LINE_SIZE 10
#define Micro 1000000
#define Milli 1000

void genBigRandArray(int* array, int SIZE, int offset);									// ���� ���� �Լ�
void printBigArray(int* array, int SIZE, int items_per_size, int num_sample_lines);		// ���� ��� �Լ�
void SuffleBigArray(int* array, int SIZE);												// ���� ���� �Լ�

#endif
