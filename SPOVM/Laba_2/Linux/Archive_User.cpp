#include "Archive_User.h"
#ifdef linux
	ArchiveUser::ArchiveUser(){

	}

	ArchiveUser::~ArchiveUser(){

	}
	void ArchiveUser::connection() {
		pipeName = open("/tmp/MyPipe", O_RDWR);
		if (pipeName < 0)
		{
			cout << "Invalid connection!\n";
			exit(1);
		}
	}
	void ArchiveUser::getCallback() {
		read(pipeName, inputMessage, 256);
	}
	void ArchiveUser::sendResponse() {
		write(pipeName, outputMessage, password.length());
	}
	void ArchiveUser::waitForAnswer() {
		cout << "Wait" << endl;
		sem_wait(sem);
		system("clear");
		cout << "Enter password: " << endl;
		getline(cin, password);
		cout << "Enter line: " << endl;
		cin >> line;
		stringstream ch;
		ch << line;
		stringstream ch1;
		ch1 << password.length();
		password = ch1.str() + "\n" + password + "\n" + ch.str() + "\n";
		cout << password;
		strcpy(outputMessage, password.c_str());
	}
	void ArchiveUser::outputResult() {
		cout << "Result: ";
		int tabs = 0;
		for(int i = 0; i < strlen(inputMessage); i++){
			if(inputMessage[i] == '\n')
				tabs++;
			if(tabs == 2)
				break;
			cout << inputMessage[i];
		}
		cout << endl;
		close(pipeName);
		sleep(3);
		sem_post(sem);
	}
	void ArchiveUser::initSem() {
		sem = sem_open("/semaphore", 0, 0777, 1);
		if (sem == SEM_FAILED)
		{
			cout << "Invalid semaphore" << endl;
			sleep(2);
			exit(0);
		}
	}
#endif

