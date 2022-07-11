/*
  ���ϸ� : "�ǽ�10_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- ���ڿ� ���� �б�, ���� Ŀ�� ������ �б�(fgets), �������� Dump, ��ȣȭ �ϱ�

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 5�� 10��)
  ���� Update : Version 2.0.0, 2022�� 5�� 11��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/05/10		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/05/11		v1.0.1		  �ڵ� �ϼ�
	�Ŵ�ȫ		 2022/05/11		v1.1.0		  �ڵ� ����ȭ
	�Ŵ�ȫ		 2022/05/11		v1.2.0		  �޴� 1�� �ڵ� ���� �� ����ȭ
	�Ŵ�ȫ		 2022/05/11		v2.0.0		  �޴� 4�� �ٽ� ����

===========================================================================================================
*/

#include "Mystring.h"
#include "Student.h"
#include "HandlingBF.h"
#include "CipherMsg.h"
#include <conio.h>

int printmenu();								// �޴� ��� �Լ�
void test_SelectionSortWords();					// �ܾ� ��������
void test_RandomFileAccess_Student();			// �л����� ���� ��, �������� ���
void test_BinaryFileDump();						// ���ĵ� �л����� �ؽ�Ʈ ������ �������Ϸ� �ѹ� ����
void test_Simple_Chiper_text();					// ���� ��ȣȭ, ��ȣȭ �۾�

int main(void)
{
	int Menu;

	while (1)
	{
		if ((Menu = printmenu()) == 0)			// �޴� �Է��� ������ 0�� ������ ����
			break;

		// �޴��� ���� ���� ����
		switch (Menu)							
		{
		case 1:
			test_SelectionSortWords();			// �ܾ� ��������
			break;
		case 2:
			test_RandomFileAccess_Student();	// �л����� ���� ��, �������� ���
			break;
		case 3:
			test_BinaryFileDump();				// ���ĵ� �л����� �ؽ�Ʈ ������ �������Ϸ� �ѹ� ����
			break;
		case 4:
			test_Simple_Chiper_text();			// ���� ��ȣȭ, ��ȣȭ �۾�
			break;
		default:
			break;
		}

		// ������ ���� ��, �޴��� ���ư����� Ű �Է�
		printf("-------------------Press any key to go to menu---------------------\n"); 
		_getch();
		system("cls"); // �ܼ�â�� �ѹ� ���ٰ� �ٽ� while�� ÷���� ���ư��� �޴� ���
	}
	return 0;
}

int printmenu()										// �޴� ��� �Լ�
{
	int menu;

	// �޴� ���
	printf("================================MENU===============================\n");
	printf("	1. Test selection sort for words\n");
	printf("	2. Test random access file for students records\n");
	printf("	3. Test Binary File Dump (BFD)\n");
	printf("	4. Test chiper text (encryption, decryption)\n");
	printf("	0. Quit\n");
	printf("===================================================================\n");

	// �޴� �Է�
	printf(" INPUT MENU : ");
	scanf("%d", &menu); 

	return menu;
}

void test_SelectionSortWords()					// �ܾ� ���Ͽ��� ���� ��, �������� �� ���Ͽ� ���
{
	FILE* fin = NULL,* fout = NULL;				// ���������͵�
	char** Words = NULL;						// �ܾ� ���� ������( �����Ҵ��� �迭�� ���� ������)
	int num_Words = 0;							// �ܾ��� �� ����
	
	if ((fin = fopen(WORDTXT, "r")) == NULL)	// �Է� ���� ����
	{
		printf("Error! Not open words.txt file!!\n");
		exit(-1);
	}
	
	if ((fout = fopen(SORTWORD, "w")) == NULL)	// ��� ���� ����
	{
		printf("Error! Not open sorted_words.txt file!!\n");
		exit(-1);
	}

	// ���Ͽ��� �ܾ���� �о���� �����Ҵ��� �迭�� ����ְ� �� �ּҸ� ��ȯ�޴´�.
	Words = fGetWords(fin, &num_Words, MAX_NUM_WORDS, MAX_WORD_LEN);
	SelectionSortWords(Words, num_Words);		// �ܾ�� ��������
	PrintWords(fout, Words, num_Words);			// ȭ��, ���Ͽ� ���
	DeleteWords(Words, MAX_NUM_WORDS);			// �����Ҵ��� �迭 �����Ҵ� ����
	fcloseall();								// ���� �ݱ�
}

