#include "Archive.h"

void start(int kol);

int main()
{
	cout << "Enter number of clients: ";
	int kol;
	cin >> kol;
	start(kol);
	return 0;		
}

void start(int kol){
#ifdef linux
	Archive archive;
	if (!archive.createPipe()) {
		cout << "cannot create  or connect pipe" << endl;
		sleep(2);
		exit(1);
	}
	for (int i = 0; i < kol; i++) {
		if (!archive.createProc()) {
			cout << "cannot create process" << endl;
			sleep(2);
			exit(1);
		}
		sleep(2);
	}

	for (int i = 0; i < kol; i++)
	{	
		system("clear");
		archive.getResponse();
		archive.validate();
		archive.sendCallback();
		sleep(3);		
	}
	archive.closeHandle();
#endif
}
