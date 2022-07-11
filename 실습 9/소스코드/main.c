#include "Student.h"
#include <Windows.h>
#include <conio.h>

#define MAX_NUM_STUDENTS 100							// �ִ� �л��� 
void printmenu(int num_students, int* menu);

int main(void)
{
	int num_students = 0;								// �л� ��
	int menu;									
	Student* pST_GPA_max, * pST_GPA_min;				// �ְ� ����, �������� �л� ã�µ� ���� ����ü ������
	extern Student students[];							// �ܺ� �迭���� students[]

	for (int i = 0; i < MAX_NUM_STUDENTS; i++)			// �л��� �˾Ƴ��� ����
	{
		if (students[i].st_id == -1)					// �л� �迭���� -1�� ������ ������ �ȴٸ�(�й��� ����� -1)
			break;										// �л����� ã�°��� �׸���
		else
		{
			num_students++;								// �л���++
		}
	}

	while (1)
	{
		printmenu(num_students, &menu);
		if (menu == 0)										// 0�� �Է��ϸ� break�� �ݺ��� ������
			break;

		switch (menu)										// switch �޴�
		{
		case 1:												// 1��(�л� ����Ʈ ���)
		{
			printStudents(students, num_students);
			printf("\n");
			break;
		}
		case 2:												// �ְ� ����, ���� ����, ���� ��� ��� �� ���
		{
			printf("\n");
			statisticsGPA(students, num_students);
			printf("\n");
			break;
		}
		case 3:												// �ְ� ������ �л�, ���� ������ �л��� ã�Ƽ� ���
		{
			printf("\n");
			pST_GPA_max = searchBestGPAStu(students, num_students); //�ְ� ���� �л��� ã�Ƽ� �� �л� ����Ʈ ���� �ּҸ� ��ȯ����
			pST_GPA_min = searchWorstGPAStu(students, num_students); //���� ���� �л��� ã�� ����ü�迭 ���� ��ġ�ּҰ��� ��ȯ����
			printf("Student with Best GPA : ");
			printStudent(pST_GPA_max);						//�ְ� ���� �л� ���
			printf("Student with Worst GPA : ");
			printStudent(pST_GPA_min);						//���� ���� �л� ���
			printf("\n");
			break;
		}
		case 4:
		{
			sortStudent(students, num_students, ST_ID);		// �й��� �������� �������� ����
			// ���
			printf("\nAfter sorting students by increasing order of student ID: ");
			printStudents(students, num_students);
			printf("\n");
			break;
		}
		case 5:
		{
			sortStudent(students, num_students, GPA);		// GPA(����)�� �������� �������� ����
			// ���
			printf("\nAfter sorting students by decreasing order of GPA: ");
			printStudents(students, num_students);
			printf("\n");
			break;
		}
		case 6:
		{
			sortStudent(students, num_students, NAME);		// �̸��� �������� �������� ����
			// ���
			printf("\nAfter sorting students by increasing order of student name: ");
			printStudents(students, num_students);
			printf("\n");
			break;
		}
		case 7:
		{
			sortStudent(students, num_students, DOB);		// ������ �������� �������� ����
			// ���
			printf("\nAfter sorting students by increasing order of student Birth date: ");
			printStudents(students, num_students);
			printf("\n");
			break;
		}
		case 8:
		{
			sortStudent(students, num_students, TEL);		// ��ȭ��ȣ�� �������� �������� ����
			// ���
			printf("\nAfter sorting students by increasing order of student's TelNumber: ");
			printStudents(students, num_students);			
			printf("\n");
			break;
		}
		default:											// �޴��� �ٸ� ���� ������ ��
			break;											// while �ݺ���
		}
		suffleStudents(students, num_students);				// �л� ���� �ڼ���
		printf("--------------------Press any key to go to menu----------------------\n");
		_getch();
		system("cls");
	}
	return 0;
}

void printmenu(int num_students, int* menu)					// ���θ޴� ��� �Լ�
{
	printf("Number of students = %d\n", num_students);		//�л��� ���
	
	// �޴� ���
	printf("====================================================================\n");
	printf(" 1 : print student records\n");
	printf(" 2 : calculate statistics GPA (max, min, avg) of students \n");
	printf(" 3 : search students of best GPA and worst GPA\n");
	printf(" 4 : sort students by student ID\n");
	printf(" 5 : sort students by GPA\n");
	printf(" 6 : sort students by name\n");
	printf(" 7 : sort students by date of birth\n");
	printf(" 8 : sort students by telephone number\n");
	printf(" 0 : Quit\n");
	printf("====================================================================\n");
	
	// �޴� �Է�
	printf("Input menu = ");
	scanf("%d", &(*menu));						
}