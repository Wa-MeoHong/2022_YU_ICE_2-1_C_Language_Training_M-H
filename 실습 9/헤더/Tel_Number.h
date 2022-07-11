#ifndef TEL_NUMBER_H
#define TEL_NUMBER_H

#include <stdio.h>

// ����ü Tel ����
typedef struct Tel_Number {
	unsigned short N_code;						// Nation_code (���� ��ȣ)
	unsigned short R_code;						// Region_code (���� ��ȣ)
	unsigned short S_no;						// Switch_no (��ȯ�� ��ȣ)
	unsigned short L_no;						// Line_no (ȸ�� ��ȣ)
} Tel;

void printTelNumber(Tel tel_no);				// ��ȭ��ȣ ����Լ� 
int compareTelNumber(Tel tn1, Tel tn2);			// ��ȭ��ȣ ���Լ�

#endif