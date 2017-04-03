#include "Proc.h"
#ifdef _WIN32 || _WIN64

Server::Server(int amount) {
	hSemaphore = CreateSemaphore(NULL, 1, 1, TEXT("semaphore"));
	hPipes = new HANDLE[amount];
}
Server::~Server() {
	delete[] hPipes;
}
bool Server::createProc() {
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	// создаем новый консольный процесс

	if (!CreateProcess(TEXT("C:\\VSProjects\\laba1\\childProc\\Debug\\childProc.exe"), NULL, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
		return false;
	return true;
}
bool Server::createPipe(HANDLE& hPipe) {
	hPipe = CreateNamedPipe(
		TEXT("\\\\.\\pipe\\MyReadPipe"),
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,//клиент пишет, сервер читает; асинхронный режим
		PIPE_TYPE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		0,
		0,
		INFINITE,
		NULL
	);
	if (hPipe == INVALID_HANDLE_VALUE) return false;
	return true;
}
bool Server::connectPipe(HANDLE& hPipe) {
	if (!ConnectNamedPipe(
		hPipe,
		NULL
	)) return false;
	return true;
}
bool Server::readFromPipe(HANDLE& hPipe) {
	if (!ReadFile(
		hPipe, // дескриптор канала
		lpszInMessage, // адрес буфера для ввода данных
		sizeof(lpszInMessage), // число читаемых байтов
		&dwBytesRead, // число прочитанных байтов
		(LPOVERLAPPED)NULL // передача данных синхронная
	)) return false;
	lpszInMessage[dwBytesRead] = '\0';
	return true;
}
bool Server::writeToPipe(HANDLE& hPipe) {
	if (!WriteFile(
		hPipe, // дескриптор канала
		lpszOutMessage, // адрес буфера для вывода данных
		sizeof(lpszOutMessage), // число записываемых байтов
		&dwBytesWrite, // число записанных байтов
		(LPOVERLAPPED)NULL // передача данных синхронная
	)) return false;
	return true;
}
bool Server::checkRequest() {
	ifstream logIn("log.txt");
	if (!logIn.is_open()) {
		cerr << "Trables whith openning log file" << endl;
		_getch();
		exit(1);
	}
	string url;
	while (getline(logIn, url)) {
		if (lpszInMessage == url) {
			strcpy(lpszOutMessage, "Error! File exist");
			return true;
		}
	}
	logIn.close();
	return false;
}
void Server::addRequestToFile() {
	ofstream logOut("log.txt", ios_base::app);
	if (!logOut.is_open()) {
		cerr << "Trables whith writing log file" << endl;
		_getch();
		exit(1);
	}
	logOut << lpszInMessage << endl;
	logOut.close();
}
HANDLE& Server::getPipe(int index) {
	return hPipes[index];
}
bool Server::checking() {
	if (!checkURI(lpszInMessage)) {
		strcpy(lpszOutMessage, "Error! URI entered incorrectly");
		system("CLS");
		cout << "Incorrectly link" << endl;
		return false;
	}
	return true;
}
void Server::downloading() {
	for (int i = 0; i < 100; i++) {
		system("CLS");
		cout << "Download file: " << lpszInMessage << endl;
		cout << setw(3) << i + 1 << "%[";
		for (int j = 0; j < 50; j++) {
			if (j <= i / 2) cout << "=";
			else cout << ".";
		}
		cout << "]" << endl;
		cout << "loading" << endl;
		Sleep(100);
	}
	strcpy(lpszOutMessage, strcat(lpszInMessage, " download success"));
}
bool Server::checkURI(char* buf) {
	int i = 0;
	for (; i < 3; i++) {
		if (buf[i] != 'w') return false;
	}
	if (buf[i] != '.') return false;
	return true;
}
void Server::closeHandle(HANDLE& hPipe) {
	CloseHandle(hPipe);
}
HANDLE& Server::getSemaphore() {
	return hSemaphore;
}
#endif // _WIN32 || _WIN64
#ifdef linux
Server::Server() {
	sem = sem_open("/semophore", O_CREAT, 0777, 1);
	sem_post(sem);
}
Server::~Server() {
	sem_unlink("/semophore");
}
bool Server::createProc() {
	pid = fork();
	if (pid < 0) return false;
	if (pid == 0)
	{
		execl("script.sh", NULL, NULL);
		exit(0);

	}
	return true;
}
bool Server::createPipe() {
	unlink("/tmp/MyPipe");
	if ((mkfifo("/tmp/MyPipe", 0777)) == -1) {
		cout << "Cannot create file" << endl;
		return false;
	}

	PipeDescript = open("/tmp/MyPipe", O_RDWR);
	if (PipeDescript < 0)
	{
		cout << "Cannot open file\n";
		return false;
	}
	return true;
}
void Server::readFromPipe() {
	read(PipeDescript, InMessage, 50);
}
void Server::writeToPipe() {
	write(PipeDescript, OutMessage, 50);
}
bool Server::checkURI(char *buf) {
	cout << "cheking" << endl;
	int i = 0;
	for (; i < 3; i++) {
		if (buf[i] != 'w') return false;
	}
	if (buf[i] != '.') return false;
	return true;
}
bool Server::checking() {
	if (!checkURI(InMessage)) {
		strcpy(OutMessage, "Error! URI entered incorrectly");
		system("clear");
		cout << "Incorrectly link" << endl;
		return false;
	}
	return true;
}
void Server::addRequestToFile() {
	ofstream logOut("log.txt", ios_base::app);
	if (!logOut.is_open()) {
		cerr << "Trables whith writing log file" << endl;
		sleep(1);
		exit(1);
	}
	logOut << InMessage << endl;
	logOut.close();
}
bool Server::checkRequest() {
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
void Server::downloading() {
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
void Server::closeHandle() {
	close(PipeDescript);
}

#endif // linux

