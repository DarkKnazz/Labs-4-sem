
	#include "Proc.h"


int main()
{
	cout << "Input number clients: ";
	int amount;
	cin >> amount;
#ifdef WIN32 || WIN64
	Server server(amount);
	for (int i = 0; i < amount; i++) {
		if (!server.createPipe(server.getPipe(i))) {
			cerr << "Creation of the named pipe failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			cout << "Press any char to finish server: " << endl;
			server.~Server();
			_getch();
			return 1;
		}
		if (!server.createProc()) {
			_cputs("The new process is not created.\n");
			_cputs("Check a name of the process.\n");
			_cputs("Press any key to finish.\n");
			server.~Server();
			_getch();
			return 1;
		}
		cout << "The server is waiting for connection with a client." << endl;
		if (!server.connectPipe(server.getPipe(i))) {
			cerr << "The connection failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			server.closeHandle(server.getPipe(i));
			server.~Server();
			cout << "Press any char to finish the server: ";
			_getch();
			return 1;
		}
	}
	for (int i = 0; i < amount; i++) {
		system("CLS");
		cout << "The server wait url...";
		if (!server.readFromPipe(server.getPipe(i))) {
			cerr << "Data reading from the named pipe failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			server.closeHandle(server.getPipe(i));
			server.~Server();
			cout << "Press any char to finish the server: ";
			_getch();
			return 1;
		}
		if (server.checking()) {
			if (!server.checkRequest())
			{
				server.addRequestToFile();
				server.downloading();
			}
		}
		if (!server.writeToPipe(server.getPipe(i))) {
			cerr << "Data writing to the named pipe failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			server.closeHandle(server.getPipe(i));
			server.~Server();
			cout << "Press any char to finish the server: ";
			_getch();
			return 1;
		}
		server.closeHandle(server.getPipe(i));
	}
	server.closeHandle(server.getSemaphore());
	_getch();
	return 0;
#endif // WIN32 || WIN64
#ifdef linux

		Server server;
		if (!server.createPipe()) {
			cout << "cannot create  or connect pipe" << endl;
			sleep(2);
			exit(1);
		}
		for (int i = 0; i < amount; i++) {
			if (!server.createProc()) {
				cout << "cannot create process" << endl;
				sleep(2);
				exit(1);
			}
}

		for (int i = 0; i < amount; i++)
		{
			server.readFromPipe();
			if (server.checking()) {
				if (!server.checkRequest()) {
					server.addRequestToFile();
					server.downloading();
				}
			}
			server.writeToPipe();
			sleep(3);			
		}
		server.closeHandle();
		return 0;
	
#endif

		
}
