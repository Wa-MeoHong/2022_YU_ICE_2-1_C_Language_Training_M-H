
/*
  파일명 : "실습2-2_21912193_신대홍"

  프로그램의 목적 및 기본 기능:
	- imit.h를 이용해서 자료형의 최대,최소값을 불러온 후, 그 값들과, +-1을 한 값들을 출력하여
	오버플로가 일어나는지 확인 한 후, 설명

  프로그램 작성자 : 신대홍(2022년 3월 9일)
  최종 Update : Version 1.0.0, 2022년 3월 9일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
   신대홍		 2022/03/09		v1.0.0		  최초작성

===========================================================================================================
*/


#include <limits.h>
#include <stdio.h>

int main(void)
{
	char char_max = CHAR_MAX, char_min = CHAR_MIN;
	short short_max = SHRT_MAX, short_min = SHRT_MIN;
	int int_max = INT_MAX, int_min = INT_MIN;

	printf("char_max = %d\n ", char_max);
	printf("char_min = %d\n ", char_min);
	printf("char_max (%d) + 1 = %d\n ", char_max, char_max + 1);
	printf("char_min (%d) - 1 = %d\n ", char_min, char_min - 1);

	printf("short_max = %d\n ", short_max);
	printf("short_min = %d\n ", short_min);
	printf("short_max (%d) + 1 = %d\n ", short_max, short_max + 1);
	printf("short_min (%d) - 1 = %d\n ", short_min, short_min - 1);

	printf("int_max = %d\n ", int_max);
	printf("int_min = %d\n ", int_min);
	printf("int_max (%d) + 1 = %d\n ", int_max, int_max + 1);
	printf("int_min (%d) - 1 = %d\n ", int_min, int_min - 1);
	return 0;
}