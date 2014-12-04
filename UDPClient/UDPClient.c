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

#include "methods.h"

int main(int argc, char* argv[]) {
	struct sockaddr_in serverAddress;	//Contains info for server address
	char buffer[MAX];					//buffer for sending commands
	FILE* cmds;							//file pointer to commands.txt
	int sock;							//socket

	if(argc > 2) {
		err_n_die("Arguments: ./program <ip address>");
	}

	//read commands from text file.
	cmds = fopen("commands.txt", "r");
	fscanf(cmds,"%s", buffer);
	fclose(cmds);

	//create socket
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons("5000");
	if(inet_pton(AF_INET, argv[1], serverAddress.sin_addr.s_addr) == -1) {
		printf("Error: %s\n", strerr(errno));
		err_n_die("inet_pton() failed\n");
	}

	if(sendto(sock, buffer, MAX, 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
		printf("Error: %s\n", strerr(errno));
		err_n_die("sendto() failed\n");
	}

}
