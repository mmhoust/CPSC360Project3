/*
 * UDPClient.c
 *
 *  Created on: Dec 3, 2014
 *      Author: Steven
 */
#define MAX 1024

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#include "methods.h"

int main(int argc, char* argv[]) {
	struct sockaddr_in serverAddress;	//Contains info for server address
	char buffer[MAX];					//buffer for sending commands
	FILE* cmds;							//file pointer to commands.txt
	unsigned int sleeptime;
	int sock;							//socket

	if(argc > 2) {
		err_n_die("Arguments: ./program <ip address>");
	}

	//create socket
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons("5000");
	if(inet_pton(AF_INET, argv[1], serverAddress.sin_addr.s_addr) == -1) {
		printf("Error: %s\n", strerr(errno));
		err_n_die("inet_pton() failed\n");
	}

	//read commands from text file.
	cmds = fopen("commands.txt", "r");
	while(getLines(&buffer, cmds)) {
		//Get sleep time
		if(strstr(buffer, "sleep") != NULL){
			int i = 0;
			for(i = 0; i < strlen(buffer); i++) {
				if((int)buffer[i] < 10) {
					sleeptime = (unsigned int)buffer[i];
					sleep(sleeptime);
					continue;
				}
			}
		}
		//default sleep time
		else if(strstr(buffer, "sleep" != NULL)) {
			sleeptime = 1;
			sleep(sleeptime);
			continue;
		}
		//send regular command
		else {
			if(sendto(sock, buffer, MAX, 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
				printf("Error: %s\n", strerr(errno));
				err_n_die("sendto() failed\n");
			}
		}

	}
	fclose(cmds);



}

ssize_t getLines(char **line, FILE* stream) {
	return getdelim(line, '\n', stream);
}
