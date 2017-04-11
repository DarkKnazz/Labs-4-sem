#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
using namespace std;

DWORD WINAPI thread2(LPVOID);

class ArchiveUser{
private:
	HANDLE sem;
	HANDLE Event;
	HANDLE Event1;
	HANDLE pipe;
	DWORD wait = -1;
	DWORD actuallyWritten;
	int l;
	string password, itog = "";
	unsigned int line;
public:
	ArchiveUser(){
		sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Sem1");
		Event = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"MyEvent");
		Event1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"MyEvent1");
		HANDLE thread = CreateThread(NULL, 0, thread2, NULL, 0, NULL);
	}
	~ArchiveUser(){

	}
	void waitForServer(){
		ResetEvent(Event1);
		while (wait != WAIT_OBJECT_0)
		{
			cout << "Waiting..." << endl;
			wait = WaitForSingleObject(sem, INFINITE);
			sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Sem1");
		}
	}

	void sendResponse(){
		system("cls");
		cout << "¬ведите пароль дл€ открыти€ архива: " << endl;
		getline(cin, password);
		cout << "¬ведите номер строки, которую нужно прочитать из файла: " << endl;
		cin >> line;

		int len = password.length();
		string temp = to_string(len);
		itog += temp;
		temp = to_string(line);
		itog = itog + " " + password + " " + temp + "\n";
		len = itog.length();
		cout << itog;
		pipe = CreateFile(
			L"\\\\.\\pipe\\$MyPipe$", GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);
		WriteFile(
			pipe,
			itog.c_str(),
			itog.length(),
			&actuallyWritten,
			nullptr
			);
		SetEvent(Event);
	}

	void getCallback(){
		wait = -1;
		while (wait != WAIT_OBJECT_0){
			wait = WaitForSingleObject(Event1, INFINITE);
		}
		ResetEvent(Event1);

		DWORD  cbRead;
		char   szBuf[256];
		ReadFile(pipe, szBuf, 512, &cbRead, NULL);
		for (l = 0; l < cbRead; l++){
			cout << szBuf[l];
		}
		for (l = 0; l < 256; l++){
			szBuf[l] = '0';
		}
		cout << endl;
		system("pause");
		ReleaseSemaphore(sem, 1, NULL);
		_exit(EXIT_SUCCESS);
	}
};

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ArchiveUser arc;
	arc.waitForServer();
	arc.sendResponse();
	arc.getCallback();
}

DWORD WINAPI thread2(LPVOID t)
{
	string name;
	HANDLE EventThread1;
	HANDLE EventThread2;
	HANDLE pipeThread;
	HANDLE semThread;
	DWORD waitThread = -1;
	EventThread1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"MyThread1");
	EventThread2 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"MyThread2");
	semThread = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"SemThread");
	fstream fil("E:/name.txt");
	getline(fil, name);
	fil.close();
	int numberOfClient = atoi(name.c_str());
	numberOfClient = numberOfClient+1;
	string temp = "";
	temp += to_string(numberOfClient);
	ofstream outFile("E:/name.txt");
	outFile.write(temp.c_str(), temp.length());
	outFile.close();
	while (true){
		while (waitThread != WAIT_OBJECT_0)
		{
			waitThread = WaitForSingleObject(semThread, INFINITE); 
			semThread = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"SemThread");
		}
		ofstream fileOut("E:/spisok.txt", ios::trunc);
		fileOut.write(name.c_str(), name.length());
		fileOut.close();
		SetEvent(EventThread1);
		waitThread = -1;
		while (waitThread != WAIT_OBJECT_0)
		{
			waitThread = WaitForSingleObject(EventThread2, INFINITE);
		}
		waitThread = -1;
		ReleaseSemaphore(semThread, 1, NULL);
		Sleep(2000);
	}
	return 0;
}