#include "Student.h"

void printDate(Date date)									// ��¥ ��� �Լ�
{
	printf("(%4d, %2d, %2d)", date.year, date.month, date.day);
}

void printTelNumber(Tel tel_no)								// ��ȭ��ȣ ��� �Լ�
{
	printf("(tel : +%2d-0%2d-%4d-%04d)"\
		, tel_no.N_code, tel_no.R_code, tel_no.S_no, tel_no.L_no);
}

void printStudent(Student* pSt)								// �л� ���� ����Լ�
{
	// �л� ������ ���, ��¥�� ��ȭ��ȣ�� ����Լ��� ���� �����Ƿ� ��� �ڵ带 �ۼ���
	printf("Student [ID: %8d, %10s, GPA: %4.2lf, ", pSt->st_id, pSt->name, pSt->GPA);
	printDate(pSt->date_of_birth);
	printf(", ");
	printTelNumber(pSt->tel_no);
	printf("]\n");
}

void printStudents(Student* stArray, int num_student)		// �л� ���� ����Ʈ ���
{
	// �л��� ������ ����ϴ°� �л�����ŭ �ݺ���
	for (int i = 0; i < num_student; i++)
	{
		printStudent(&stArray[i]);
	}
}

void fprintDate(FILE* fout, Date date)						// ��¥ ���� ��� �Լ�
{
	fprintf(fout, "(%4d, %2d, %2d)", date.year, date.month, date.day);
}

void fprintTelNumber(FILE* fout, Tel tel_no)				// ��ȭ��ȣ ��� �Լ�
{
	fprintf(fout, "(tel : +%2d-0%2d-%4d-%04d)"\
		, tel_no.N_code, tel_no.R_code, tel_no.S_no, tel_no.L_no);
}

void FprintStudent(FILE* fout, Student* pSt)
{
	// �л� ������ ���, ��¥�� ��ȭ��ȣ�� ����Լ��� ���� �����Ƿ� ��� �ڵ带 �ۼ���
	fprintf(fout, "Student [ID: %8d, %10s, GPA: %4.2lf, ", pSt->st_id, pSt->name, pSt->GPA);
	fprintDate(fout, pSt->date_of_birth);
	fprintf(fout, ", ");
	fprintTelNumber(fout, pSt->tel_no);
	fprintf(fout, "]\n");
}

void FprintStudents(FILE* fout, Student* stArray, int num_student) // �л� ���� ����Ʈ ���
{
	// �л��� ������ ����ϴ°� �л�����ŭ �ݺ���
	for (int i = 0; i < num_student; i++)
	{
		FprintStudent(fout, &stArray[i]);
	}
}

void suffleStudents(Student* students, int num_student)		// �л� ����Ʈ ���� 
{
	Student temp;
	int suffle_count = 0;
	RANDOMIZE();								// ���� �õ� ����

	while(1)
	{
		int a = rand() % num_student;				// �л� �ε�����ȣ�� �������� ����
		int b = rand() % num_student;				// ����

		if (suffle_count == Suffle_Max)				// ���� ������ Ƚ���� 30���� �Ѿ��ٸ�
			break;									// ����

		if (a == b)									// ���� a, b�� ���ٸ� �ٽ�
			continue;
		else
		{
			temp = students[a];						// �ٲٱ�
			students[a] = students[b];
			students[b] = temp;
			suffle_count++;							// ������ Ƚ�� ��
		}
	}
}

void SelectSort_by_ST_ID(Student* students, int num_student)		// �л� ���� �Լ�
{
	Student temp;									// �� �ٲٱ����� �ӽ� ����
	int sort_IDX = 0;								// ���� ���� �ε��� ��
	int min_IDX = 0;								// �ּҰ��� �ε��� ��ȣ�� ã��
	while (1)
	{
		if (sort_IDX == num_student)				// ���� ���� ���� �ε��� ���� �迭�� ������ ����� ����
			break;
		temp = students[sort_IDX];					// �ʱⰪ ����
		min_IDX = sort_IDX;							// �ε��� �ʱⰪ ����

		for (int i = sort_IDX; i < num_student; i++)
		// ���� ���� �ε��� ��ȣ������ �ε����� ������ ������ �ε��� ��ȣ���� �ּҰ��� ã��
		{
			if (temp.st_id > students[i].st_id)		// id�� ���ϴ� ������ ũ�ٸ�
			{
				temp = students[i];					// �ּҰ� ����
				min_IDX = i;						// �ε��� ��ȣ ����
			}
		}

		// �� �ٲٱ�
		students[min_IDX] = students[sort_IDX];
		students[sort_IDX] = temp;
		sort_IDX++;									// ���� ���� ��ȣ ���� 
	}
}