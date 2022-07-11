#include "Student.h"

void printStudent(Student* pSt)								//�л� ���� ����Լ�
{
	// �л� ������ ���, ��¥�� ��ȭ��ȣ�� ����Լ��� ���� �����Ƿ� ��� �ڵ带 �ۼ���
	printf("Student [ID: %8d, %10s, GPA: %4.2lf, ", pSt->st_id, pSt->name, pSt->GPA);
	printDate(pSt->date_of_birth);
	printf(", ");
	printTelNumber(pSt->tel_no);
	printf("]\n");
}

void printStudents(Student* stArray, int num_student)		//�л� ���� ����Ʈ ���
{
	// �л��� ������ ����ϴ°� �л�����ŭ �ݺ���
	printf("\n");
	for (int i = 0; i < num_student; i++)
	{
		printStudent(&stArray[i]);
	}
}

void suffleStudents(Student students[], int num_student)	// �л� ����Ʈ ���� 
{
	Student temp;
	int suffle_count = 0;
	RANDOMIZE();						//���� �õ� ����

	while (1)
	{
		int a = rand() % num_student;	// �л� �ε�����ȣ�� �������� ����
		int b = rand() % num_student;	// ����

		if (suffle_count == Suffle_Max) //���� ������ Ƚ���� 30���� �Ѿ��ٸ�
			break;						// ����

		if (a == b)						// ���� a, b�� ���ٸ� �ٽ�
			continue;
		else
		{
			temp = students[a];			//�ٲٱ�
			students[a] = students[b];
			students[b] = temp;
			suffle_count++;				//������ Ƚ�� ��
		}
	}
}

void statisticsGPA(Student students[], int num_student)			 // �ְ�, ����, ��� ���� ����� ���
{
	double maxGPA = students[0].GPA;				// maxGPA �ʱⰪ ����
	double minGPA = students[0].GPA;				// minGPA �ʱⰪ ����
	double sumGPA = students[0].GPA;				// sumGPA �ʱⰪ ���� (������ �ε��� ��ȣ�� 1���� �����ϱ� ����)
	double avgGPA = 0;								// ���� ���

	for (int i = 1; i < num_student; i++)
	{
		maxGPA = MAX(students[i].GPA, maxGPA);		// MAX ��ũ�θ� ���� maxGPA�� ����
		minGPA = MIN(students[i].GPA, minGPA);		// MIN ��ũ�θ� ���� minGPA�� ����
		sumGPA += students[i].GPA;					// ����� ���ϱ� ���� ���� �հ� ���
	}

	avgGPA = sumGPA / num_student;					// ��� ���

	// ���
	printf("GPA_max = (%4.2lf), GPA_min (%4.2lf), GPA_avg (%4.2lf)\n", maxGPA, minGPA, avgGPA);	
}

Student* searchBestGPAStu(Student students[], int num_student)		//�ְ� ���� �л� ����
{
	double maxGPA = students[0].GPA;				// maxGPA�� ����
	int max_index = 0;								// �ְ� ���� �л� �ε�����ȣ�� ã�� ����

	for (int i = 1; i < num_student; i++)			//�ʱⰪ�� �ε��� 0��, �׷��� 1������ ����
	{
		if (maxGPA < students[i].GPA)
		{
			max_index = i;							// �ε��� ��ȣ ���� �� �ְ����� ����
			maxGPA = students[i].GPA;
		}
	}

	return &(students[max_index]);					// �л� ����Ʈ���� �ְ� ���� �л� ��ġ �ּҸ� ��ȯ
}

Student* searchWorstGPAStu(Student students[], int num_student)		//���� ���� �л� ����
{
	double minGPA = students[0].GPA;				// minGPA�� ����
	int min_index = 0;								// ���� ���� �л� �ε�����ȣ�� ã�� ����

	for (int i = 1; i < num_student; i++)			// �ʱⰪ�� �ε��� 0��, �׷��� 1������ ����
	{
		if (minGPA > students[i].GPA)
		{
			min_index = i;							// �ε��� ��ȣ ���� �� �������� ����
			minGPA = students[i].GPA;
		}
	}

	return &(students[min_index]);					// �л� ����Ʈ���� ���� ���� �л� ��ġ �ּҸ� ��ȯ
}

