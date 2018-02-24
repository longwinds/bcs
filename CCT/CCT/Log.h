#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <netinet/in.h>      /* sockaddr_in{} and other Internet defns */


class CLog
{
public:
	CLog(void);
	~CLog(void);
};
