/*
 * UDPClient.c
 *
 *  Created on: Dec 3, 2014
 *      Author: Steven
 */

#include "client.h"
#include "methods.h"

ssize_t getLines(char **line, FILE* stream,size_t *len);

int main(int argc, char* argv[]) {
	struct sockaddr_in serverAddress;	//Contains info for server address
	char *buffer = (char*) malloc(1024);					//buffer for sending commands
	FILE* cmds;							//file pointer to commands.txt
	unsigned int sleeptime;
	int sock;							//socket

	if(argc > 2 || argc == 1) {
		err_n_die("Arguments: ./program <ip address>");
	}

	//create socket
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sock < 0) {
		printf("ERROR\t%s\n", strerror(errno));
		err_n_die("socket() failed\n");
	}

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(5000);
	if(inet_pton(AF_INET, argv[1], &serverAddress.sin_addr.s_addr) == -1) {
		err_n_die("inet_pton() failed\n");
	}

	//read commands from text file.
	cmds = fopen("commands.txt", "r");
	size_t len = 0;
	while(getLines(&buffer, cmds,&len) != -1) {

		//Get sleep time
		if(strstr(buffer, "sleep") != NULL){
			//Get ready for bed.
			int i = 0;
			for(i = 0; i < strlen(buffer); i++) {
				if((int)buffer[i] < 10) {
					//good night
					sleeptime = (unsigned int)buffer[i];
					sleep(sleeptime);
					break;
				} //if
			} //for
		} //if

		//send regular command
		else {
			if(sendto(sock, buffer, MAX, 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
				err_n_die("sendto() failed\n");
			} //if
		} //else
		//Block until we get response
		getResponse(sock);
	} //while

	//TODO: Receive data and save data. infinite loop?
	free(buffer);
	fclose(cmds);
	return 0;
} //main

ssize_t getLines(char **line, FILE* stream ,size_t *len) {
	return getdelim(line, len,'\n', stream);
}
