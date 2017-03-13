#pragma once

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<locale.h>
#include<cstring>
#include<string>
#include<iostream>
#endif
#ifdef linux
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
#endif
using namespace std;

class ArchiveUser
{
private:
	string password;
	int l;
	string itog;
	int len;

	LPWSTR pipeName;
	HANDLE pipe;

	LPWSTR appPath;
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInform;

public:
	explicit ArchiveUser(LPWSTR pipe_name, LPWSTR app_path)
		: pipeName(pipe_name), pipe(nullptr), appPath(app_path) {
		GetStartupInfo(&startupInfo);
		pipe = CreateNamedPipe(
			pipe_name,
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

	void formQuery(const string& pass, unsigned line) {
		password = pass;
		l = line;
		int len = password.length();
		string temp = to_string(len);
		itog += temp;
		temp = to_string(l);
		itog = itog + " " + password + " " + temp + "\n";
		len = itog.length();
		cout << itog;
	}

	void sendQuery() {
		CreateProcess(
			appPath,
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
		BOOL fConnected = ConnectNamedPipe(pipe, NULL);
		DWORD actuallyWritten;
		DWORD wait = -1;

		WriteFile(
			pipe,
			itog.c_str(),
			itog.length(),
			&actuallyWritten,
			nullptr
			);

		while (wait != WAIT_OBJECT_0){
			system("cls");
			cout << "Ожидается возвращение значения из дочернего процесса..." << endl;
			wait = WaitForSingleObject(processInform.hProcess, INFINITE);
		}

		system("cls");
		DWORD  cWritten;
		char   sBuf[256];
		ReadFile(pipe, sBuf, 512, &cWritten, NULL);
		len = cWritten;
		itog = sBuf;
	}
	void print(){
		cout << "Возвращено значение из дочернего процесса: " << endl;
		for (int i = 0; i < len; i++){
			cout << itog[i];
		}
		cout << endl;
	}
};
