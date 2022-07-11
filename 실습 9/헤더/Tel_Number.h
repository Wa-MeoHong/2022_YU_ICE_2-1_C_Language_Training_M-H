#ifndef TEL_NUMBER_H
#define TEL_NUMBER_H

#include <stdio.h>

// 구조체 Tel 정의
typedef struct Tel_Number {
	unsigned short N_code;						// Nation_code (국가 번호)
	unsigned short R_code;						// Region_code (지역 번호)
	unsigned short S_no;						// Switch_no (교환기 번호)
	unsigned short L_no;						// Line_no (회선 번호)
} Tel;

void printTelNumber(Tel tel_no);				// 전화번호 출력함수 
int compareTelNumber(Tel tn1, Tel tn2);			// 전화번호 비교함수

#endif