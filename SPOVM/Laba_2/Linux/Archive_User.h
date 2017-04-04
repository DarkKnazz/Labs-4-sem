#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef linux
	#include <fcntl.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <semaphore.h>
#endif // linux


using namespace std;
#ifdef linux
	class ArchiveUser {
		int pipeName;
		string password;
		int line;
		char inputMessage[256];
		char outputMessage[256];
		sem_t* sem;
	public:
		ArchiveUser();
		~ArchiveUser();
		void connection();
		void sendResponse();
		void getCallback();
		void waitForAnswer();
		void outputResult();
		void initSem();
};
#endif
