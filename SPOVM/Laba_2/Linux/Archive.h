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
	#include <sstream>
#endif


using namespace std;
#ifdef linux
class Archive {
private:
	pid_t pid;
	int pipeName;
	char response[256];
	char callback[256];
	char err1[256] = "Invalid password!\n\n";
	char err2[256] = "Out of file!\n\n";
	string mas[3];
	string password;
	int lineFile;
	int line;
	int len;
	sem_t *sem;
public:
	Archive();
	~Archive();
	bool createProc();
	bool createPipe();
	void getResponse();
	void sendCallback();
	void validate();
	void closeHandle();
};
#endif



