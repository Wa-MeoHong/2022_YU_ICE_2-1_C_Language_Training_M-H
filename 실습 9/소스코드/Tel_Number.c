#include "Tel_Number.h"

void printTelNumber(Tel tel_no)							// 전화번호 출력 함수
{
	printf("(tel : +%2d-0%2d-%4d-%04d)", tel_no.N_code, tel_no.R_code, tel_no.S_no, tel_no.L_no);
}

int compareTelNumber(Tel tn1, Tel tn2)					// 전화번호 비교함수 (크면 1, 작으면 -1, 같으면 0)
{
	if (tn1.N_code > tn2.N_code)
		return 1;
	else if (tn1.N_code < tn2.N_code)
		return -1;

	//국가 번호 동일
	else if (tn1.R_code > tn2.R_code)
		return 1;
	else if (tn1.R_code < tn2.R_code)
		return -1;

	// 지역번호 동일
	else if (tn1.S_no > tn2.S_no)
		return 1;
	else if (tn1.S_no < tn2.S_no)
		return -1;

	// 교환 번호 동일
	else if (tn1.L_no > tn2.L_no)
		return 1;
	else if (tn1.L_no < tn2.L_no)
		return -1;

	// 모든 번호 동일 (회선번호까지 동일)
	else
		return 0;
}