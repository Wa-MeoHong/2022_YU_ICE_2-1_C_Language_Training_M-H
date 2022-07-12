#include <stdio.h>
#include "ConsoleDisplay.h"

HANDLE consoleHandler;

HANDLE initConsoleHandler()									// �ܼ� �ʱⰪ ����
{
	HANDLE stdCnslHndlr;
	stdCnslHndlr = GetStdHandle(STD_OUTPUT_HANDLE);  
	consoleHandler = stdCnslHndlr;
	return consoleHandler; 
}

void closeConsoleHandler(HANDLE hndlr)						// �ܼ� �ڵ鷯 �ݱ�
{
	CloseHandle(hndlr);
}

int gotoxy(HANDLE consHndlr, int x, int y)					// �ܼ� â ��ġ �����ϴ� �Լ�
{
	if (consHndlr == INVALID_HANDLE_VALUE)
		return 0;
	COORD coords = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(consHndlr, coords);
}