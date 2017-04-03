#include "Archive.h"


int main()
{
	cout << "Input number clients: ";
	int amount;
	cin >> amount;
#ifdef linux

		Archive archive;
		if (!archive.createPipe()) {
			cout << "cannot create  or connect pipe" << endl;
			sleep(2);
			exit(1);
		}
		for (int i = 0; i < amount; i++) {
			if (!archive.createProc()) {
				cout << "cannot create process" << endl;
				sleep(2);
				exit(1);
			}
}

		for (int i = 0; i < amount; i++)
		{
			archive.readFromPipe();
			archive.addRequestToFile();
			archive.downloading();
			archive.writeToPipe();
			sleep(3);			
		}
		archive.closeHandle();
		return 0;
	
#endif

		
}
