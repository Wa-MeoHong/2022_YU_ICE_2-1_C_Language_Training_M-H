#ifndef MATRIX_H
#define MATRIX_H

#pragma warning(disable: 4996)											// scanf오류 안뜨게 하는 pragma정의 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Mtrx_SIZE 5														// 행렬 크기



void CheckAddr_2D_Array(double** dM, int row_SIZE, int col_SIZE);		// 2차원배열 주소 체크 함수
void DeleteDoubleMatrix(double** dM, int row_SIZE);						// 동적 할당 해제 함수 (2차원배열 해제)
double** fGetMtrx(FILE* fin, int* row_SIZE, int* col_SIZE);				// 파일 입력 함수
double** getStaticsMtrx(double** mA, int n_row_SIZE, int n_col_SIZE);	// 행렬의 각 평균값 산출 함수
void PrintMtrx(double** mA, int row_SIZE, int col_SIZE);				// 행렬 출력 함수
void FPrintMtrx(FILE* fout, double** mA, int row_SIZE, int col_SIZE);	// 행렬 출력 함수

#endif