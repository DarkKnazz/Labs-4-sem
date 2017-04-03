#include "Archive.h"
#ifdef linux
Archive::Archive() {
	sem = sem_open("/semaphore", O_CREAT, 0777, 1);
	sem_post(sem);
}
Archive::~Archive() {
	sem_unlink("/semaphore");
}
bool Archive::createProc() {
	pid = fork();
	if (pid < 0) return false;
	if (pid == 0)
	{
		execl("script.sh", NULL, NULL);
		exit(0);

	}
	return true;
}
bool Archive::createPipe() {
	unlink("/tmp/MyPipe");
	if ((mkfifo("/tmp/MyPipe", 0777)) == -1) {
		cout << "Невозможно создать пайп" << endl;
		return false;
	}

	PipeDescript = open("/tmp/MyPipe", O_RDWR);
	if (PipeDescript < 0)
	{
		cout << "Невозможно открыть файл\n";
		return false;
	}
	return true;
}
void Archive::readData() {
	read(PipeDescript, input, 50);
}
void Archive::writeData() {
	write(PipeDescript, output, 50);
}
void Archive::addRequestToFile() {
	ofstream logOut("log.txt", ios_base::app);
	if (!logOut.is_open()) {
		cerr << "Trables whith writing log file" << endl;
		sleep(1);
		exit(1);
	}
	logOut << InMessage << endl;
	logOut.close();
}
bool Archive::checkRequest() {
	ifstream logIn("log.txt");
	if (!logIn.is_open()) {
		cerr << "Trables whith openning log file" << endl;
		sleep(1);
		return true;
	}
	cout << "open file input" << endl;
	string url;
	while (getline(logIn, url)) {
		if (InMessage == url) {
			strcpy(OutMessage, "Error! File exist");
			return true;
		}
	}
	logIn.close();
	return false;
}
void Archive::downloading() {
	for (int i = 0; i < 100; i++) {
		system("clear");
		cout << "Download file: " << InMessage << endl << i + 1 << "%[";

		for (int j = 0; j < 50; j++) {
			if (j <= i / 2) cout << "=";
			else cout << ".";
		}
		cout << "]" << endl;
		cout << "loading" << endl;
		usleep(100000);
	}
	strcpy(OutMessage, strcat(InMessage, " download success"));
}
void Archive::closeHandle() {
	close(PipeDescript);
}

#endif

