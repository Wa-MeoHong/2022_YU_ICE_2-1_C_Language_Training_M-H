#ifndef MTRX_CALCULATE_H
#define MTRX_CALCULATE_H

#include "Matrix.h"

double** AddMtrx(double** mA, double** mB, int row_SIZE, int col_SIZE); // ��� ����
double** SubMtrx(double** mA, double** mB, int row_SIZE, int col_SIZE); // ��� ����
double** MulMtrx(double** mA, double** mB, int row_SIZE, int SIZE_k, int col_SIZE); // ��� ����

#endif // !MTRX_CALCULATE_H
