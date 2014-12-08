#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>     
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netdb.h>      
#include <stdlib.h>    
#include <unistd.h>     
#include <ctype.h>

#include "methods.h"

void processResponse(char *buffer, char *type, char *resp);
void sendResponse(char *buffer, int sock, struct sockaddr_in ClntAddr);
