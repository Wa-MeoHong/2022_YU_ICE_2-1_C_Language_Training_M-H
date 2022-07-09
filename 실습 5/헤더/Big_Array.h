/*
  ���ϸ� : "�ǽ�5_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- ��ó����, ��������� ���� main�Լ��� ��� ����, ���Ͽ� �Է��غ��� ���α׷�

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 3�� 30��)
  ���� Update : Version 2.0.1, 2022�� 3�� 31��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
   �Ŵ�ȫ		 2022/03/30		v1.0.0		  �����ۼ�
   �Ŵ�ȫ		 2022/03/30		v2.0.0		  ���α׷� ������ ���� �ϰ��ƾ���
   �Ŵ�ȫ		 2022/03/31		v2.0.1		  �ذ� ��, ���α׷� ����ȭ
   �Ŵ�ȫ		 2022/03/31		v2.0.2		  ���α׷� ����ȭ, ������ڵ� ����

===========================================================================================================
*/


#ifndef BIG_ARRAY_H
#define BIG_ARRAY_H
#pragma warning(disable: 4996)						 		// scanf���� �ȶ߰� �ϴ� pragma���� 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// main.c���� ���
#define MAX_NUM_DATA 100 
#define ESC 0x1B											// EOF

// big_array.c���� ���
#define LINE_SIZE 10										// 10�� ǥ��
#define POWNUM 2											//������
#define MAX(x,y) ((x) > (y)) ? (x) : (y)					// MAX ��ũ��
#define MIN(x,y) ((x) < (y)) ? (x) : (y)					// MIN ��ũ��
#define BIG_SIZE 50000
#define OFFSET 1

void printArray(int* data_array, int SIZE, int line_size);					// ���� �迭�� ��� �Լ�
void fprintArray(FILE* fout, int* data_array, int SIZE, int line_size);		//���Ͽ� �����迭 ����Լ�
void printBigarraySample(int* array, int SIZE, int line_size, int num_sample_lines);				// ū �迭 ���
void fprintBigarraySample(FILE* fout, int* array, int SIZE, int line_size, int num_sample_lines);	//���Ͽ� ū�迭 ���
void getArrayStatistics(int* array, int SIZE);								//�迭��ҵ� ����(�ִ�, �ּ�, ���, �л�, ǥ������)��� �� ����Լ�
void fgetArrayStatistics(FILE* fout, int* array, int SIZE);					//���Ͽ� getArrayStatistics�Լ�
void BigRandArray(int* array, int SIZE);

#endif 