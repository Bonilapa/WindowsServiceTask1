#pragma once
#include"MyData.h"
#include"ErrorWrapper.h"
class Server
{
public:
	Server();
	~Server();
	MyData MYDATA, *PMYDATA;
	DWORD WINAPI server(void*);
	DWORD create(void*);
};

