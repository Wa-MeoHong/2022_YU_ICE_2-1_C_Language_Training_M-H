#include "Student.h"

void printStudent(Student* pSt)								//학생 정보 출력함수
{
	// 학생 정보를 출력, 날짜와 전화번호는 출력함수가 따로 있으므로 끊어서 코드를 작성함
	printf("Student [ID: %8d, %10s, GPA: %4.2lf, ", pSt->st_id, pSt->name, pSt->GPA);
	printDate(pSt->date_of_birth);
	printf(", ");
	printTelNumber(pSt->tel_no);
	printf("]\n");
}

void printStudents(Student* stArray, int num_student)		//학생 정보 리스트 출력
{
	// 학생의 정보를 출력하는걸 학생수만큼 반복함
	printf("\n");
	for (int i = 0; i < num_student; i++)
	{
		printStudent(&stArray[i]);
	}
}

void suffleStudents(Student students[], int num_student)	// 학생 리스트 셔플 
{
	Student temp;
	int suffle_count = 0;
	RANDOMIZE();						//랜덤 시드 생성

	while (1)
	{
		int a = rand() % num_student;	// 학생 인덱스번호를 랜덤으로 생성
		int b = rand() % num_student;	// 동일

		if (suffle_count == Suffle_Max) //만약 셔플한 횟수가 30번이 넘었다면
			break;						// 종료

		if (a == b)						// 만약 a, b가 같다면 다시
			continue;
		else
		{
			temp = students[a];			//바꾸기
			students[a] = students[b];
			students[b] = temp;
			suffle_count++;				//셔플한 횟수 업
		}
	}
}

void statisticsGPA(Student students[], int num_student)			 // 최고, 최저, 평균 학점 산출및 출력
{
	double maxGPA = students[0].GPA;				// maxGPA 초기값 설정
	double minGPA = students[0].GPA;				// minGPA 초기값 설정
	double sumGPA = students[0].GPA;				// sumGPA 초기값 설정 (이유는 인덱스 번호가 1부터 시작하기 때문)
	double avgGPA = 0;								// 학점 평균

	for (int i = 1; i < num_student; i++)
	{
		maxGPA = MAX(students[i].GPA, maxGPA);		// MAX 매크로를 통해 maxGPA값 변경
		minGPA = MIN(students[i].GPA, minGPA);		// MIN 매크로를 통해 minGPA값 변경
		sumGPA += students[i].GPA;					// 평균을 구하기 위해 학점 합계 계산
	}

	avgGPA = sumGPA / num_student;					// 평균 계산

	// 출력
	printf("GPA_max = (%4.2lf), GPA_min (%4.2lf), GPA_avg (%4.2lf)\n", maxGPA, minGPA, avgGPA);	
}

Student* searchBestGPAStu(Student students[], int num_student)		//최고 학점 학생 산출
{
	double maxGPA = students[0].GPA;				// maxGPA를 설정
	int max_index = 0;								// 최고 학점 학생 인덱스번호를 찾는 변수

	for (int i = 1; i < num_student; i++)			//초기값이 인덱스 0번, 그래서 1번부터 시작
	{
		if (maxGPA < students[i].GPA)
		{
			max_index = i;							// 인덱스 번호 갱신 및 최고학점 갱신
			maxGPA = students[i].GPA;
		}
	}

	return &(students[max_index]);					// 학생 리스트에서 최고 학점 학생 위치 주소를 반환
}

Student* searchWorstGPAStu(Student students[], int num_student)		//최저 학점 학생 산출
{
	double minGPA = students[0].GPA;				// minGPA를 설정
	int min_index = 0;								// 최저 학점 학생 인덱스번호를 찾는 변수

	for (int i = 1; i < num_student; i++)			// 초기값이 인덱스 0번, 그래서 1번부터 시작
	{
		if (minGPA > students[i].GPA)
		{
			min_index = i;							// 인덱스 번호 갱신 및 최저학점 갱신
			minGPA = students[i].GPA;
		}
	}

	return &(students[min_index]);					// 학생 리스트에서 최저 학점 학생 위치 주소를 반환
}

