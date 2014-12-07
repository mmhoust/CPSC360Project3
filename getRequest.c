// Matt Houston

/* this function has been tested and works for recieving a simple message up to 100 chars
MUST PASS IN BUFFER OF SIZE char[10][20] */
#include "getRequest.h"

#define MAX 100
// Will use port 5000
int getRequest(char messageBuffer[100][20], struct sockaddr_in *clntAddr){
	int sock;                        /* Socket */
    struct sockaddr_in ServAddr; /* Local address */ /* Client address */
    unsigned int clientAddrLen;         /* Length of incoming message */
    char buffer[MAX];        /* Buffer for echo string */
    unsigned short echoServPort;     /* Server port */
    int recvMsgSize;                 /* Size of received message */
	int messageCount = 0;
	int pid;
    echoServPort = 5000;  

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        err_n_die("socket() failed");

    /* Construct local address structure */
    memset(&ServAddr, 0, sizeof(ServAddr));   /* Zero out structure */
    ServAddr.sin_family = AF_INET;                /* Internet address family */
    ServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    ServAddr.sin_port = htons(echoServPort);      /* Local port */

    /* Bind to the local address */
   // printf("UDPEchoServer: About to bind to port %d\n", echoServPort);    
    if (bind(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0)
        err_n_die("bind() failed");
    int flag = 1
    while (flag == 1) 
    {
        /* Set the size of the in-out parameter */
        clientAddrLen = sizeof(*clntAddr);

        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock, buffer, MAX, 0,
            (struct sockaddr *) clntAddr, &clientAddrLen)) < 0)
            err_n_die("recvfrom() failed");
        strcpy(messageBuffer[messageCount],buffer);
        messageCount++;
        if (strcmp(buffer,"END") == 0){
            flag == 0
        }

    }
    return messageCount ;
} 