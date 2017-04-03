#include "Archive_User.h"
#ifdef linux
	void ArchiveUser::connection() {
		pipeName = open("/tmp/MyPipe", O_RDWR);
		if (pipeName < 0)
		{
			cout << "Invalid connection!\n";
			exit(1);
		}
	}
	void ArchiveUser::getCallback() {
		read(pipeName, InMessage, 50);
	}
	void ArchiveUser::sendResponse() {
		write(pipeName, OutMessage, url.size() + 1);
	}
	void ArchiveUser::waitForAnswer() {
		cout << "Wait" << endl;
		sem_wait(sem);
		system("clear");
		cout << "Put your URL-address" << endl;
		cin >> url;

		int i = url.size();
		strcpy(OutMessage, url.c_str());
		OutMessage[i + 1] = '\n';
	}
	void ArchiveUser::outputResult() {
		cout << "Result: " << InMessage << endl;
		sleep(5);
		sem_post(sem);
		close(pipeName);
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

