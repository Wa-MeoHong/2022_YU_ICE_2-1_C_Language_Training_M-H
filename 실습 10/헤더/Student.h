#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>								// suffle할때 rand()함수를 가져오기 위함
#include <time.h>								// RANDOMIZE()를 위해 필요함 (시간을 기준으로 시드를 만듦)
#include <string.h>								// 문자열 복사, 비교를 위한 함수를 가져올 헤더파일 (strcpy, strcmp)

#define RANDOMIZE() srand((unsigned int)time(NULL)) // srand함수를 define으로 정의
#define MAX_NAME_LEN 20								// 학생 이름 최대 칸수
#define Suffle_Max 30								// 셔플할 횟수

#define SORTSTUD "Sorted_Students.txt"				// 학생 정렬 후 출력 파일
#define NUM_STUDENTS 10								// 학생 수 10명
#define MAX_STRING_LEN 512							// 문자 개수

// 구조체 Date 자료형 설정
typedef struct Date {
	int year;
	int month;
	int day;
} Date;

// 구조체 Tel 자료형 설정
typedef struct Tel_Number {
	unsigned short N_code;						// Nation_code (국가 번호)
	unsigned short R_code;						// Region_code (지역 번호)
	unsigned short S_no;						// Switch_no (교환기 번호)
	unsigned short L_no;						// Line_no (회선 번호)
} Tel;

// 학생 구조체 Student 
typedef struct Student {
	int st_id;									// 학번
	char name[MAX_NAME_LEN];					// 이름
	Date date_of_birth;							// 생일
	Tel tel_no;									// 전화번호
	double GPA;									// 학점
} Student;

void printStudent(Student* pSt);									// 학생 정보 출력
void printStudents(Student* stArray, int num_student);				// 학생의 정보 리스트 출력
void printDate(Date date);											// 날짜 출력 함수
void printTelNumber(Tel tel_no);									// 전화번호 출력 함수

void FprintStudent(FILE* fout, Student* pSt);						// 학생 정보 파일 출력
void FprintStudents(FILE* fout, Student* stArray, int num_student); // 학생의 정보 리스트 파일 출력
void fprintDate(FILE* fout, Date date);								// 날짜 파일 출력 함수
void fprintTelNumber(FILE* fout, Tel tel_no);						// 전화번호 파일 출력 함수

void suffleStudents(Student* students, int num_student);			// 학생의 정보 섞기
void SelectSort_by_ST_ID(Student* students, int num_student);		// 선택정렬 함수

#endif