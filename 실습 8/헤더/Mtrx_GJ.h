#ifndef MATRIX_GJ_H
#define MATRIX_GJ_H

#include "Matrix.h"
#include <math.h>


#define Epsilon 0.000001

void GetAugmentedMtrx(FILE* fin, double** MtrxD, int* SIZE_N);
void pivoting(double** augMtrx, int SIZE_N, int p, int* piv_FOUND);
void Diagnolize(FILE* fout, double** augMtrx, int SIZE_N, int* solExist);
void InvMtrx(FILE* fout, double** mA, double** Inv_mA, int SIZE_N, int* solexist);

#endif