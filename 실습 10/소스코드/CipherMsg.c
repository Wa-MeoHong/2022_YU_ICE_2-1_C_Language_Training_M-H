#include "CipherMsg.h"

unsigned char xtoa(unsigned char uc)						// 16������ ���ڷ� �ٲ��ش�.
{
	unsigned char Ch;

	if (uc >= 0 && uc <= 9)
		Ch = 48 + uc;								// 0 = 0x30 ~ 9 = 0x39
	else if (uc >= 10 && uc <= 15)
		Ch = 65 + uc - 10;							// A = 0x41 ~ F = 0x46 
	return Ch;
}

unsigned int atox(unsigned char uc)							 // ���ڸ� 16���������� ������ ��ȯ���ִ� �Լ�
{
	unsigned int hexVal = 0;

	if (uc >= '0' && uc <= '9')						// 0 ~ 9���� �ƽ�Ű�����϶�
		hexVal = uc - '0';							// uc(�ƽ�Ű����) - 0x30
	else if (uc >= 'A' && uc <= 'F')				// A ~ F (10 ~ 15)���� �϶�
		hexVal = uc - 'A' + 10;						// uc(�ƽ�Ű����) - 65 + (10) 
	else if (uc >= 'a' && uc <= 'f')				// a ~ f (�ҹ���, 10 ~ 15�� ����)
		hexVal = uc - 'a' + 10;						// uc(�ƽ�Ű����) - 97 + (10)

	return hexVal;
}

void CipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l) // �� ���ڸ� ������Ʈ, ������Ʈ�� �ɰ��� �Լ�
{
	char i = 0;

	i = ch >> 4;						// ������Ʈ (���� 4��Ʈ�� ���������� �δ�)
	*pCC_u = xtoa(i);

	i = ch & 0x0F;						// 0000 1111 (������Ʈ�� ��󳻱�)
	*pCC_l = xtoa(i);
}

void CipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code) // �ؽ�Ʈ�� ��ȣȭ�ϱ�
{
	unsigned char read_c = 0;							// ��ȣȭ�� ���ڸ� ��� ����
	unsigned char upper = 0;							// read_c ���� 4��Ʈ ����
	unsigned char lower = 0;							// read_c ���� 4��Ʈ ����
	int read_len = 0;									// �о�� ���ڿ��� ����
	int read_lines = 1;

	while (!(feof(fp_msg)))
	{
		unsigned char Read_Str[MAX_LEN] = { 0 };		// ���ڿ��� �о�� �ӽú���
		fgets(Read_Str, MAX_LEN, fp_msg);				// �ؽ�Ʈ���� ������ �о��
		read_len = strlen(Read_Str);					// ���ڿ� ���̸� ����

		printf("(%2d-th Input String, length %d) : ", read_lines, read_len); printf("%s", Read_Str);
		// ���� ���ڿ� ���

		for (int i = 0; i < read_len; i++)				// ������ ��� ����� �� ����
		{
			read_c = Read_Str[i] ^ cipher_code;			// Read_Str ���ڿ��� �� ���ڿ� ��ȣ�ص� �ڵ带 XOR
			CipherChar(read_c, &upper, &lower);			// �� XOR�� ���ڸ� ������Ʈ, ������Ʈ�� �ɰ��� ���ڷ� ǥ��
			fprintf(fp_tx, "%c%c", upper, lower);		// ���� ���
		}
		fprintf(fp_tx, "\n");							// ���� ��ĭ ����
		read_lines++;
	}
}

unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l)		// ��/���� ��Ʈ�� �ɰ��� ���� ��ġ��
{
	unsigned int upper = 0;
	unsigned int lower = 0;

	upper = atox(rc_u); lower = atox(rc_l);				// ���ڷ� �ٲ� ��/���� ����Ʈ���� ������ ��ü

	return (upper << 4) | lower;
}

void DecipherText(FILE* fp_tx, FILE* fout, unsigned char cipher_code)	// �ؽ�Ʈ ��ȣȭ�ϱ�
{
	unsigned char decp_c = 0;							// ��ȣȭ�� ���ڸ� ��� ����
	int read_len = 0;									// �о�� ���ڿ��� ����


	printf("\nReceived and Deciphered Message : \n");
	while (!(feof(fp_tx)))
	{
		unsigned char Read_Str[MAX_LEN] = { 0 };		//���ڿ��� �о�� �ӽú���
		fgets(Read_Str, MAX_LEN, fp_tx);				// �ؽ�Ʈ���� ������ �о��
		read_len = strlen(Read_Str);					// ���ڿ� ���̸� ����

		for (int i = 0; i < read_len-1; i += 2)			// ������ ��� ����� �� ���� ( i�� 2���� ����)
			// read_len - 1 �ϴ� ���� : ���ڸ� ������ �ٹٲ޹��ڵ� ���� ���ԵǾ� ������ ���ʹ� ���� ��ȣȭ�Ѵ�.
		{
			decp_c = deCipherChar(Read_Str[i], Read_Str[i + 1]); // upper�� ���ʹ���, lower�� ������ ����
			decp_c ^= cipher_code;						// ��ȣ �ص��ڵ�� ���� ��ȣȭ
			
			// ���
			printf("%c", decp_c);
			fprintf(fout, "%c", decp_c);
		}
	}
}