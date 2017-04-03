#pragma once
#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
#ifdef _WIN32 || _WIN64
	#include <string>
	#include <cstdio>
	#include <cstdlib>
	#include <conio.h>
	#include <iomanip>
	#include <sstream>
	#include <limits>
	#include <windows.h>
	#include <tchar.h>
#endif // _WIN32 || _WIN64
#ifdef linux
	#include <unistd.h>
	#include <cstdlib>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <signal.h>
	#include <semaphore.h> 
	#include <errno.h>
#endif


using namespace std;
#ifdef _WIN32 || _WIN64
class Server
{
	HANDLE* hPipes;
	HANDLE hSemaphore;
	char lpszInMessage[50];
	DWORD dwBytesRead;
	char  lpszOutMessage[50];
	DWORD dwBytesWrite;
	int N;
public:
	Server(int amount);
	~Server();
	bool checkURI(char* buf);
	bool createProc();
	bool createPipe(HANDLE& hPipe);
	bool connectPipe(HANDLE& hPipe);
	bool readFromPipe(HANDLE& hPipe);
	bool writeToPipe(HANDLE& hPipe);
	bool checkRequest();
	void addRequestToFile();
	void downloading();
	void closeHandle(HANDLE& hPipe);
	HANDLE& getPipe(int index);
	bool checking();
	HANDLE& getSemaphore();
};
#endif
#ifdef linux
class Server {
private:
	pid_t pid;
	int PipeDescript;
	char InMessage[50];
	char OutMessage[50];
	sem_t *sem;
public:
	Server();
	~Server();
	bool createProc();
	bool createPipe();
	void readFromPipe();
	void writeToPipe();
	bool checkURI(char *buf);
	bool checking();
	bool checkRequest();
	void addRequestToFile();
	void downloading();
	void closeHandle();

};
#endif // linux



