#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>								// suffle�Ҷ� rand()�Լ��� �������� ����
#include <time.h>								// RANDOMIZE()�� ���� �ʿ��� (�ð��� �������� �õ带 ����)
#include <string.h>								// ���ڿ� ����, �񱳸� ���� �Լ��� ������ ������� (strcpy, strcmp)

#define RANDOMIZE() srand((unsigned int)time(NULL)) // srand�Լ��� define���� ����
#define MAX_NAME_LEN 20								// �л� �̸� �ִ� ĭ��
#define Suffle_Max 30								// ������ Ƚ��

#define SORTSTUD "Sorted_Students.txt"				// �л� ���� �� ��� ����
#define NUM_STUDENTS 10								// �л� �� 10��
#define MAX_STRING_LEN 512							// ���� ����

// ����ü Date �ڷ��� ����
typedef struct Date {
	int year;
	int month;
	int day;
} Date;

// ����ü Tel �ڷ��� ����
typedef struct Tel_Number {
	unsigned short N_code;						// Nation_code (���� ��ȣ)
	unsigned short R_code;						// Region_code (���� ��ȣ)
	unsigned short S_no;						// Switch_no (��ȯ�� ��ȣ)
	unsigned short L_no;						// Line_no (ȸ�� ��ȣ)
} Tel;

// �л� ����ü Student 
typedef struct Student {
	int st_id;									// �й�
	char name[MAX_NAME_LEN];					// �̸�
	Date date_of_birth;							// ����
	Tel tel_no;									// ��ȭ��ȣ
	double GPA;									// ����
} Student;

void printStudent(Student* pSt);									// �л� ���� ���
void printStudents(Student* stArray, int num_student);				// �л��� ���� ����Ʈ ���
void printDate(Date date);											// ��¥ ��� �Լ�
void printTelNumber(Tel tel_no);									// ��ȭ��ȣ ��� �Լ�

void FprintStudent(FILE* fout, Student* pSt);						// �л� ���� ���� ���
void FprintStudents(FILE* fout, Student* stArray, int num_student); // �л��� ���� ����Ʈ ���� ���
void fprintDate(FILE* fout, Date date);								// ��¥ ���� ��� �Լ�
void fprintTelNumber(FILE* fout, Tel tel_no);						// ��ȭ��ȣ ���� ��� �Լ�

void suffleStudents(Student* students, int num_student);			// �л��� ���� ����
void SelectSort_by_ST_ID(Student* students, int num_student);		// �������� �Լ�

#endif