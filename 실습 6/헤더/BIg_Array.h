#ifndef Big_ARRAY_H
#define Big_ARRAY_H
#pragma warning(disable: 4996) // scanf오류 안뜨게 하는 pragma정의 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Small_SIZE 100
#define LINE_SIZE 10
#define Micro 1000000
#define Milli 1000

void genBigRandArray(int* array, int SIZE, int offset);									// 난수 생성 함수
void printBigArray(int* array, int SIZE, int items_per_size, int num_sample_lines);		// 난수 출력 함수
void SuffleBigArray(int* array, int SIZE);												// 난수 셔플 함수

#endif
