/*
  파일명 : "실습5_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 전처리기, 헤더파일을 만들어서 main함수에 끌어서 쓰고, 파일에 입력해보는 프로그램

  프로그램 작성자 : 신대홍(2022년 3월 30일)
  최종 Update : Version 2.0.1, 2022년 3월 31일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
   신대홍		 2022/03/30		v1.0.0		  최초작성
   신대홍		 2022/03/30		v2.0.0		  프로그램 오류로 인해 싹갈아엎음
   신대홍		 2022/03/31		v2.0.1		  해결 후, 프로그램 최적화
   신대홍		 2022/03/31		v2.0.2		  프로그램 최적화, 헤더용코드 압축

===========================================================================================================
*/


#ifndef BIG_ARRAY_H
#define BIG_ARRAY_H
#pragma warning(disable: 4996)						 		// scanf오류 안뜨게 하는 pragma정의 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// main.c에서 사용
#define MAX_NUM_DATA 100 
#define ESC 0x1B											// EOF

// big_array.c에서 사용
#define LINE_SIZE 10										// 10줄 표시
#define POWNUM 2											//제곱수
#define MAX(x,y) ((x) > (y)) ? (x) : (y)					// MAX 매크로
#define MIN(x,y) ((x) < (y)) ? (x) : (y)					// MIN 매크로
#define BIG_SIZE 50000
#define OFFSET 1

void printArray(int* data_array, int SIZE, int line_size);					// 적은 배열의 출력 함수
void fprintArray(FILE* fout, int* data_array, int SIZE, int line_size);		//파일용 적은배열 출력함수
void printBigarraySample(int* array, int SIZE, int line_size, int num_sample_lines);				// 큰 배열 출력
void fprintBigarraySample(FILE* fout, int* array, int SIZE, int line_size, int num_sample_lines);	//파일용 큰배열 출력
void getArrayStatistics(int* array, int SIZE);								//배열요소들 정보(최대, 최소, 평균, 분산, 표준편차)계산 및 출력함수
void fgetArrayStatistics(FILE* fout, int* array, int SIZE);					//파일용 getArrayStatistics함수
void BigRandArray(int* array, int SIZE);

#endif 