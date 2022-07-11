/*
  파일명 : "실습10_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 문자열 파일 읽기, 파일 커서 조정후 읽기(fgets), 이진파일 Dump, 암호화 하기

  프로그램 작성자 : 신대홍(2022년 5월 10일)
  최종 Update : Version 2.0.0, 2022년 5월 11일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/05/10		v1.0.0		  최초작성
	신대홍		 2022/05/11		v1.0.1		  코드 완성
	신대홍		 2022/05/11		v1.1.0		  코드 최적화
	신대홍		 2022/05/11		v1.2.0		  메뉴 1번 코드 통합 및 최적화
	신대홍		 2022/05/11		v2.0.0		  메뉴 4번 다시 만듦

===========================================================================================================
*/

#include "Mystring.h"
#include "Student.h"
#include "HandlingBF.h"
#include "CipherMsg.h"
#include <conio.h>

int printmenu();								// 메뉴 출력 함수
void test_SelectionSortWords();					// 단어 선택정렬
void test_RandomFileAccess_Student();			// 학생정보 정렬 후, 내림차순 출력
void test_BinaryFileDump();						// 정렬된 학생정보 텍스트 파일을 이진파일로 한번 덤핑
void test_Simple_Chiper_text();					// 파일 암호화, 복호화 작업

int main(void)
{
	int Menu;

	while (1)
	{
		if ((Menu = printmenu()) == 0)			// 메뉴 입력을 받을때 0을 받으면 종료
			break;

		// 메뉴에 따라서 동작 수행
		switch (Menu)							
		{
		case 1:
			test_SelectionSortWords();			// 단어 선택정렬
			break;
		case 2:
			test_RandomFileAccess_Student();	// 학생정보 정렬 후, 내림차순 출력
			break;
		case 3:
			test_BinaryFileDump();				// 정렬된 학생정보 텍스트 파일을 이진파일로 한번 덤핑
			break;
		case 4:
			test_Simple_Chiper_text();			// 파일 암호화, 복호화 작업
			break;
		default:
			break;
		}

		// 동작을 끝낸 후, 메뉴로 돌아가기전 키 입력
		printf("-------------------Press any key to go to menu---------------------\n"); 
		_getch();
		system("cls"); // 콘솔창을 한번 껏다가 다시 while문 첨으로 돌아가서 메뉴 출력
	}
	return 0;
}

int printmenu()										// 메뉴 출력 함수
{
	int menu;

	// 메뉴 출력
	printf("================================MENU===============================\n");
	printf("	1. Test selection sort for words\n");
	printf("	2. Test random access file for students records\n");
	printf("	3. Test Binary File Dump (BFD)\n");
	printf("	4. Test chiper text (encryption, decryption)\n");
	printf("	0. Quit\n");
	printf("===================================================================\n");

	// 메뉴 입력
	printf(" INPUT MENU : ");
	scanf("%d", &menu); 

	return menu;
}

void test_SelectionSortWords()					// 단어 파일에서 읽은 후, 선택정렬 후 파일에 출력
{
	FILE* fin = NULL,* fout = NULL;				// 파일포인터들
	char** Words = NULL;						// 단어 이중 포인터( 동적할당한 배열을 담을 포인터)
	int num_Words = 0;							// 단어의 총 개수
	
	if ((fin = fopen(WORDTXT, "r")) == NULL)	// 입력 파일 열기
	{
		printf("Error! Not open words.txt file!!\n");
		exit(-1);
	}
	
	if ((fout = fopen(SORTWORD, "w")) == NULL)	// 출력 파일 열기
	{
		printf("Error! Not open sorted_words.txt file!!\n");
		exit(-1);
	}

	// 파일에서 단어들을 읽어오고 동적할당한 배열에 집어넣고 그 주소를 반환받는다.
	Words = fGetWords(fin, &num_Words, MAX_NUM_WORDS, MAX_WORD_LEN);
	SelectionSortWords(Words, num_Words);		// 단어들 선택정렬
	PrintWords(fout, Words, num_Words);			// 화면, 파일에 출력
	DeleteWords(Words, MAX_NUM_WORDS);			// 동적할당한 배열 동적할당 해제
	fcloseall();								// 파일 닫기
}

