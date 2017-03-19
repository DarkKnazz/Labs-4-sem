#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
using namespace std;

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int l;
	HANDLE sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Sem1");
	HANDLE Event = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"MyEvent");
	HANDLE Event1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"MyEvent1");
	ResetEvent(Event1);
	DWORD wait = -1;
	while (wait != WAIT_OBJECT_0)
	{
		wait = WaitForSingleObject(sem, INFINITE);
		sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Sem1");
	}
	string password, itog = "";
	unsigned int line;
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
	HANDLE pipe = CreateFile(
		L"\\\\.\\pipe\\$MyPipe$", GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);
	DWORD actuallyWritten;
	WriteFile(
		pipe,
		itog.c_str(),
		itog.length(),
		&actuallyWritten,
		nullptr
		);
	SetEvent(Event);
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