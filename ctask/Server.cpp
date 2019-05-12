#include "stdafx.h"
#include "Server.h"


Server::Server()
{
}


Server::~Server()
{
}


DWORD WINAPI server(void*)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	//char recvbuf[DEFAULT_BUFLEN];
	//int recvbuflen = DEFAULT_BUFLEN;
	MyData recvbuf;
	int recvbuflen = sizeof(recvbuf);

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		ExitThread(1);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		ExitThread(1);
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		ExitThread(1);
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		ExitThread(1);
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		ExitThread(1);
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		ExitThread(1);
	}

	// No longer need server socket
	closesocket(ListenSocket);

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, (char*)&recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			printf("Request to sum %d and %d \n", recvbuf.a, recvbuf.b);
			recvbuf.sum = recvbuf.a + recvbuf.b;
			//TODO iResult check / match!

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, (char*)&recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				ExitThread(1);
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			ExitThread(1);
		}

	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		ExitThread(1);
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	ExitThread(0);
}

DWORD Server::create(void*) {

	TCHAR szMessage[256];
	DWORD dwTemp, i, dwCounter = 0;
	HANDLE hThreads[THREADS_NUMBER];
	CONST HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	ErrorWrapper* ew = new ErrorWrapper();
	if (NULL == hMutex) {
		ew->Error(hStdOut, TEXT((LPCWSTR)"Failed to create mutex.\r\n"));
	}

	for (i = 0; i < THREADS_NUMBER; i++) {
		hThreads[i] = CreateThread(NULL, 0, server, NULL, 0, NULL);
		if (NULL == hThreads[i]) {
			ew->Error(hStdOut, TEXT((LPCWSTR)"Failed to create thread.\r\n"));
		}
	}

	WaitForMultipleObjects(THREADS_NUMBER, hThreads, TRUE, INFINITE);
	wsprintf(szMessage, TEXT("Counter = %d\r\n"), dwCounter);
	WriteConsole(hStdOut, szMessage, lstrlen(szMessage), &dwTemp, NULL);

	for (i = 0; i < THREADS_NUMBER; i++) {
		CloseHandle(hThreads[i]);
	}
	CloseHandle(hMutex);
	ExitProcess(0);
	this->server(NULL);
}