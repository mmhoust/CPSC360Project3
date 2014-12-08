#include "sendRequest.h"
#include "methods.h"

int sendRequest(unsigned short port, char *request)
{
	int sock;
	int reqLen;
	struct sockaddr_in servAddr;
	char *servip = "130.127.192.62";
	if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		err_n_die("socket() failed");
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(servip);
	servAddr.sin_port = htons(port);
	if(connect(sock,(struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
		err_n_die("connect() failed");
	reqLen = strlen(request);
	if(send(sock,request,reqLen, 0) != reqLen)
		err_n_die("send() failed");

	return sock;
}
