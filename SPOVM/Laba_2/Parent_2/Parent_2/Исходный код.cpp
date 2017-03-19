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
int main(){
	int kol = 0;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	DWORD wait = -1;
	HANDLE sem = CreateSemaphore(NULL, 1, 1, L"Sem1");
	HANDLE Event = CreateEvent(NULL, FALSE, FALSE, L"MyEvent");
	HANDLE Event1 = CreateEvent(NULL, FALSE, FALSE, L"MyEvent1");
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInform;
	cout << "Лабораторная работа №2" << endl;
	cout << "Взаимодействие с архивом нескольких клиентов" << endl;
	_getch();
	system("Cls");
	int n;
	cout << "Введите количество клиентов: " << endl;
	cin >> n;
	for (int i = 0; i < n; i++){
		GetStartupInfo(&startupInfo);
		CreateProcess(
			L"..\\..\\Child_2\\Debug\\Child_2.exe",
			nullptr,
			nullptr,
			nullptr,
			false,
			CREATE_NEW_CONSOLE,
			nullptr,
			nullptr,
			&startupInfo,
			&processInform
			);
	}
	int j;
	for (int k = 0; k < n; k++){
		ResetEvent(Event1);
		HANDLE pipe = CreateNamedPipe(
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
		while (wait != WAIT_OBJECT_0){
			wait = WaitForSingleObject(Event, INFINITE);
		}
		BOOL fConnected = ConnectNamedPipe(pipe, NULL);
		//Разбор строки из дочернего процесса
		unsigned int line;
		string password;
		DWORD  cbRead;
		char   szBuf[256];
		string mas[3];
		ReadFile(pipe, szBuf, 512, &cbRead, NULL);
		fstream fil("E:/file.txt");
		string st;
		while (fil) {
			getline(fil, st);
			kol++;
		}
		fil.close();
		cout << "Количество строк в файле: " << kol << endl;
		j = 0;
		char *buf = strtok(szBuf, " \n");
		//Разделение полученного буфера на строки
		while (j != 3){
			mas[j] = buf;
			buf = strtok(NULL, " \n");
			j++;
		}
		line = atoi(mas[2].c_str());
		cout << "Искомая строка: " << line << endl;
		//Отправление строки дочернему процессу
		int i = 0;
		string str;
		DWORD  cWritten;
		bool check = false;
		string temp = "";
		if (mas[1] == "password"){
			if (line < kol - 1){
				cout << "Все данные верны, чтение из файла" << endl;
				check = true;
			}
			else{
				str = "Выход за границы файла.";
				cout << str;
				WriteFile(pipe, str.c_str(), str.length(),
					&cWritten, NULL);
			}
		}
		else{
			str = "Пароль неверен.";
			cout << str;
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
			cout << str << endl;
			WriteFile(pipe, str.c_str(), str.length(),
				&cWritten, NULL);
		}
		kol = 0;
		fin.close();
		wait = -1;
		SetEvent(Event1);
		ResetEvent(Event);
	}
	_getch();
	return 0;
}