#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include <Windows.h>

HANDLE initConsoleHandler();							// �ܼ� ���÷��� �Լ� 
void closeConsoleHandler(HANDLE hndlr);					// �ܼ� â �ݱ�
int gotoxy(HANDLE consoleHandler, int x, int y);		// �ܼ�â �̵�

#endif