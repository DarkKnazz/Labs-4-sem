#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include<iostream>
#include<conio.h>
#include<fstream>
#include<process.h>
#include<string>
#include<stdio.h>
#include<locale.h>
#include<cstring>
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

class Process_Work{
public:
	void start(){
		#ifdef WIN32
		setlocale(LC_ALL, "Russian");
		cout << "Лабораторная работа 1" << endl;
		cout << "Организация работы человека и архивной системы" << endl;
		cout << "Передается запрос на возврат строки из файла" << endl;
		cout << "При несовпадении строки или пароля от архива возвратит ошибку" << endl;
		_getch();
		system("cls");
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		GetStartupInfo(&si);
		HANDLE hNamedPipe;
		int lbl;
		char   szBuf[256] = "Hello suka!\n";
		string password;
		int kol;
		int i;
		string itog;
		int len = 0;
		string mas[3];
		while (1){
			LPSTR  lpszPipeName = "\\\\.\\pipe\\$MyPipe$";
			hNamedPipe = CreateNamedPipe(
				L"\\\\.\\pipe\\$MyPipe$",
				PIPE_ACCESS_DUPLEX,
				PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
				PIPE_UNLIMITED_INSTANCES,
				512, 512, 5000, NULL);
			CreateProcess(L"E:\\1.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
			BOOL fConnected = ConnectNamedPipe(hNamedPipe, NULL);
			DWORD  cbWritten;
			DWORD dWait = -1;
			while (1){
				kol = 0;
				system("cls");
				cout << "Введите пароль для открытия архива: " << endl;
				getline(cin, password);
				for (i = 0; i < password.length(); i++){
					if (password[i] == ' ')
						kol++;
				}
				if (kol == 0)
					break;
			}
			kol = 0;
			cout << "Введите номер строки, которую нужно прочитать из файла: " << endl;
			cin >> kol;
			len = password.length();
			string temp = to_string(len);
			itog += temp;
			temp = to_string(kol);
			itog = itog + " " + password + " " + temp + "\n";
			len = itog.length();
			cout << itog;
			_getch();
			WriteFile(hNamedPipe, itog.c_str(), len,
				&cbWritten, NULL);
			while (dWait != WAIT_OBJECT_0){
				system("cls");
				cout << "Ожидание" << endl;
				dWait = WaitForSingleObject(pi.hProcess, INFINITE);
			}
			system("cls");
			DWORD  cWritten;
			char   sBuf[256];
			ReadFile(hNamedPipe, sBuf, 512, &cWritten, NULL);
			itog = sBuf;
			cout << "Возвращено значение из дочернего процесса: " << endl;
			for (i = 0; i < cWritten; i++){
				cout << sBuf[i];
			}
			cout << endl;
			cout << "Если хотите продолжить, нажмите 1: " << endl;
			cin >> lbl;
			cin.ignore(1, '\n');
			itog = "";
			password = "";
			kol = 0;
			if (lbl != 1)
				break;
		}
		#endif
        #ifdef linux
		int pipefd[2];
		int pipef[2];
		char buf1[255];
		char buf2[255];
		int kol, len;
		int i;
		pid_t cpid;
		char buf;
		string password, itog;
		string mas[3];

		cpid = fork();
		if (cpid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (cpid == 0) {//Child process
			close(pipefd[1]);
			i = 0;
			while (read(pipefd[0], &buf, 1) > 0){
				buf2[i] = buf;
				i++;
			}
			kol = 0;
			fstream fil("file.txt");
			string st, str;
			while (fil) {
				getline(fil, st);
				kol++;
			}
			fil.close();
			cout << kol << endl;
			int j = 0;
			char   *sBuf;
			char *b = strtok(szBuf, " \n");
			//Разделение полученного буфера на строки
			while (j != 3){
				mas[j] = b;
				b = strtok(NULL, " \n");
				j++;
			}

			int n = atoi(mas[2].c_str());
			cout << n << endl;
			i = 0;
			bool check = false;
			string temp = "";
			if (mas[1] == "password"){
				if (n < kol - 1){
					cout << "All data is OK, start to send" << endl;
					check = true;
				}
				else{
					str = "Out of file";
					close(pipefd[0]);
					write(pipefd[1], str.c_str(), str.length);
					close(pipefd[1]); 
				}
			}
			else{
				str = "Пароль неверен.";
				close(pipefd[0]);
				write(pipefd[1], str.c_str(), str.length);
				close(pipefd[1]); 
			}
			fstream fin("file.txt");
			i = 0;
			if (check == true){
				string str;
				while (fin) {
					getline(fin, temp);
					i++;
					if (i == n)
						break;
				}
				str = temp;
				cout << str << endl;
				close(pipefd[0]);
				write(pipefd[1], str.c_str(), str.length);
				close(pipefd[1]); 
			}
			fin.close();
			close(pipefd[0]);
			_exit(EXIT_SUCCESS);

		}
		else {//Parent process
			while (1){
				kol = 0;
				cout << "Enter your password for opening an archive: " << endl;
				getline(cin, password);
				for (i = 0; i < password.length(); i++){
					if (password[i] == ' ')
						kol++;
				}
				if (kol == 0)
					break;
			}
			kol = 0;
			cout << "Enter the number of string in file:" << endl;
			cin >> kol;
			len = password.length();
			string temp = to_string(len);
			itog += temp;
			temp = to_string(kol);
			itog = itog + " " + password + " " + temp + "\n";
			len = itog.length();
			cout << itog;
			for(i = 0; i < len; i++){
				buf1[i] = itog[i];
			}

			close(pipefd[0]);
			write(pipefd[1], buf1, len);
			close(pipefd[1]);
			cout << "Waiting..." << endl;
			wait(NULL);

			close(pipef[1]);
			itog = "";
			while (read(pipef[0], &buf, 1) > 0){
				itog += buf;
			}
			close(pipef[0]);
			cout << "Child process return a string." << endl;
			cout << itog << endl;
			exit(EXIT_SUCCESS);
		}
        #endif
	}
};

int main()
{
	Process_Work *proc = new Process_Work();
	proc->start();
	delete proc;
	return 0;
}
