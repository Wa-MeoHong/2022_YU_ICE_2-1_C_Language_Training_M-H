#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include <Windows.h>

HANDLE initConsoleHandler();							// 콘솔 디스플레이 함수 
void closeConsoleHandler(HANDLE hndlr);					// 콘솔 창 닫기
int gotoxy(HANDLE consoleHandler, int x, int y);		// 콘솔창 이동

#endif