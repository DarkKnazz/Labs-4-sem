
	#include "Client.h"



int main(void) {
	Client client;
#ifdef linux
	client.initSem();
	client.ConnectPipe();
	client.waitServer();
#endif // linux
	
#ifdef _WIN32 || _WIN64
	client.ConnectPipe();
	client.createThread();
	client.waitServer();
#endif // _WIN32 || _WUN64
	
	client.writeInPipe();
	if (client.getWait() == 'N') {
		cout << " I can work" << endl;
		for (int i = 0; i < 10; i++) {
#ifdef _WIN32 || _WIN64
			Sleep(500);
#endif
#ifdef linux
			usleep(200000);
#endif
			cout << i << '.';
			std::cout.flush();
		}
		cout << " I doing something " << endl;
	}
#ifdef _WIN32 || _WIN64
	client.readFromFile();
	client.waitAnswer();
	client.closeHandle();
	cin.ignore(256, '\n');
	fflush(stdin);
	_getch();
#endif // _WIN32 || _WIN64
#ifdef linux
	sleep(2);
	client.readFromPipe();
	client.outputResult();
	sleep(5);
#endif // linux
	return 0;
	
}




