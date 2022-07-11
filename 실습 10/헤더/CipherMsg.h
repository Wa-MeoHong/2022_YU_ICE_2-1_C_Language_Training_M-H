#ifndef CIPHERMSG_H
#define CIPHERMSG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGTXT "Message.txt"
#define TRASMIT "Transmit.txt"
#define OUTPUTMSG "OutPutMsg.txt"
#define MAX_LEN 150												// 한번에 읽어올 문자의 개수

unsigned char xtoa(unsigned char uc);							// 16진수를 문자로 바꿔준다.
unsigned int atox(unsigned char uc);							// 16진수 '문자'를 정수로 변환하는 함수
void CipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l); // 한 문자를 상위비트, 하위비트로 쪼개는 함수
unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l);		// 상/하위 비트로 쪼개진 문자 합치기
void CipherText(FILE* fp_msg, FILE* fp_tx, unsigned char chiper_code);	// 텍스트를 암호화하기
void DecipherText(FILE* fp_tx, FILE* fout, unsigned char chiper_code);	// 텍스트 복호화하기

#endif // !CHIPERMSG_H
