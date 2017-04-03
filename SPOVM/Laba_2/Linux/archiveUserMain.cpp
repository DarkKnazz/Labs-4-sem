#include "Archive_User.h"

int main(void) {
	ArchiveUser arcUser;
#ifdef linux
	arcUser.initSem();
	arcUser.connection();
	arcUser.waitForAnswer();
	arcUser.sendResponse();
	sleep(2);
	arcUser.getCallback();
	arcUser.outputResult();
	sleep(5);
#endif
	return 0;
	
}