void test_RandomFileAccess_Student()			// 학생 정보 정렬 후, 파일 커서를 지정해 그 줄을 읽어서 내림차순으로 출력
{
	FILE* fin = NULL,* fout = NULL;				// 파일 포인터들
	extern Student students[NUM_STUDENTS];		// 외부변수(StudentRecords.c에 담긴 배열)
	char Stud_record[MAX_STRING_LEN] = { 0 };	// 정렬한 학생 파일을 읽어올 문자열
	int record_len;								// 읽은 문자의 개수
	int cur_pos;								// 커서의 위치를 반환받을 변수

//----------------------------------학생 정렬-------------------------------------------
	
	if ((fout = fopen(SORTSTUD, "w")) == NULL)				// Sorted_Students.txt를 쓰기모드로 열기
	{
		printf("Error! Not open Sorted_Students.txt file!!\n");
		exit(-1);
	}

	printf("\nArray of students at initialization : \n");	// 정렬 전 학생 출력
	printStudents(students, NUM_STUDENTS); printf("\n");

	SelectSort_by_ST_ID(students, NUM_STUDENTS);			// 선택 정렬 

	// 정렬 후 학생 출력
	printf("Storing sorted students by increasing order of student ID into Sorted_Student.txt ....\n");
	printStudents(students, NUM_STUDENTS); printf("\n");	
	FprintStudents(fout, students, NUM_STUDENTS); 

	// 파일을 닫아준다
	fclose(fout);

//----------------------------------정렬한 파일 읽기-------------------------------------------
	
	if ((fin = fopen(SORTSTUD, "r")) == NULL)				// 이제 읽기모드로 연다.
	{
		printf("Error! Not open Sorted_Students.txt file!!\n");
		exit(-1);
	}

	fgets(Stud_record, MAX_STRING_LEN, fin);				// 파일에서 문자열 1줄을 읽고 저장(혹은 최대 개수만큼 읽고)
	record_len = strlen(Stud_record);						// 읽은 문자개수 구함
	rewind(fin);											// 파일커서를 맨 처음으로 돌림

	printf("\nRandom access to Sorted_students.txt file (Student record length: %d) ...\n", record_len);
	for (int i = NUM_STUDENTS - 1; i >= 0; i--)				// 내림차순으로 읽기 위해서 i를 줄여가는 방향으로 설정
	{
		fseek(fin, (record_len + 1) * i, SEEK_SET);			// 90번째 문자 = 2번째줄 시작, SEEK_SET(기준을 맨처음으로 잡음)
		// 왜 i = 9부터 시작이고, len + 1을 할까? len은 한 줄의 맨 끝문자의 위치. 처음부터 읽기 위해선 + 1을 해준다.
		cur_pos = ftell(fin);								// 현재 커서의 위치를 읽어온다.
		printf("Current file_position : %3d\n", cur_pos);	// 커서의 위치를 표시
		fgets(Stud_record, MAX_STRING_LEN, fin);			// 파일의 한줄(학생의 정보)을 읽어 Stud_record에 저장
		printf("Student (%2d): %s", i, Stud_record);		// 출력
	}
	printf("\n");
	fclose(fin);											// 모든 동작이 끝나면 파일을 닫는다.
	suffleStudents(students, NUM_STUDENTS);					// 마지막엔 셔플함
}

