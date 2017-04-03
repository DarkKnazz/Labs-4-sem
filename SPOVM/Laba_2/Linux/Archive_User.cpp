#include "Client.h"
#ifdef _WIN32 || _WIN64
	int Client::flag = 0;
	Client::Client() {
		over = { 0 };
		over.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		hServerPipe = INVALID_HANDLE_VALUE;
		hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("semaphore"));
		setFlag(0);
	}
	void Client::ConnectPipe() {
		while (INVALID_HANDLE_VALUE == hServerPipe) {
			WaitNamedPipe(TEXT("\\\\.\\pipe\\MyReadPipe"), NMPWAIT_WAIT_FOREVER);

			hServerPipe = CreateFile(
				TEXT("\\\\.\\pipe\\MyReadPipe"), // имя канала
				GENERIC_WRITE | GENERIC_READ, // читаем и записываем в канал
				FILE_SHARE_WRITE | FILE_SHARE_READ, // разрешаем чтение и запись в канал
				(LPSECURITY_ATTRIBUTES)NULL, // защита по умолчанию
				OPEN_EXISTING, // открываем существующий канал
				0, // атрибуты по умолчанию
				(HANDLE)NULL // дополнительных атрибутов нет
			);
		}
	}
	void Client::setFlag(int flag) {
		Client::flag = flag;
	}
	DWORD WINAPI Client::ThreadProc(CONST LPVOID lpParam) {
		while (!flag) {
			system("CLS");
			cout << "Wait" << endl;
			if (_kbhit()) cout << "Error! Wait when server " << endl;
			while (_kbhit()) _getch();
			Sleep(1000);
		}
		ExitThread(0);
	}
	void Client::createThread() {
		hThread = CreateThread(NULL, 0, &ThreadProc, NULL, 0, NULL);
		if (NULL == hThread) {
			cout << "Error create Thread" << endl;
		}
	}
	bool Client::writeInPipe() {
		if (!WriteFile(hServerPipe, url.c_str(), url.size(), &dwWritten, &over))
		{
			cout << "writing in pipe is failed" << endl;
			CloseHandle(hServerPipe);
			return false;
		}
		return true;
	}
	bool Client::readFromFile() {
		if (!ReadFile(hServerPipe, lpszOutMessage, sizeof(lpszOutMessage), &dwRead, NULL))
		{
			cout << "reading from pipe failed" << endl;
			CloseHandle(hServerPipe);
			fflush(stdin);
			_getch();
			return false;
		}
		return true;
	}
	void Client::waitServer() {
		WaitForSingleObject(hSemaphore, INFINITE);
		setFlag(1);
		cout << "Enter your URL-address" << endl;
		cin >> url;

		cout << "You want wait downloding? Y/N" << endl;
		cin >> wait;
	}
	void Client::waitAnswer() {
		WaitForSingleObject(hServerPipe, INFINITE);
		ReleaseSemaphore(hSemaphore, 1, NULL);
		cout << "Result: " << lpszOutMessage << endl;
	}
	void Client::closeHandle() {
		CloseHandle(hServerPipe);
		CloseHandle(hSemaphore);
	}
#endif // _WIN32 || _WIN64
	Client::~Client() {

	}
	char Client::getWait() {
		return wait;
	}
#ifdef linux
	Client::Client() {

	}
	void Client::ConnectPipe() {
		PipeDescript = open("/tmp/MyPipe", O_RDWR);
		if (PipeDescript < 0)
		{
			cout << "Cannot open file\n";
			exit(1);
		}
	}
	void Client::readFromPipe() {
		read(PipeDescript, InMessage, 50);
	}
	void Client::writeInPipe() {
		write(PipeDescript, OutMessage, url.size() + 1);
	}
	void Client::waitServer() {
		cout << "Wait" << endl;
		sem_wait(sem);
		system("clear");
		cout << "Put your URL-address" << endl;
		cin >> url;
		cout << "Do you want to wait?(Y/N)" << endl;
		cin >> wait;

		int i = url.size();
		strcpy(OutMessage, url.c_str());
		OutMessage[i + 1] = '\n';
	}
	void Client::outputResult() {
		cout << "Result: " << InMessage << endl;
		sleep(5);
		sem_post(sem);
		close(PipeDescript);
	}
	void Client::initSem() {
		sem = sem_open("/semophore", 0, 0777, 1);
		if (sem == SEM_FAILED)
		{
			cout << "Error with semophore" << endl;
			sleep(2);
			exit(0);
		}
	}
#endif // linux

