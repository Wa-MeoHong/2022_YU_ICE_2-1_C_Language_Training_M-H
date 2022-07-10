#ifndef MATRIX_H
#define MATRIX_H
#pragma warning(disable: 4996) // scanf���� �ȶ߰� �ϴ� pragma���� 

#include <stdio.h>
#include <stdlib.h>

//������ �迭 ���� �Ҵ�, ���� �Լ�
double** fGetMtrx(FILE* fin, int* row_SIZE, int* col_SIZE);								// ���� �Է� �Լ�
void DeleteDynMtrx(double** dM, int row_SIZE);											// ���� �Ҵ� ���� �Լ� (2�����迭 ����)

// ������ �迭 ��� �Լ�
void PrintMtrx(double** mA, int row_SIZE, int col_SIZE);								// ��� ��� �Լ�
void FPrintMtrx(FILE* fout, double** mA, int row_SIZE, int col_SIZE);					// ��� ���� ��� �Լ�

//������ ��� ��� �Լ�
double** AddMtrx(double** mA, double** mB, int row_SIZE, int col_SIZE);					// ��� ����
double** SubMtrx(double** mA, double** mB, int row_SIZE, int col_SIZE);					// ��� ����
double** MulMtrx(double** mA, double** mC, int row_SIZE, int SIZE_k, int col_SIZE);		// ��� ����

#endif