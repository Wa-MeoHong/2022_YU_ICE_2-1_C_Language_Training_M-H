#include "Student.h"

void printDate(Date date)									// 날짜 출력 함수
{
	printf("(%4d, %2d, %2d)", date.year, date.month, date.day);
}

void printTelNumber(Tel tel_no)								// 전화번호 출력 함수
{
	printf("(tel : +%2d-0%2d-%4d-%04d)"\
		, tel_no.N_code, tel_no.R_code, tel_no.S_no, tel_no.L_no);
}

void printStudent(Student* pSt)								// 학생 정보 출력함수
{
	// 학생 정보를 출력, 날짜와 전화번호는 출력함수가 따로 있으므로 끊어서 코드를 작성함
	printf("Student [ID: %8d, %10s, GPA: %4.2lf, ", pSt->st_id, pSt->name, pSt->GPA);
	printDate(pSt->date_of_birth);
	printf(", ");
	printTelNumber(pSt->tel_no);
	printf("]\n");
}

void printStudents(Student* stArray, int num_student)		// 학생 정보 리스트 출력
{
	// 학생의 정보를 출력하는걸 학생수만큼 반복함
	for (int i = 0; i < num_student; i++)
	{
		printStudent(&stArray[i]);
	}
}

void fprintDate(FILE* fout, Date date)						// 날짜 파일 출력 함수
{
	fprintf(fout, "(%4d, %2d, %2d)", date.year, date.month, date.day);
}

void fprintTelNumber(FILE* fout, Tel tel_no)				// 전화번호 출력 함수
{
	fprintf(fout, "(tel : +%2d-0%2d-%4d-%04d)"\
		, tel_no.N_code, tel_no.R_code, tel_no.S_no, tel_no.L_no);
}

void FprintStudent(FILE* fout, Student* pSt)
{
	// 학생 정보를 출력, 날짜와 전화번호는 출력함수가 따로 있으므로 끊어서 코드를 작성함
	fprintf(fout, "Student [ID: %8d, %10s, GPA: %4.2lf, ", pSt->st_id, pSt->name, pSt->GPA);
	fprintDate(fout, pSt->date_of_birth);
	fprintf(fout, ", ");
	fprintTelNumber(fout, pSt->tel_no);
	fprintf(fout, "]\n");
}

void FprintStudents(FILE* fout, Student* stArray, int num_student) // 학생 정보 리스트 출력
{
	// 학생의 정보를 출력하는걸 학생수만큼 반복함
	for (int i = 0; i < num_student; i++)
	{
		FprintStudent(fout, &stArray[i]);
	}
}

void suffleStudents(Student* students, int num_student)		// 학생 리스트 셔플 
{
	Student temp;
	int suffle_count = 0;
	RANDOMIZE();								// 랜덤 시드 생성

	while(1)
	{
		int a = rand() % num_student;				// 학생 인덱스번호를 랜덤으로 생성
		int b = rand() % num_student;				// 동일

		if (suffle_count == Suffle_Max)				// 만약 셔플한 횟수가 30번이 넘었다면
			break;									// 종료

		if (a == b)									// 만약 a, b가 같다면 다시
			continue;
		else
		{
			temp = students[a];						// 바꾸기
			students[a] = students[b];
			students[b] = temp;
			suffle_count++;							// 셔플한 횟수 업
		}
	}
}

void SelectSort_by_ST_ID(Student* students, int num_student)		// 학생 정렬 함수
{
	Student temp;									// 값 바꾸기위한 임시 변수
	int sort_IDX = 0;								// 정렬 기준 인덱스 값
	int min_IDX = 0;								// 최소값의 인덱스 번호를 찾음
	while (1)
	{
		if (sort_IDX == num_student)				// 만약 정렬 기준 인덱스 값이 배열의 범위를 벗어나면 종료
			break;
		temp = students[sort_IDX];					// 초기값 설정
		min_IDX = sort_IDX;							// 인덱스 초기값 설정

		for (int i = sort_IDX; i < num_student; i++)
		// 정렬 기준 인덱스 번호까지의 인덱스를 제외한 나머지 인덱스 번호에서 최소값을 찾음
		{
			if (temp.st_id > students[i].st_id)		// id가 비교하는 값보다 크다면
			{
				temp = students[i];					// 최소값 갱신
				min_IDX = i;						// 인덱스 번호 갱신
			}
		}

		// 값 바꾸기
		students[min_IDX] = students[sort_IDX];
		students[sort_IDX] = temp;
		sort_IDX++;									// 정렬 기준 번호 증가 
	}
}