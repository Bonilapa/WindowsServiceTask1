#include "stdafx.h"
#include "ErrorWrapper.h"


ErrorWrapper::ErrorWrapper()
{
}


ErrorWrapper::~ErrorWrapper()
{
}

VOID ErrorWrapper::Error(CONST HANDLE hStdOut, CONST LPCWSTR szMessage) {
	DWORD dwTemp;
	TCHAR szError[256];
	WriteConsole(hStdOut, szMessage, lstrlen((LPCSTR)(char*)szMessage), &dwTemp, NULL);
	wsprintf(szError, TEXT("LastError = %d\r\n"), GetLastError());
	WriteConsole(hStdOut, szError, lstrlen(szError), &dwTemp, NULL);
	ExitProcess(0);
}