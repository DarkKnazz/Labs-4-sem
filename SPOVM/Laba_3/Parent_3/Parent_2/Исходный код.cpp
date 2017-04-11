#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<locale.h>
#include<cstring>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

DWORD WINAPI thread2(LPVOID);

class Archive{
private:
	HANDLE sem;
	HANDLE semThread;
	DWORD wait = -1;
	DWORD waitThread = -1;
	HANDLE Event;
	HANDLE Event1;
	HANDLE pipe;
	HANDLE pipeThread;
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInform;
	unsigned int line;
	string password;
	DWORD  cbRead;
	char   szBuf[256];
	string mas[3];
public:
	Archive(){
		sem = CreateSemaphore(NULL, 1, 1, L"Sem1");
		Event = CreateEvent(NULL, FALSE, FALSE, L"MyEvent");
		Event1 = CreateEvent(NULL, FALSE, FALSE, L"MyEvent1");
		HANDLE thread = CreateThread(NULL, 0, thread2, NULL, 0, NULL);
	}
	~Archive(){
	}
	void getResponse(){
		ReadFile(pipe, szBuf, 512, &cbRead, NULL);
	}
	void createPipe(){
		pipe = CreateNamedPipe(
			L"\\\\.\\pipe\\$MyPipe$",
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | // ??
			PIPE_READMODE_MESSAGE |
			PIPE_WAIT, // ??
			PIPE_UNLIMITED_INSTANCES, // ??
			512, // ??
			512, // ??
			5000, // ??
			nullptr // ??
			);
	}
	void validate(){
		ResetEvent(Event1);
		int kol = 0;
		createPipe();
		while (wait != WAIT_OBJECT_0){
			wait = WaitForSingleObject(Event, INFINITE);
		}
		BOOL fConnected = ConnectNamedPipe(pipe, NULL);
		getResponse();
		//Разбор строки из дочернего процесса
		fstream fil("E:/file.txt");
		string st;
		while (fil) {
			getline(fil, st);
			kol++;
		}
		fil.close();
		int j = 0;
		char *buf = strtok(szBuf, " \n");
		//Разделение полученного буфера на строки
		while (j != 3){
			mas[j] = buf;
			buf = strtok(NULL, " \n");
			j++;
		}
		line = atoi(mas[2].c_str());
		//Отправление строки дочернему процессу
		int i = 0;
		string str;
		DWORD  cWritten;
		bool check = false;
		string temp = "";
		if (mas[1] == "password"){
			if (line < kol - 1){
				check = true;
			}
			else{
				str = "Выход за границы файла.";
				WriteFile(pipe, str.c_str(), str.length(),
					&cWritten, NULL);
			}
		}
		else{
			str = "Пароль неверен.";
			WriteFile(pipe, str.c_str(), str.length(),
				&cWritten, NULL);
		}
		fstream fin("E:/file.txt");
		i = 0;
		if (check == true){
			string str;
			while (fin) {
				getline(fin, temp);
				i++;
				if (i == line)
					break;
			}
			str = "";
			str += "Строка из файла " + to_string(line) + "\n";
			str += temp;
			WriteFile(pipe, str.c_str(), str.length(),
				&cWritten, NULL);
		}
		kol = 0;
		fin.close();
		wait = -1;
		SetEvent(Event1);
		ResetEvent(Event);
	}
};

int main(){
	int kol = 0;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Archive archive;
	cout << "Лабораторная работа №2" << endl;
	cout << "Взаимодействие с архивом нескольких клиентов" << endl;
	_getch();
	system("cls");
	for (;;){
		archive.validate();
	}
	_getch();
	return 0;
}

DWORD WINAPI thread2(LPVOID t)
{
	HANDLE EventThread1;
	HANDLE semThread;
	HANDLE pipeThread;
	HANDLE EventThread2;
	DWORD waitThread = -1;
	semThread = CreateSemaphore(NULL, 1, 1, L"SemThread");
	EventThread1 = CreateEvent(NULL, FALSE, FALSE, L"MyThread1");
	EventThread2 = CreateEvent(NULL, FALSE, FALSE, L"MyThread2");
	ResetEvent(EventThread1);
	ResetEvent(EventThread2);
	ofstream fil("E:/name.txt", ios::trunc);
	string name = "1";
	string read = "";
	fil.write(name.c_str(), name.length());
	fil.close();
	while (1){
		ResetEvent(EventThread1);
		ResetEvent(EventThread2);
		waitThread = -1;
		while (waitThread != WAIT_OBJECT_0){
			waitThread = WaitForSingleObject(EventThread1, INFINITE);
		}
		fstream fileName("E:/spisok.txt");
		string stSpis = "";
		getline(fileName, stSpis);
		cout << "Project name which in list: "<< stSpis << endl;
		fileName.close();
		SetEvent(EventThread2);
	}
}