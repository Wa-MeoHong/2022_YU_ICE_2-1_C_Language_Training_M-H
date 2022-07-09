/*
  파일명 : "실습4_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 키보드의 키에 주파수를 매핑해서 간단한 전자피아노를 만들어본다.

  프로그램 작성자 : 신대홍(2022년 3월 25일)
  최종 Update : Version 3.0.0, 2022년 3월 25일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
   신대홍		 2022/03/23		v1.0.0		  최초작성
   신대홍		 2022/03/23		v2.0.0		  2옥타브~8옥타브#까지 구현완료
   신대홍		 2022/03/25		v3.0.0		  1옥타브까지 전부 구현완료
===========================================================================================================
*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

#define ESC 0x1B										// ESC (27)

int key_to_freq(char key, char alt_on);
void print_sentence(void);

int main(void)
{
	char key, alt_on = 0;
	int duration = 80;									// 80ms
	int freq = 0;

	print_sentence();									//글자출력.. 

	while ((key = _getch()) != ESC) 
	// getch()의 특성 : 입력 버퍼가 없으므로 값이 바로 변수에 저장됨. 그러므로 엔터키나 탭키같은것도 입력 가능
	{
		alt_on = 0;
		if (GetAsyncKeyState(VK_MENU) & 0x8000)			// 지금 ALT키가 눌려져 있는가? 
			alt_on = 1;
		freq = key_to_freq(key, alt_on);
		if (freq != -1)									// 잘못눌린키가 아닐시
		{
			printf("input key (%c) : freq (%3d)\n", key, freq);
			Beep(freq, duration);						// 주파수에 맞는 음을 소리낸다. (주파수가 완전 동일하진 않음)
		}
		else
		{
			printf("input key (%c) is wrong key input..\n", key); 
			// 잘못된 키를 입력했다고 하고 소리도 안남
		}
	}

	return 0;
}

void print_sentence(void)								// 문장 출력 함수
{
	printf("\tsimple E-Piano\n");
	printf("‘!’~ ‘&’ : octave 8 도 레 미 파 솔 라 시,\n");
	printf("‘Q’~ ‘U’ : octave 7 도 레 미 파 솔 라 시,\n");
	printf("‘A’~ ‘J’ : octave 6 도 레 미 파 솔 라 시,\n");
	printf("‘Z’~ ‘M’ : octave 5 도 레 미 파 솔 라 시,\n");
	printf("‘1’~ ‘7’ : octave 4 도 레 미 파 솔 라 시,\n");
	printf("‘q’~ ‘u’ : octave 3 도 레 미 파 솔 라 시,\n");
	printf("‘a’~ ‘j’ : octave 2 도 레 미 파 솔 라 시,\n");
	printf("‘z’~ ‘m’ : octave 1 도 레 미 파 솔 라 시 \n\n");
	printf("input keyboard keys (ESC = quit) : \n");
}

int key_to_freq(char key, char alt_on)
{
	int freq = 0;
	int shift_on = -1;
	int Key_to_eng[2][2][26] =
	{
	   { // alt 안누름
			{ 65, 49, 41, 82, 165, 87, 98, 110, -1, 123, -1, -1, 62,
			55, -1, -1, 131, 175, 73, 196, 247, 44, 147, 37, 220, 33},				// a ~ z 까지 입력 (옥타브 3 ~ 1)
			{ 1047, 784, 659, 1319, 2637, 1397, 1568, 1760, -1, 1976, -1, -1, 988,
			880, -1, -1, 2093, 2794, 1175, 3136, 3951, 699, 2349, 587, 3520, 523}	// A ~ Z 까지 입력 (옥타브 7 ~ 5)
	   },
	   { // alt 누름 
			{ 69, 52, -1, -1, -1, 93, 104, 117, -1, -1, -1, -1, -1,
			58, -1, -1, 139, 185, 78, 208, -1, 46, 156, 39, 233, 35},				// a ~ z 까지 (옥타브 3# ~ 1#)
			{ 1109, 831, -1, -1, -1, 1480, 1661, 1865, -1, -1, -1, -1, -1,
			932, -1, -1, 2217, 2960, 1245, 3322, -1, 740, 2489, 622, 3729, 554}		// A ~ Z 까지 입력 (옥타브 7# ~ 5#)
	   }
	};
	int Key_to_num[2][10] =
	{
		{ -1, 262, 294, 311, 349, 392, 440, 494, -1, -1 },						// 0 ~ 9 까지 (옥타브 4), alt 안누름
		{ -1, 277, 311, -1, 367, 415, 466, -1, -1, -1 },						// 0 ~ 9 까지 (옥타브 4#), alt 누름
	};
	if (key >= 'A' && key <= 'Z')				//대문자 입력시
	{
		shift_on = 1;
		freq = Key_to_eng[alt_on][shift_on][key - 65];
	}
	else if (key >= 'a' && key <= 'z')			//소문자 입력시
	{
		shift_on = 0;
		freq = Key_to_eng[alt_on][shift_on][key - 97];
	}
	else if (key >= '0' && key <= '9')			//숫자키 입력시
	{
		freq = Key_to_num[alt_on][key - 48];
	}
	else
	{
		switch (key)							//옥타브 8 (숫자 + shift)
		{
		case '!':
		{	if (alt_on == 1) { freq = 4435; }
		else freq = 4186;
		break; }
		case '@':
		{	if (alt_on == 1) { freq = 4978; }
		else freq = 4699;
		break; }
		case '#':
		{	if (alt_on == 1) { freq = -1; }
		else freq = 5274;
		break; }
		case '$':
		{	if (alt_on == 1) { freq = 5920; }
		else freq = 5588;
		break; }
		case '%':
		{	if (alt_on == 1) { freq = 6645; }
		else freq = 6272;
		break; }
		case '^':
		{	if (alt_on == 1) { freq = 7459; }
		else freq = 7040;
		break; }
		case '&':
		{	if (alt_on == 1) { freq = -1; }
		else freq = 7902;
		break; }
		default:
		{	freq = -1;							// 위의 모든 해당사항이 아니면 
		break; }
		}
	}
	return freq;
}