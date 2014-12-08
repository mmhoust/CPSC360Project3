#include "getResponse.h"
#include "methods.h"

void getResponse(int sock, char *buffer)
{
	int bytesRcvd;
	if((bytesRcvd = recv(sock, buffer, 1024, 0) )<= 0)
		err_n_die("rev() failed");	
}
