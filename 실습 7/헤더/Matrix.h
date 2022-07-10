#ifndef MATRIX_H
#define MATRIX_H

#pragma warning(disable: 4996)											// scanf���� �ȶ߰� �ϴ� pragma���� 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Mtrx_SIZE 5														// ��� ũ��



void CheckAddr_2D_Array(double** dM, int row_SIZE, int col_SIZE);		// 2�����迭 �ּ� üũ �Լ�
void DeleteDoubleMatrix(double** dM, int row_SIZE);						// ���� �Ҵ� ���� �Լ� (2�����迭 ����)
double** fGetMtrx(FILE* fin, int* row_SIZE, int* col_SIZE);				// ���� �Է� �Լ�
double** getStaticsMtrx(double** mA, int n_row_SIZE, int n_col_SIZE);	// ����� �� ��հ� ���� �Լ�
void PrintMtrx(double** mA, int row_SIZE, int col_SIZE);				// ��� ��� �Լ�
void FPrintMtrx(FILE* fout, double** mA, int row_SIZE, int col_SIZE);	// ��� ��� �Լ�

#endif