#include "Archive.h"
#ifdef linux
Archive::Archive() {
	sem = sem_open("/semaphore", O_CREAT, 0777, 0);
	sem_post(sem);
	fstream fil("file.txt");
	string st;
	lineFile = 0;
	while (fil){
		getline(fil, st);
		lineFile++;
	}
	cout << "Number of lines in file: "<< lineFile << endl;
}
Archive::~Archive() {
	sem_unlink("/semaphore");
}
bool Archive::createProc() {
	pid = fork();
	if (pid < 0) return false;
	if (pid == 0)
	{
		execl("script.sh", NULL, NULL);
		exit(0);

	}
	return true;
}
bool Archive::createPipe() {
	unlink("/tmp/MyPipe");
	if ((mkfifo("/tmp/MyPipe", 0777)) == -1) {
		cout << "Невозможно создать пайп" << endl;
		return false;
	}

	pipeName = open("/tmp/MyPipe", O_RDWR);
	if (pipeName < 0)
	{
		cout << "Невозможно открыть файл\n";
		return false;
	}
	return true;
}
void Archive::getResponse() {
	read(pipeName, response, 50);
	mas[2] = "";
	mas[1] = "";
	mas[0] = "";
}
void Archive::sendCallback() {
	write(pipeName, callback, len);
}
void Archive::validate() {
	string str = string(response);
	int j = 0;
	int k = 0;
	while (j < str.length()){
		if (str[j] == '\n'){
			k++;
		}
		if (str[j] != '\n')
			mas[k] += str[j];
		j++;
		if (k == 3)
			break;
	}
	line = atoi(mas[2].c_str());
	cout << "Your string number is: " << line << endl;
	if (mas[1] == "password"){
		if (line < lineFile){
			cout << "All data is correct, start forming a response." << endl;
			fstream fin("file.txt");
			string itog = "";
			string st;
			int kol = 0;
			while (fin){
				getline(fin, st);
				kol++;
				if (kol == line)
					break;
				}
				stringstream ch;
				ch << line;
				itog = "";
				itog = itog + "Your number of string is " + ch.str() + "\n" + "Your string is " + st + "\n";
				len = itog.length();
				strcpy(callback, itog.c_str());
			}
			else{
				len = strlen(err2);
				strcpy(callback, err2);				
			}
		}
		else{
			len = strlen(err1);
			strcpy(callback, err1);
		}
}
void Archive::closeHandle() {
	close(pipeName);
}

#endif

