#ifndef SORTING_H
#define SORTING_H

#include "Big_Array.h"

#define QUICK_SELECTION_THRESHOLD 25 // 하이브리드 퀵정렬에 필요( newpi가 멈추는곳)

void selectionSort(int* array, int SIZE, int left, int right);				// 선택정렬 

void mergeSort(int* array, int SIZE);										// 병합정렬 초기함수(임시 저장 배열 temp_array 생성목적)
void _mergeSort(int* array, int* temp_array, int left, int right);			// 병합정렬 본함수

int _partition(int* array, int SIZE, int left, int right, int P_I);			// 파티션 위치값 반환 함수
void quickSort(int* array, int SIZE, int left, int right);					// 퀵정렬,본함수
void _QUICKSORT(int* array, int SIZE);										// 퀵 정렬 최초 함수

void _H_Brid_QUICKSORT(int* array, int SIZE);								// 하이브리드 퀵정렬 최초함수
void H_Brid_quickSort(int* array, int SIZE, int left, int right);			// 하이브리드 퀵정렬 본함수

#endif 