int compareStudents(Student* pST1, Student* pST2, ST_KEY st_key)	// 학생 비교 함수
{
	switch (st_key)
	{
	case ST_ID:									// ST_ID 일 경우 
	{
		if (pST1->st_id > pST2->st_id)			// 크면 1, 작으면 -1, 같으면 0
			return 1;
		else if (pST1->st_id < pST2->st_id)
			return -1;
		else
			return 0;
	}
	case NAME:									// NAME 일 경우 
	{
		return strcmp(pST1->name, pST2->name);	// 크면 1, 작으면 -1, 같으면 0
	}
	case GPA:									// GPA 일 경우 
	{
		if (pST1->GPA > pST2->GPA)				// 크면 1, 작으면 -1, 같으면 0
			return 1;
		else if (pST1->GPA < pST2->GPA)
			return -1;
		else
			return 0;
	}
	case DOB:									// DOB(Date of Birth) 일 경우 
	{
		return compareDate(pST1->date_of_birth, pST2->date_of_birth);	 // 크면 1, 작으면 -1, 같으면 0
	}
	case TEL:									// TEL 일 경우 
	{
		return compareTelNumber(pST1->tel_no, pST2->tel_no);	 // 크면 1, 작으면 -1, 같으면 0
	}
	// 기본 반환값 0 설정
	default :
		return 0;
	}
}

void sortStudent(Student students[], int num_student, ST_KEY st_key)	// 학생 정렬 함수
{
	switch (st_key)
	{
	// 학번, NAME, DOB(생일), TEL(전번)은 오름차순 정렬
	case ST_ID:		
	case NAME:
	case DOB:
	case TEL:
	{
		SelectSort(students, num_student, st_key);
		break;
	}
	// GPA(학점)은 오름차순 정렬
	case GPA:		
	{
		SelectSort(students, num_student, st_key);
		break;
	}
	}
}

void SelectSort(Student students[], int num_student, ST_KEY st_key)		// 정렬 함수
{
	Student temp;										// 값 바꾸기위한 임시 변수
	int sort_Index = 0;									// 정렬 기준 인덱스 값

	// 학점을 기준으로 내림차순
	if (st_key == GPA)	
	{
		int max_Index = 0;								// 최대값의 인덱스 번호를 찾음 (내림차순이기 때문)
		while (1) 
		{
			if (sort_Index == num_student)				// 만약 정렬 기준 인덱스 값이 배열의 범위를 벗어나면 종료
				break;

			temp = students[sort_Index];
			max_Index = sort_Index;

			for (int i = sort_Index; i < num_student; i++)
			// 정렬 기준 인덱스 번호까지의 인덱스를 제외한 나머지 인덱스 번호에서 최소값을 찾음
			{
				if (compareStudents(&temp, &students[i], st_key) == -1)
				{
					temp = students[i];
					max_Index = i;
				}
			}

			//값 바꾸기
			students[max_Index] = students[sort_Index];
			students[sort_Index] = temp;
			sort_Index++;								//정렬 기준 번호 증가 
		}
	}

	// 다른 기준은 오름차순
	else
	{
		int min_Index = 0;								// 최소값의 인덱스 번호를 찾음
		while (1) 
		{	
			if (sort_Index == num_student)				// 만약 정렬 기준 인덱스 값이 배열의 범위를 벗어나면 종료
				break;

			temp = students[sort_Index];
			min_Index = sort_Index;

			for (int i = sort_Index; i < num_student; i++)
			// 정렬 기준 인덱스 번호까지의 인덱스를 제외한 나머지 인덱스 번호에서 최소값을 찾음
			{
				if (compareStudents(&temp, &students[i], st_key) == 1)
				{
					temp = students[i];
					min_Index = i;
				}
			}

			//값 바꾸기
			students[min_Index] = students[sort_Index];
			students[sort_Index] = temp;
			sort_Index++;								// 정렬 기준 번호 증가 
		}
	}
}