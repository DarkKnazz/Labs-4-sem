#pragma once
#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
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
#ifdef linux
class Archive {
private:
	pid_t pid;
	int PipeDescript;
	char InMessage[50];
	char OutMessage[50];
	sem_t *sem;
public:
	Archive();
	~Archive();
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
#endif



