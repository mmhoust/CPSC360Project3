// Matt Houston

/* this function has been tested and works for recieving a simple message up to 100 chars
MUST PASS IN BUFFER OF SIZE char[10][20] */
#include "getRequest.h"

#define MAX 100
// Will use port 5000
int getRequest(int sock, char *buffer, struct sockaddr_in *clntAddr){

	int recvMsgSize;
	int clientAddrLen = sizeof(clntAddr);
        if ((recvMsgSize = recvfrom(sock, buffer, 50, 0,
            (struct sockaddr *) clntAddr, &clientAddrLen)) < 0)
            err_n_die("recvfrom() failed");
	return recvMsgSize;
} 
