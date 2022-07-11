#ifndef CIPHERMSG_H
#define CIPHERMSG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGTXT "Message.txt"
#define TRASMIT "Transmit.txt"
#define OUTPUTMSG "OutPutMsg.txt"
#define MAX_LEN 150												// �ѹ��� �о�� ������ ����

unsigned char xtoa(unsigned char uc);							// 16������ ���ڷ� �ٲ��ش�.
unsigned int atox(unsigned char uc);							// 16���� '����'�� ������ ��ȯ�ϴ� �Լ�
void CipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l); // �� ���ڸ� ������Ʈ, ������Ʈ�� �ɰ��� �Լ�
unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l);		// ��/���� ��Ʈ�� �ɰ��� ���� ��ġ��
void CipherText(FILE* fp_msg, FILE* fp_tx, unsigned char chiper_code);	// �ؽ�Ʈ�� ��ȣȭ�ϱ�
void DecipherText(FILE* fp_tx, FILE* fout, unsigned char chiper_code);	// �ؽ�Ʈ ��ȣȭ�ϱ�

#endif // !CHIPERMSG_H
