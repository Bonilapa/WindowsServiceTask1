// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <strsafe.h>
#include <iostream>
#include "ErrorWrapper.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define WIN32_LEAN_AND_MEAN
#define THREADS_NUMBER 10
#define ITERATIONS_NUMBER 100
#define PAUSE 10 /* ms */
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define SVCNAME (char*)"AAA_Innopolis"
