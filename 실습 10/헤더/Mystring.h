#ifndef MYSTRING_H
#define MYSTRING_H

#pragma warning(disable: 4996)									// scanf오류 안뜨게 하는 pragma정의 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORDTXT "words.txt"
#define SORTWORD "sorted_words.txt"
#define MAX_NUM_WORDS 1000
#define MAX_WORD_LEN 20
#define Line_per_Words 10

char** fGetWords(FILE* fin, int* num_words, int NOW, int LOW);	// 동적할당, 파읽읽기 함수
void DeleteWords(char** Words, int NOW);						// 동적할당 해제
void PrintWords(FILE* fout, char** Words, int NoW);				// 단어를 파일에 출력하는 함수
void SelectionSortWords(char** Words, int num_words);			// 단어 선택 정렬 함수

#endif // !MYSTRING_H
