// get request
#ifndef GETREQUEST
#include "methods.h"
#define GETREQUEST

/* This function will get request from UDPclient
   will take in preallocated message that will contain 
   the message from the request */
int getRequest(char *message, struct sockaddr_in *clntaddress, int sock);

#endif
