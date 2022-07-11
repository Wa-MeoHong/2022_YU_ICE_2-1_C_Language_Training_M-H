#ifndef STUDENT_H
#define STUDENT_H

#include "Date.h"										// ����ü Date�� ��¥ ���, ��¥ �� �Լ� �������
#include "Tel_Number.h"									// ����ü Tel�� ��ȭ��ȣ ���, ��ȣ �� �Լ� �������
#include <stdlib.h>										// suffle�Ҷ� rand()�Լ��� �������� ����
#include <time.h>										// RANDOMIZE()�� ���� �ʿ��� (�ð��� �������� �õ带 ����)
#include <string.h>										// ���ڿ� ����, �񱳸� ���� �Լ��� ������ ������� (strcpy, strcmp)

#define RANDOMIZE() srand((unsigned int)time(NULL))		// srand�Լ��� define���� ����
#define MAX_NAME_LEN 20									// �л� �̸� �ִ� ĭ��
#define MAX(x,y) ((x) >= (y)) ? (x) : (y)				// MAX(x,y) ��ũ�� (���Ǻ� �����)
#define MIN(x,y) ((x) <= (y)) ? (x) : (y)				// MIN(x,y) ��ũ�� (���Ǻ� �����)
#define Suffle_Max 30

//�л� ����ü Student (typedef�� ����)
typedef struct Student{							
	int st_id;											// �й�
	char name[MAX_NAME_LEN];							// �̸�
	Date date_of_birth;									// ����
	Tel tel_no;											// ��ȭ��ȣ
	double GPA;											// ����
} Student;

// �л� ������ enum���� ����
typedef enum ST_KEY {
	ST_ID, NAME, GPA, DOB, TEL
} ST_KEY;

void printStudent(Student* pSt);										// �л� ���� ���
void printStudents(Student* stArray, int num_student);					// �л��� ���� ����Ʈ ���
void suffleStudents(Student students[], int num_student);				// �л��� ���� ����
void statisticsGPA(Student students[], int num_student);				// ���� �ְ�, ����, ��� ��� �� ���
Student* searchBestGPAStu(Student students[], int num_student);			// �ְ� ���� �л� ã�� �ּҰ� ��ȯ
Student* searchWorstGPAStu(Student students[], int num_student);		// ���� ���� �л� ã�� �ּҰ� ��ȯ
int compareStudents(Student* pST1, Student* pST2, ST_KEY st_key);		// �л�1, �л� 2�� ���� ST_KEY�� ���� ���ϰ� ���� ��ȯ
void sortStudent(Student students[], int num_student, ST_KEY st_key);	// �޴��� ���� ���� ������ �ٸ��� �� ��������
void SelectSort(Student students[], int num_student, ST_KEY st_key);	// �������� �Լ�

#endif