int compareStudents(Student* pST1, Student* pST2, ST_KEY st_key)	// �л� �� �Լ�
{
	switch (st_key)
	{
	case ST_ID:									// ST_ID �� ��� 
	{
		if (pST1->st_id > pST2->st_id)			// ũ�� 1, ������ -1, ������ 0
			return 1;
		else if (pST1->st_id < pST2->st_id)
			return -1;
		else
			return 0;
	}
	case NAME:									// NAME �� ��� 
	{
		return strcmp(pST1->name, pST2->name);	// ũ�� 1, ������ -1, ������ 0
	}
	case GPA:									// GPA �� ��� 
	{
		if (pST1->GPA > pST2->GPA)				// ũ�� 1, ������ -1, ������ 0
			return 1;
		else if (pST1->GPA < pST2->GPA)
			return -1;
		else
			return 0;
	}
	case DOB:									// DOB(Date of Birth) �� ��� 
	{
		return compareDate(pST1->date_of_birth, pST2->date_of_birth);	 // ũ�� 1, ������ -1, ������ 0
	}
	case TEL:									// TEL �� ��� 
	{
		return compareTelNumber(pST1->tel_no, pST2->tel_no);	 // ũ�� 1, ������ -1, ������ 0
	}
	// �⺻ ��ȯ�� 0 ����
	default :
		return 0;
	}
}

void sortStudent(Student students[], int num_student, ST_KEY st_key)	// �л� ���� �Լ�
{
	switch (st_key)
	{
	// �й�, NAME, DOB(����), TEL(����)�� �������� ����
	case ST_ID:		
	case NAME:
	case DOB:
	case TEL:
	{
		SelectSort(students, num_student, st_key);
		break;
	}
	// GPA(����)�� �������� ����
	case GPA:		
	{
		SelectSort(students, num_student, st_key);
		break;
	}
	}
}

void SelectSort(Student students[], int num_student, ST_KEY st_key)		// ���� �Լ�
{
	Student temp;										// �� �ٲٱ����� �ӽ� ����
	int sort_Index = 0;									// ���� ���� �ε��� ��

	// ������ �������� ��������
	if (st_key == GPA)	
	{
		int max_Index = 0;								// �ִ밪�� �ε��� ��ȣ�� ã�� (���������̱� ����)
		while (1) 
		{
			if (sort_Index == num_student)				// ���� ���� ���� �ε��� ���� �迭�� ������ ����� ����
				break;

			temp = students[sort_Index];
			max_Index = sort_Index;

			for (int i = sort_Index; i < num_student; i++)
			// ���� ���� �ε��� ��ȣ������ �ε����� ������ ������ �ε��� ��ȣ���� �ּҰ��� ã��
			{
				if (compareStudents(&temp, &students[i], st_key) == -1)
				{
					temp = students[i];
					max_Index = i;
				}
			}

			//�� �ٲٱ�
			students[max_Index] = students[sort_Index];
			students[sort_Index] = temp;
			sort_Index++;								//���� ���� ��ȣ ���� 
		}
	}

	// �ٸ� ������ ��������
	else
	{
		int min_Index = 0;								// �ּҰ��� �ε��� ��ȣ�� ã��
		while (1) 
		{	
			if (sort_Index == num_student)				// ���� ���� ���� �ε��� ���� �迭�� ������ ����� ����
				break;

			temp = students[sort_Index];
			min_Index = sort_Index;

			for (int i = sort_Index; i < num_student; i++)
			// ���� ���� �ε��� ��ȣ������ �ε����� ������ ������ �ε��� ��ȣ���� �ּҰ��� ã��
			{
				if (compareStudents(&temp, &students[i], st_key) == 1)
				{
					temp = students[i];
					min_Index = i;
				}
			}

			//�� �ٲٱ�
			students[min_Index] = students[sort_Index];
			students[sort_Index] = temp;
			sort_Index++;								// ���� ���� ��ȣ ���� 
		}
	}
}