#include <stdio.h>
#include "ConsoleDisplay.h"

HANDLE consoleHandler;

HANDLE initConsoleHandler()						// 콘솔 초기값 설정
{
	HANDLE stdCnslHndlr;
	stdCnslHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleHandler = stdCnslHndlr;
	return consoleHandler;
}

void closeConsoleHandler(HANDLE hndlr)			// 콘솔 핸들러 닫기
{
	CloseHandle(hndlr);
}

int gotoxy(HANDLE consHndlr, int x, int y)		// 콘솔 창 위치 변경하는 함수
{
	if (consHndlr == INVALID_HANDLE_VALUE)
		return 0;
	COORD coords = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(consHndlr, coords);
}