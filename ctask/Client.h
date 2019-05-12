#pragma once
#include"MyData.h"
class Client
{
public:
	MyData MYDATA, *PMYDATA;
	Client();
	~Client();
	int __cdecl client(int argc, char **argv);
};

