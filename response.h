/*
I tested processResponse and it was working. Needs the buffer to be passed to it and the type to be passed to it (GPS, etc)
The formatting or protocol that it uses is [response: 1]/r/n[type]/r/n[length]/r/n[data]

Haven't tested sendResponse but I am pretty sure it works. If not it should be an easy fix.
Needs the buffer, the udp client socket, and the client address.
*/
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


char* processResponse(char *buffer, char *type);
void sendResponse(char *buffer, int messageSize, int sock, struct sockaddr_in ClntAddr);

char* processResponse(char *buffer, char *type)
{
	char *i;
	int data = 0;
	int length = 0;
	char *databuf;
	int k = 0;
	char buf[1024];
	int j = 0;
	for(i=buffer; *i; i++)
	{
		if(data == 0)
		{
			if(*i != '\n')
			{
				buf[j] = *i;
				j++;
			}
			else
			{
				buf[j] = *i;
				int n = strlen(buf);
				while(!isalnum(buf[n]) && n >= 0)
					buf[n--] = '\0';
				if(buf[0] == '\0')
					data = 1;
				int l;
				char *e;
				e = strchr(buf,':');
				if(e!=NULL)
					l = (int)(e-buf);
				else
					l = strlen(buf);
				char copy[1024] = {0};
				strncpy(copy,buf,l);
				copy[l] = '\0';
				if(!strcmp(copy,"Content-Length"))
				{
					char *tbuf = buf;
					char len[40] = {0};
					tbuf  += l + 2;
					strcpy(len, tbuf);
					length = atoi(len);
					databuf = (char *)malloc((length+1)*sizeof(char));
				}
				j = 0;
				memset(&buf[0],'\0',sizeof(buf));
			}
		}
		else
		{
			databuf[k] = *i;
			k++;
		}
	}
	databuf[k] = '\0';
	static char resp[1024];
	sprintf(resp, "%s\r\n%d\r\n%s",type,length,databuf);
	free(databuf);
	return resp;
}

void sendResponse(char *buffer, int sock, struct sockaddr_in ClntAddr)
{
	if(sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *) &ClntAddr, sizeof(ClntAddr)))
	{
		printf("sendto() failed.\n");
		exit(0);
	}
}

