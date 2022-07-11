#ifndef MYSTRING_H
#define MYSTRING_H

#pragma warning(disable: 4996)									// scanf���� �ȶ߰� �ϴ� pragma���� 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORDTXT "words.txt"
#define SORTWORD "sorted_words.txt"
#define MAX_NUM_WORDS 1000
#define MAX_WORD_LEN 20
#define Line_per_Words 10

char** fGetWords(FILE* fin, int* num_words, int NOW, int LOW);	// �����Ҵ�, �����б� �Լ�
void DeleteWords(char** Words, int NOW);						// �����Ҵ� ����
void PrintWords(FILE* fout, char** Words, int NoW);				// �ܾ ���Ͽ� ����ϴ� �Լ�
void SelectionSortWords(char** Words, int num_words);			// �ܾ� ���� ���� �Լ�

#endif // !MYSTRING_H
