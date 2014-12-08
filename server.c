#include "methods.h"
#include "getRequest.h"
#include "getResponse.h"
#include "processRequest.h"
#include "response.h"
#include "sendRequest.h"

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	char buffer[50];
	char response[1024];
	char request[1024];
	char udpresponse[1024];
	int rosock;
	unsigned short port = 5000;
	unsigned short roport;
	int recvMsgSize;
	
	if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		err_n_die("socket() failed");
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);
	
	if(bind(sock,(struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		err_n_die("bind() failed");
	
	for(;;)
	{
		memset(request,0,1024);
		memset(response,0,1024);
		memset(udpresponse,0,1024);
		getRequest(sock,buffer, &clntAddr);
		roport = processRequest(request,buffer);
		rosock = sendRequest(roport, request);
		getResponse(rosock,response);
		processResponse(response, buffer, udpresponse);
		sendResponse(udpresponse, sock, clntAddr);
	}	
}
