#include "Tel_Number.h"

void printTelNumber(Tel tel_no)							// ��ȭ��ȣ ��� �Լ�
{
	printf("(tel : +%2d-0%2d-%4d-%04d)", tel_no.N_code, tel_no.R_code, tel_no.S_no, tel_no.L_no);
}

int compareTelNumber(Tel tn1, Tel tn2)					// ��ȭ��ȣ ���Լ� (ũ�� 1, ������ -1, ������ 0)
{
	if (tn1.N_code > tn2.N_code)
		return 1;
	else if (tn1.N_code < tn2.N_code)
		return -1;

	//���� ��ȣ ����
	else if (tn1.R_code > tn2.R_code)
		return 1;
	else if (tn1.R_code < tn2.R_code)
		return -1;

	// ������ȣ ����
	else if (tn1.S_no > tn2.S_no)
		return 1;
	else if (tn1.S_no < tn2.S_no)
		return -1;

	// ��ȯ ��ȣ ����
	else if (tn1.L_no > tn2.L_no)
		return 1;
	else if (tn1.L_no < tn2.L_no)
		return -1;

	// ��� ��ȣ ���� (ȸ����ȣ���� ����)
	else
		return 0;
}