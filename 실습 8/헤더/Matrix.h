#ifndef MATRIX_H
#define MATRIX_H
#pragma warning(disable: 4996) // scanf오류 안뜨게 하는 pragma정의 

#include <stdio.h>
#include <stdlib.h>

//이차원 배열 동적 할당, 해제 함수
double** fGetMtrx(FILE* fin, int* row_SIZE, int* col_SIZE);								// 파일 입력 함수
void DeleteDynMtrx(double** dM, int row_SIZE);											// 동적 할당 해제 함수 (2차원배열 해제)

// 이차원 배열 출력 함수
void PrintMtrx(double** mA, int row_SIZE, int col_SIZE);								// 행렬 출력 함수
void FPrintMtrx(FILE* fout, double** mA, int row_SIZE, int col_SIZE);					// 행렬 파일 출력 함수

//이차원 행렬 계산 함수
double** AddMtrx(double** mA, double** mB, int row_SIZE, int col_SIZE);					// 행렬 덧셈
double** SubMtrx(double** mA, double** mB, int row_SIZE, int col_SIZE);					// 행렬 뺄셈
double** MulMtrx(double** mA, double** mC, int row_SIZE, int SIZE_k, int col_SIZE);		// 행렬 곱셈

#endif