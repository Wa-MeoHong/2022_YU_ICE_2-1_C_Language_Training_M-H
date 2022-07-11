#include "CipherMsg.h"

unsigned char xtoa(unsigned char uc)						// 16진수를 문자로 바꿔준다.
{
	unsigned char Ch;

	if (uc >= 0 && uc <= 9)
		Ch = 48 + uc;								// 0 = 0x30 ~ 9 = 0x39
	else if (uc >= 10 && uc <= 15)
		Ch = 65 + uc - 10;							// A = 0x41 ~ F = 0x46 
	return Ch;
}

unsigned int atox(unsigned char uc)							 // 문자를 16진수형태의 정수로 변환해주는 함수
{
	unsigned int hexVal = 0;

	if (uc >= '0' && uc <= '9')						// 0 ~ 9까지 아스키문자일땐
		hexVal = uc - '0';							// uc(아스키문자) - 0x30
	else if (uc >= 'A' && uc <= 'F')				// A ~ F (10 ~ 15)까지 일땐
		hexVal = uc - 'A' + 10;						// uc(아스키문자) - 65 + (10) 
	else if (uc >= 'a' && uc <= 'f')				// a ~ f (소문자, 10 ~ 15는 동일)
		hexVal = uc - 'a' + 10;						// uc(아스키문자) - 97 + (10)

	return hexVal;
}

void CipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l) // 한 문자를 상위비트, 하위비트로 쪼개는 함수
{
	char i = 0;

	i = ch >> 4;						// 상위비트 (위의 4비트를 오른쪽으로 민다)
	*pCC_u = xtoa(i);

	i = ch & 0x0F;						// 0000 1111 (하위비트만 골라내기)
	*pCC_l = xtoa(i);
}

void CipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code) // 텍스트를 암호화하기
{
	unsigned char read_c = 0;							// 암호화한 문자를 담는 변수
	unsigned char upper = 0;							// read_c 상위 4비트 글자
	unsigned char lower = 0;							// read_c 하위 4비트 글자
	int read_len = 0;									// 읽어온 문자열의 길이
	int read_lines = 1;

	while (!(feof(fp_msg)))
	{
		unsigned char Read_Str[MAX_LEN] = { 0 };		// 문자열을 읽어올 임시변수
		fgets(Read_Str, MAX_LEN, fp_msg);				// 텍스트파일 한줄을 읽어옴
		read_len = strlen(Read_Str);					// 문자열 길이를 구함

		printf("(%2d-th Input String, length %d) : ", read_lines, read_len); printf("%s", Read_Str);
		// 읽은 문자열 출력

		for (int i = 0; i < read_len; i++)				// 한줄을 모두 출력할 때 까지
		{
			read_c = Read_Str[i] ^ cipher_code;			// Read_Str 문자열중 한 글자와 암호해독 코드를 XOR
			CipherChar(read_c, &upper, &lower);			// 그 XOR한 문자를 상위비트, 하위비트로 쪼개서 문자로 표현
			fprintf(fp_tx, "%c%c", upper, lower);		// 파일 출력
		}
		fprintf(fp_tx, "\n");							// 파일 한칸 엔터
		read_lines++;
	}
}

unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l)		// 상/하위 비트로 쪼개진 문자 합치기
{
	unsigned int upper = 0;
	unsigned int lower = 0;

	upper = atox(rc_u); lower = atox(rc_l);				// 문자로 바뀐 상/하위 바이트들을 정수로 교체

	return (upper << 4) | lower;
}

void DecipherText(FILE* fp_tx, FILE* fout, unsigned char cipher_code)	// 텍스트 복호화하기
{
	unsigned char decp_c = 0;							// 복호화한 문자를 담는 변수
	int read_len = 0;									// 읽어온 문자열의 길이


	printf("\nReceived and Deciphered Message : \n");
	while (!(feof(fp_tx)))
	{
		unsigned char Read_Str[MAX_LEN] = { 0 };		//문자열을 읽어올 임시변수
		fgets(Read_Str, MAX_LEN, fp_tx);				// 텍스트파일 한줄을 읽어옴
		read_len = strlen(Read_Str);					// 문자열 길이를 구함

		for (int i = 0; i < read_len-1; i += 2)			// 한줄을 모두 출력할 때 까지 ( i는 2개씩 증가)
			// read_len - 1 하는 이유 : 문자를 읽을때 줄바꿈문자도 같이 들어가게되어 마지막 엔터는 빼고 암호화한다.
		{
			decp_c = deCipherChar(Read_Str[i], Read_Str[i + 1]); // upper는 왼쪽문자, lower는 오른쪽 문자
			decp_c ^= cipher_code;						// 암호 해독코드로 문자 복호화
			
			// 출력
			printf("%c", decp_c);
			fprintf(fout, "%c", decp_c);
		}
	}
}