void test_RandomFileAccess_Student()			// �л� ���� ���� ��, ���� Ŀ���� ������ �� ���� �о ������������ ���
{
	FILE* fin = NULL,* fout = NULL;				// ���� �����͵�
	extern Student students[NUM_STUDENTS];		// �ܺκ���(StudentRecords.c�� ��� �迭)
	char Stud_record[MAX_STRING_LEN] = { 0 };	// ������ �л� ������ �о�� ���ڿ�
	int record_len;								// ���� ������ ����
	int cur_pos;								// Ŀ���� ��ġ�� ��ȯ���� ����

//----------------------------------�л� ����-------------------------------------------
	
	if ((fout = fopen(SORTSTUD, "w")) == NULL)				// Sorted_Students.txt�� ������� ����
	{
		printf("Error! Not open Sorted_Students.txt file!!\n");
		exit(-1);
	}

	printf("\nArray of students at initialization : \n");	// ���� �� �л� ���
	printStudents(students, NUM_STUDENTS); printf("\n");

	SelectSort_by_ST_ID(students, NUM_STUDENTS);			// ���� ���� 

	// ���� �� �л� ���
	printf("Storing sorted students by increasing order of student ID into Sorted_Student.txt ....\n");
	printStudents(students, NUM_STUDENTS); printf("\n");	
	FprintStudents(fout, students, NUM_STUDENTS); 

	// ������ �ݾ��ش�
	fclose(fout);

//----------------------------------������ ���� �б�-------------------------------------------
	
	if ((fin = fopen(SORTSTUD, "r")) == NULL)				// ���� �б���� ����.
	{
		printf("Error! Not open Sorted_Students.txt file!!\n");
		exit(-1);
	}

	fgets(Stud_record, MAX_STRING_LEN, fin);				// ���Ͽ��� ���ڿ� 1���� �а� ����(Ȥ�� �ִ� ������ŭ �а�)
	record_len = strlen(Stud_record);						// ���� ���ڰ��� ����
	rewind(fin);											// ����Ŀ���� �� ó������ ����

	printf("\nRandom access to Sorted_students.txt file (Student record length: %d) ...\n", record_len);
	for (int i = NUM_STUDENTS - 1; i >= 0; i--)				// ������������ �б� ���ؼ� i�� �ٿ����� �������� ����
	{
		fseek(fin, (record_len + 1) * i, SEEK_SET);			// 90��° ���� = 2��°�� ����, SEEK_SET(������ ��ó������ ����)
		// �� i = 9���� �����̰�, len + 1�� �ұ�? len�� �� ���� �� �������� ��ġ. ó������ �б� ���ؼ� + 1�� ���ش�.
		cur_pos = ftell(fin);								// ���� Ŀ���� ��ġ�� �о�´�.
		printf("Current file_position : %3d\n", cur_pos);	// Ŀ���� ��ġ�� ǥ��
		fgets(Stud_record, MAX_STRING_LEN, fin);			// ������ ����(�л��� ����)�� �о� Stud_record�� ����
		printf("Student (%2d): %s", i, Stud_record);		// ���
	}
	printf("\n");
	fclose(fin);											// ��� ������ ������ ������ �ݴ´�.
	suffleStudents(students, NUM_STUDENTS);					// �������� ������
}

