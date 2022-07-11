#include "Student.h"
#include <Windows.h>
#include <conio.h>

#define MAX_NUM_STUDENTS 100							// 최대 학생수 
void printmenu(int num_students, int* menu);

int main(void)
{
	int num_students = 0;								// 학생 수
	int menu;									
	Student* pST_GPA_max, * pST_GPA_min;				// 최고 학점, 최저학점 학생 찾는데 쓰는 구조체 포인터
	extern Student students[];							// 외부 배열변수 students[]

	for (int i = 0; i < MAX_NUM_STUDENTS; i++)			// 학생수 알아내는 과정
	{
		if (students[i].st_id == -1)					// 학생 배열에서 -1인 지점을 만나게 된다면(학번에 저장된 -1)
			break;										// 학생수를 찾는것을 그만둠
		else
		{
			num_students++;								// 학생수++
		}
	}

	while (1)
	{
		printmenu(num_students, &menu);
		if (menu == 0)										// 0을 입력하면 break로 반복문 나가기
			break;

		switch (menu)										// switch 메뉴
		{
		case 1:												// 1번(학생 리스트 출력)
		{
			printStudents(students, num_students);
			printf("\n");
			break;
		}
		case 2:												// 최고 학점, 최저 학점, 학점 평균 계산 후 출력
		{
			printf("\n");
			statisticsGPA(students, num_students);
			printf("\n");
			break;
		}
		case 3:												// 최고 학점인 학생, 최저 학점인 학생을 찾아서 출력
		{
			printf("\n");
			pST_GPA_max = searchBestGPAStu(students, num_students); //최고 학점 학생을 찾아서 그 학생 리스트 안의 주소를 반환받음
			pST_GPA_min = searchWorstGPAStu(students, num_students); //최저 학점 학생을 찾아 구조체배열 안의 위치주소값을 반환받음
			printf("Student with Best GPA : ");
			printStudent(pST_GPA_max);						//최고 학점 학생 출력
			printf("Student with Worst GPA : ");
			printStudent(pST_GPA_min);						//최저 학점 학생 출력
			printf("\n");
			break;
		}
		case 4:
		{
			sortStudent(students, num_students, ST_ID);		// 학번을 기준으로 오름차순 정렬
			// 출력
			printf("\nAfter sorting students by increasing order of student ID: ");
			printStudents(students, num_students);
			printf("\n");
			break;
		}
		case 5:
		{
			sortStudent(students, num_students, GPA);		// GPA(학점)을 기준으로 내림차순 정렬
			// 출력
			printf("\nAfter sorting students by decreasing order of GPA: ");
			printStudents(students, num_students);
			printf("\n");
			break;
		}
		case 6:
		{
			sortStudent(students, num_students, NAME);		// 이름을 기준으로 오름차순 정렬
			// 출력
			printf("\nAfter sorting students by increasing order of student name: ");
			printStudents(students, num_students);
			printf("\n");
			break;
		}
		case 7:
		{
			sortStudent(students, num_students, DOB);		// 생일을 기준으로 오름차순 정렬
			// 출력
			printf("\nAfter sorting students by increasing order of student Birth date: ");
			printStudents(students, num_students);
			printf("\n");
			break;
		}
		case 8:
		{
			sortStudent(students, num_students, TEL);		// 전화번호을 기준으로 오름차순 정렬
			// 출력
			printf("\nAfter sorting students by increasing order of student's TelNumber: ");
			printStudents(students, num_students);			
			printf("\n");
			break;
		}
		default:											// 메뉴의 다른 것을 눌렀을 때
			break;											// while 반복함
		}
		suffleStudents(students, num_students);				// 학생 정보 뒤섞기
		printf("--------------------Press any key to go to menu----------------------\n");
		_getch();
		system("cls");
	}
	return 0;
}

void printmenu(int num_students, int* menu)					// 메인메뉴 출력 함수
{
	printf("Number of students = %d\n", num_students);		//학생수 출력
	
	// 메뉴 출력
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
	
	// 메뉴 입력
	printf("Input menu = ");
	scanf("%d", &(*menu));						
}