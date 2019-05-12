#pragma once
class ErrorWrapper
{
public:
	ErrorWrapper();
	~ErrorWrapper();
	VOID Error(CONST HANDLE, CONST LPCWSTR);
};