void test_BinaryFileDump()									// ���� ���� ����
{
	FILE* fin = NULL, *fout = NULL;

	if ((fin = fopen(SORTSTUD, "rb")) == NULL)				// ���� ���ĵ� �л� ���� �ؽ�Ʈ ������ ���� �б���� ����
	{
		printf("Error! Not open Sorted_Students.txt file in Binary mode!!\n");
		exit(-1);
	}

	if ((fout = fopen(OUTPUT, "w")) == NULL)				// �о�� ���������� ���� ��¿� ���� ����
	{
		printf("Error! Not open Output.txt file!!\n");
		exit(-1);
	}

	// ���� ����
	printf("\n Dumping binary file (%s) ... \n", SORTSTUD);
	DumpBinaryFile(fin, fout);
	printf(" Done. Please Check Output.txt. \n\n");
	fcloseall();											// ��� ������ ������ ������ �ݴ´�.
}	

void test_Simple_Chiper_text()								// ���� ��ȣȭ, ��ȣȭ �۾�
{
	FILE* fp_msg = NULL, * fp_tx = NULL, * fout = NULL;		// ���������͵�
	int Cipher_code = 0;
	char c = 0;

	if ((fp_msg = fopen(MSGTXT, "r")) == NULL)				// �޼��� ���� ������ �б���� ����
	{
		printf("Error! Not open Message.txt file!!\n");
		exit(-1);
	}

	printf(" Text message to be chipered : \n\n");			// ���� �޼����� ���Ͽ��� �а� ����Ѵ�. 
	while (fscanf(fp_msg, "%c", &c) != EOF)
		printf("%c", c);
	printf("\n\n");
	
	while (1)
	{
		rewind(fp_msg);										// �Ʊ� ������ �о��� ������ Ŀ����ġ�� �ٽ� �ű�
		printf(" Input Chiper_code ( -1 : Quit) : ");		// ��ȣȭ �ڵ� �Է�
		scanf("%x", &Cipher_code);
		if (Cipher_code == EOF)								// -1 �Է½� ������
			break;

		if ((fp_tx = fopen(TRASMIT, "w")) == NULL)			// ��ȣȭ�� ������ ���� ������ ������� ����, ������ �������
		{
			printf("Error! Not open Transmit.txt file!!\n");
			exit(-1);
		}

		// ��ȣ �ڵ�� ���� ��ȣȭ
		printf("Generating cipher text with cipher-code (%#04x) ..\n", Cipher_code); 
		Waiting();	CipherText(fp_msg, fp_tx, Cipher_code);		// ��ȣȭ
		printf("\n\nSuccess Chiper text Generating. Close Transmit.txt.. \n");
		fclose(fp_tx);											// ��ȣȭ �� ���� �ݱ����� �ݱ�

		if ((fout = fopen(OUTPUTMSG, "w")) == NULL)				// ��� ������ ������� ����, ������ �������
		{
			printf("Error! Not open OutPutMsg.txt file!!\n");
			exit(-1);
		}

		rewind(fp_msg);											// ���� ���� ������ ���� �ٽ� Ŀ���� �̵�
		fprintf(fout, "Binary dump of Message.txt file : \n");	// ���� ������ ������Ͽ� ���
		DumpBinaryFile(fp_msg, fout);							// ����

		if ((fp_tx = fopen(TRASMIT, "r")) == NULL)				// ��ȣȭ�� ���� ������ �б���� ����, ������ �������
		{
			printf("Error! Not open Transmit.txt file!!\n");
			exit(-1);
		}

		// ��ȣȭ�� ���� ���� ����
		fprintf(fout, "\n===================================================================\n"); 
		fprintf(fout, "Binary dump of ciphered document: \n"); 
		DumpBinaryFile(fp_tx, fout);							// ����

		// ��ȣȭ ����
		printf("Decryption Transmit.txt file with cipher-code (%#04x) ..\n", Cipher_code); 
		fprintf(fout, "\nDecryption Transmit.txt file with cipher-code (%#04x) ..\n", Cipher_code);
		Waiting(); DecipherText(fp_tx, fout, Cipher_code);		// ��ȣȭ

		printf("\n===================================================================\n");
		fclose(fp_tx); fclose(fout);							// ���⼭ ������ �͵��� �ݾ������
	}
	printf(" DONE. Please Check OutPutMSG.txt. \n");
	fcloseall();												// ���� ��� ������ ���� �ݾ��ش�
}