#ifdef WIN32
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#endif
#ifdef linux
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#endif
using namespace std;

class Archive
{
#ifdef WIN32
private:
	unsigned int line;
	string password;
	DWORD  cbRead;
	char   szBuf[256];
	string mas[3];
	LPWSTR pipeName;
	HANDLE pipe;

	int kol;
#endif
public:
	Archive() {
#ifdef WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Дочерний процесс" << endl;
		pipe = CreateFile(
			L"\\\\.\\pipe\\$MyPipe$", GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);

	}
#endif

	void validate() {
#ifdef WIN32
		ReadFile(pipe, szBuf, 512, &cbRead, NULL);
		fstream fil("/file.txt");
		string st;
		while (fil) {
			getline(fil, st);
			kol++;
		}
		fil.close();
		cout << "Количество строк в файле: " << kol << endl;
		int j = 0;
		char *buf = strtok(szBuf, " \n");
		//Разделение полученного буфера на строки
		while (j != 3){
			mas[j] = buf;
			buf = strtok(NULL, " \n");
			j++;
		}
		line = atoi(mas[2].c_str());
		cout << "Искомая строка: " << line << endl;
#endif
#ifdef linux
		int pipefd[2];
		int pipef[2];
		pid_t cpid;
		string password;
		char buf;
		char s[50] = "Hello world!!!!";
		char err1[50] = "Invalid password!";
		char err2[50] = "Out of file!";
		string s1;
		char b;
		char str[100];
		char tmp[100];
		char msg[100];
		string mas[3];

		if (pipe(pipefd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (pipe(pipef) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		cpid = fork();
		if (cpid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (cpid == 0) {    /* Child reads from pipe */
			close(pipefd[1]);          /* Close unused write end */
			s1 = "";
			while (read(pipefd[0], &buf, 1) > 0)
				s1 += buf;
			int j;
			fstream fil("file.txt");
			string st;
			int kol = 0;
			while (fil){
				getline(fil, st);
				kol++;
			}
			cout << endl << "***************************" << endl;
			cout << "Child process is working..." << endl;
			cout << "Number of lines in file: " << kol << endl;
			j = 0;
			int k = 0;
			while (j != s1.length()){
				if (s1[j] == '\n'){
					k++;
				}
				if (s1[j] != '\n')
					mas[k] += s1[j];
				j++;
				if (k == 3)
					break;
			}
			int line = atoi(mas[2].c_str());
			cout << "Your string number is: " << line << endl;
			if (mas[1] == "password"){
				if (line < kol){
					cout << "All data is correct, start forming a response." << endl;
					fstream fin("file.txt");
					string itog = "";
					kol = 0;
					while (fin){
						getline(fin, st);
						kol++;
						if (kol == line)
							break;
					}
					stringstream ch;
					ch << line;
					itog = itog + "Your number of string is " + ch.str() + "\n" + "Your string is " + st + "\n";
					for (j = 0; j < itog.length(); j++){
						msg[j] = itog[j];
					}
					close(pipefd[0]);
					close(pipef[0]);
					write(pipef[1], msg, itog.length());
				}
				else{
					close(pipefd[0]);
					close(pipef[0]);
					write(pipef[1], err2, strlen(err2));
				}
			}
			else{
				close(pipefd[0]);
				close(pipef[0]);
				write(pipef[1], err1, strlen(err1));
			}
			cout << "Response is sending do parent...!" << endl;
			cout << "***************************" << endl;
			sleep(2);
			close(pipef[1]);
			_exit(EXIT_SUCCESS);

		}
		else {
			cout << "In parent" << endl;
			close(pipefd[0]);          /* Close unused rtmp, ead end */
			cout << "Enter password: " << endl;
			getline(cin, password);
			cout << "Enter line: " << endl;
			int kol;
			cin >> kol;
			stringstream ch;
			ch << kol;
			stringstream ch1;
			ch1 << password.length();
			password = ch1.str() + "\n" + password + "\n" + ch.str() + "\n";
			for (int i = 0; i < password.length(); i++){
				str[i] = password[i];
			}
			write(pipefd[1], str, password.length());
			cout << "Bytes written!" << endl;
			close(pipefd[1]);          /* Reader will see EOF */
			wait(NULL);                /* Wait for child */
			close(pipef[1]);
			cout << endl << "***************************" << endl;;
			while (read(pipef[0], &b, 1) > 0)
				write(STDOUT_FILENO, &b, 1);
			write(STDOUT_FILENO, "\n", 1);
			close(pipef[0]);
			cout << "End..." << endl;
			exit(EXIT_SUCCESS);
		}
#endif
	}

	void sendResponse() {
#ifdef WIN32
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
				WriteFile(pipe, str.c_str(), str.length(),
					&cWritten, NULL);
			}
		}
		else{
			str = "Пароль неверен.";
			WriteFile(pipe, str.c_str(), str.length(),
				&cWritten, NULL);
		}
		fstream fin("/file.txt");
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
		fin.close();
		_getch();

		ExitProcess(WAIT_OBJECT_0);
#endif
#ifdef linux
		return;
#endif
	}
};