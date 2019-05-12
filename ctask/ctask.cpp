// ctask.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include "Server.h"
#include "Client.h"



int main(int argc, char* argv[])
{

	if (0 == strcmp(argv[1], "--service"))
	{
		printf("nothing here\n");
		/*SERVICE_TABLE_ENTRY DispatchTable[] =
		{
			{ SVCNAME, (LPSERVICE_MAIN_FUNCTION)SvcMain },
		{ NULL, NULL }
		};*/

		// This call returns when the service has stopped. 
		// The process should simply terminate when the call returns.
		//if (!StartServiceCtrlDispatcher(DispatchTable))
		//{
		//	//SvcReportEvent(TEXT("StartServiceCtrlDispatcher"));
		//}
	}
	else if (0 == strcmp(argv[1], "--server"))
	{
		Server* server = new Server();
		server->create(NULL);
	}
	else if (0 == strcmp(argv[1], "--client"))
	{
		Client* client = new Client();
		client->client(argc - 1, argv + 1);
	}
	else
	{
		//TODO error;
		printf("Unknown mode. \n");
	}
	//std::string line, path = "C:\\111\\ServiceIn.txt";

	//std::ifstream in(path); // окрываем файл для чтения
	//if (in.is_open())
	//{
	//	while (getline(in, line))
	//	{
	//		line += ">C:\\111\\ServiceOut.txt";
	//		const char* b = line.c_str();
	//		system(b);
	//	}
	//}
	//in.close();     // закрываем файл

}

