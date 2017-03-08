#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include<fstream>
using namespace std;

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char   szPipeName[256];
	HANDLE hNamedPipe;
	string mas[3];
	strcpy(szPipeName, "\\\\.\\pipe\\$MyPipe$");
	hNamedPipe = CreateFile(
		szPipeName, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);
	DWORD  cbRead;
	char   szBuf[256];
	int i = 0;
	ReadFile(hNamedPipe, szBuf, 512, &cbRead, NULL);
	int kol = 0;
	fstream fil("E:/file.txt");
	string st, str;
	while (fil) {
		getline(fil, st);
		kol++;
	}
	fil.close();
	cout << kol << endl;
	DWORD  cWritten;
	int j = 0;
	char   *sBuf;
	char *buf = strtok(szBuf, " \n");
	//Разделение полученного буфера на строки
	while (j != 3){
		mas[j] = buf;
		buf = strtok(NULL, " \n");
		j++;
	}
	int n = atoi(mas[2].c_str());
	cout << n << endl;
	i = 0;
	bool check = false;
	string temp = "";
	if (mas[1] == "password"){
		if (n < kol - 1){
			cout << "Все данные верны, чтение из файла" << endl;
			check = true;
		}
		else{
			str = "Выход за границы файла.";
			WriteFile(hNamedPipe, str.c_str(), str.length(),
				&cWritten, NULL);
		}
	}
	else{
		str = "Пароль неверен.";
		WriteFile(hNamedPipe, str.c_str(), str.length(),
			&cWritten, NULL);
	}
	fstream fin("E:/file.txt");
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
		WriteFile(hNamedPipe, str.c_str(), str.length(),
			&cWritten, NULL);
	}
	fin.close();
	_getch();
	ExitProcess(WAIT_OBJECT_0);
	return 0;
}