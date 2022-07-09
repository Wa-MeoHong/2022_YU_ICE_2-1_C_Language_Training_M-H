#ifndef SORTING_H
#define SORTING_H

#include "Big_Array.h"

#define QUICK_SELECTION_THRESHOLD 25 // ���̺긮�� �����Ŀ� �ʿ�( newpi�� ���ߴ°�)

void selectionSort(int* array, int SIZE, int left, int right);				// �������� 

void mergeSort(int* array, int SIZE);										// �������� �ʱ��Լ�(�ӽ� ���� �迭 temp_array ��������)
void _mergeSort(int* array, int* temp_array, int left, int right);			// �������� ���Լ�

int _partition(int* array, int SIZE, int left, int right, int P_I);			// ��Ƽ�� ��ġ�� ��ȯ �Լ�
void quickSort(int* array, int SIZE, int left, int right);					// ������,���Լ�
void _QUICKSORT(int* array, int SIZE);										// �� ���� ���� �Լ�

void _H_Brid_QUICKSORT(int* array, int SIZE);								// ���̺긮�� ������ �����Լ�
void H_Brid_quickSort(int* array, int SIZE, int left, int right);			// ���̺긮�� ������ ���Լ�

#endif 