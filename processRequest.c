// process request

#include "processRequest.h"
//returns portnumber
int processRequest(char *request,char **messageBuffer, int bufferPos){
	int port;
	char getLine[100];
	char message[50];
	strcpy(message,messageBuffer[bufferPos]);
	// create first line of request
	if(strcmp(message,"GPS") == 0){
		port = 8082;
		strcat(getLine,"GET state?id=little HTTP/1.1\r\n");
	}else if(strcmp(message,"DGPS") == 0){
		port = 8084;
		strcat(getLine,"GET state?id=little HTTP/1.1\r\n");
	}else if(strcmp(message,"LASERS")){
		port = 8083;
		strcat(getLine,"GET state?id=little HTTP/1.1\r\n");
	}else if(strcmp(message,"MOVE") == 0){
		port = 8082;
		strcat(getLine,"GET twist?id=little&lx=4 HTTP/1.1\r\n");
	}else if(strcmp(message,"TURN") == 0){
		port = 8082;
		strcat(getLine,"GET twist?id=little&az=30 HTTP/1.1\r\n");
	}else if(strcmp(message,"STOP") == 0){
		port = 8082;
		strcat(getLine,"GET twist?id=little&lx=0 HTTP/1.1\r\n");
	}

	strcat(request,getLine);
	strcat(request,"Connection: Keep-Alive\r\n");
	strcat(request,"Host: www.cs.clemson.edu\r\n");
	strcat(request,"\r\n");
	return port;
}