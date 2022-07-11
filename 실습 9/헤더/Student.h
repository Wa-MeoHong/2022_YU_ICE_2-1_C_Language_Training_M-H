#ifndef STUDENT_H
#define STUDENT_H

#include "Date.h"										// 구조체 Date와 날짜 출력, 날짜 비교 함수 가지고옴
#include "Tel_Number.h"									// 구조체 Tel와 전화번호 출력, 번호 비교 함수 가지고옴
#include <stdlib.h>										// suffle할때 rand()함수를 가져오기 위함
#include <time.h>										// RANDOMIZE()를 위해 필요함 (시간을 기준으로 시드를 만듦)
#include <string.h>										// 문자열 복사, 비교를 위한 함수를 가져올 헤더파일 (strcpy, strcmp)

#define RANDOMIZE() srand((unsigned int)time(NULL))		// srand함수를 define으로 정의
#define MAX_NAME_LEN 20									// 학생 이름 최대 칸수
#define MAX(x,y) ((x) >= (y)) ? (x) : (y)				// MAX(x,y) 매크로 (조건부 연산식)
#define MIN(x,y) ((x) <= (y)) ? (x) : (y)				// MIN(x,y) 매크로 (조건부 연산식)
#define Suffle_Max 30

//학생 구조체 Student (typedef로 정의)
typedef struct Student{							
	int st_id;											// 학번
	char name[MAX_NAME_LEN];							// 이름
	Date date_of_birth;									// 생일
	Tel tel_no;											// 전화번호
	double GPA;											// 성적
} Student;

// 학생 정보를 enum으로 설정
typedef enum ST_KEY {
	ST_ID, NAME, GPA, DOB, TEL
} ST_KEY;

void printStudent(Student* pSt);										// 학생 정보 출력
void printStudents(Student* stArray, int num_student);					// 학생의 정보 리스트 출력
void suffleStudents(Student students[], int num_student);				// 학생의 정보 섞기
void statisticsGPA(Student students[], int num_student);				// 학점 최고, 최저, 평균 계산 후 출력
Student* searchBestGPAStu(Student students[], int num_student);			// 최고 학점 학생 찾아 주소값 반환
Student* searchWorstGPAStu(Student students[], int num_student);		// 최저 학점 학생 찾고 주소값 반환
int compareStudents(Student* pST1, Student* pST2, ST_KEY st_key);		// 학생1, 학생 2을 받은 ST_KEY에 따라 비교하고 값을 반환
void sortStudent(Student students[], int num_student, ST_KEY st_key);	// 메뉴에 따라 정렬 기준을 다르게 해 선택정렬
void SelectSort(Student students[], int num_student, ST_KEY st_key);	// 선택정렬 함수

#endif