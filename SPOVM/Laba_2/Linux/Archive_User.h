#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32 || _WIN64
	#include <windows.h>
	#include <conio.h>
#endif
#ifdef linux
	#include <fcntl.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <semaphore.h>
#endif // linux


using namespace std;

#ifdef _WIN32 || _WIN64
	class Client {

		static int flag;
	private:
		string url;
		string result;
		char wait;
		OVERLAPPED over;
		HANDLE hServerPipe;
		HANDLE hSemaphore;
		HANDLE hThread;
		DWORD dwWritten;
		DWORD dwRead;
		char lpszOutMessage[50];

	public:
		Client();
		~Client();
		char getWait();
		void ConnectPipe();
		static void setFlag(int i);
		static DWORD WINAPI ThreadProc(CONST LPVOID lpParam);
		void createThread();
		bool writeInPipe();
		bool readFromFile();
		void waitServer();
		void waitAnswer();
		void closeHandle();

	};
#endif // _WIN32 || _WIN64
#ifdef linux
	class Client {
		int PipeDescript;
		string url;
		char wait;
		char InMessage[50];
		char OutMessage[50];
		sem_t* sem;
	public:
		Client();
		~Client();
		char getWait();
		void ConnectPipe();
		void writeInPipe();
		void readFromPipe();
		void waitServer();
		void outputResult();
		void initSem();
};
#endif // linux