void test_BinaryFileDump()									// 이진 파일 덤핑
{
	FILE* fin = NULL, *fout = NULL;

	if ((fin = fopen(SORTSTUD, "rb")) == NULL)				// 위의 정렬된 학생 정보 텍스트 파일을 이진 읽기모드로 연다
	{
		printf("Error! Not open Sorted_Students.txt file in Binary mode!!\n");
		exit(-1);
	}

	if ((fout = fopen(OUTPUT, "w")) == NULL)				// 읽어온 이진파일을 담을 출력용 파일 열기
	{
		printf("Error! Not open Output.txt file!!\n");
		exit(-1);
	}

	// 파일 덤핑
	printf("\n Dumping binary file (%s) ... \n", SORTSTUD);
	DumpBinaryFile(fin, fout);
	printf(" Done. Please Check Output.txt. \n\n");
	fcloseall();											// 모든 동작이 끝나면 파일을 닫는다.
}	

void test_Simple_Chiper_text()								// 파일 암호화, 복호화 작업
{
	FILE* fp_msg = NULL, * fp_tx = NULL, * fout = NULL;		// 파일포인터들
	int Cipher_code = 0;
	char c = 0;

	if ((fp_msg = fopen(MSGTXT, "r")) == NULL)				// 메세지 원본 파일을 읽기모드로 열기
	{
		printf("Error! Not open Message.txt file!!\n");
		exit(-1);
	}

	printf(" Text message to be chipered : \n\n");			// 원본 메세지를 파일에서 읽고 출력한다. 
	while (fscanf(fp_msg, "%c", &c) != EOF)
		printf("%c", c);
	printf("\n\n");
	
	while (1)
	{
		rewind(fp_msg);										// 아까 파일을 읽었기 때문에 커서위치를 다시 옮김
		printf(" Input Chiper_code ( -1 : Quit) : ");		// 암호화 코드 입력
		scanf("%x", &Cipher_code);
		if (Cipher_code == EOF)								// -1 입력시 나가기
			break;

		if ((fp_tx = fopen(TRASMIT, "w")) == NULL)			// 암호화된 내용을 담을 파일을 쓰기모드로 열기, 못열면 오류출력
		{
			printf("Error! Not open Transmit.txt file!!\n");
			exit(-1);
		}

		// 암호 코드로 이제 암호화
		printf("Generating cipher text with cipher-code (%#04x) ..\n", Cipher_code); 
		Waiting();	CipherText(fp_msg, fp_tx, Cipher_code);		// 암호화
		printf("\n\nSuccess Chiper text Generating. Close Transmit.txt.. \n");
		fclose(fp_tx);											// 암호화 후 파일 닫기파일 닫기

		if ((fout = fopen(OUTPUTMSG, "w")) == NULL)				// 출력 파일을 쓰기모드로 열기, 못열면 오류출력
		{
			printf("Error! Not open OutPutMsg.txt file!!\n");
			exit(-1);
		}

		rewind(fp_msg);											// 이진 파일 덤핑을 위해 다시 커서로 이동
		fprintf(fout, "Binary dump of Message.txt file : \n");	// 파일 덤핑을 출력파일에 출력
		DumpBinaryFile(fp_msg, fout);							// 덤핑

		if ((fp_tx = fopen(TRASMIT, "r")) == NULL)				// 암호화된 내용 파일을 읽기모드로 열기, 못열면 오류출력
		{
			printf("Error! Not open Transmit.txt file!!\n");
			exit(-1);
		}

		// 암호화된 내용 파일 덤핑
		fprintf(fout, "\n===================================================================\n"); 
		fprintf(fout, "Binary dump of ciphered document: \n"); 
		DumpBinaryFile(fp_tx, fout);							// 덤핑

		// 복호화 진행
		printf("Decryption Transmit.txt file with cipher-code (%#04x) ..\n", Cipher_code); 
		fprintf(fout, "\nDecryption Transmit.txt file with cipher-code (%#04x) ..\n", Cipher_code);
		Waiting(); DecipherText(fp_tx, fout, Cipher_code);		// 복호화

		printf("\n===================================================================\n");
		fclose(fp_tx); fclose(fout);							// 여기서 열었던 것들은 닫아줘야함
	}
	printf(" DONE. Please Check OutPutMSG.txt. \n");
	fcloseall();												// 열린 모든 파일을 전부 닫아준다
}