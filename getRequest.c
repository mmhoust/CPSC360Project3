// Matt Houston

/* this function has been tested and works for recieving a simple message up to 100 chars
MUST PASS IN BUFFER OF SIZE char[10][20] */
#include "getRequest.h"

#define MAX 100
// Will use port 5000
int getRequest(char *messageBuffer, struct sockaddr_in *clntAddr,int sock){
                    /* Socket */

    unsigned int clientAddrLen;         /* Length of incoming message */
    char buffer[MAX];        /* Buffer for echo string */
    unsigned short echoServPort;     /* Server port */
    int recvMsgSize;                 /* Size of received message */



    clientAddrLen = sizeof(*clntAddr);

    /* Block until receive message from a client */
    if ((recvMsgSize = recvfrom(sock, buffer, MAX, 0,
        (struct sockaddr *) clntAddr, &clientAddrLen)) < 0)
        err_n_die("recvfrom() failed");
    strcpy(messageBuffer,buffer);
 
   
    return 0;
} 
