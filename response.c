#include "response.h"

void processResponse(char *buffer, char *type, char *resp)
{
	char *i;
	int data = 0;
	int length = 0;
	char databuf[1024];
	int k = 0;
	char buf[1024];
	int j = 0;
	memset(&databuf[0],'\0',sizeof(databuf));
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
	type[strlen(type)-1] = '\0';
	sprintf(resp, "%s\r\n%d\r\n%s",type,length,databuf);
}

void sendResponse(char *buffer, int sock, struct sockaddr_in ClntAddr)
{
	int a;
	if((a = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *) &ClntAddr, sizeof(ClntAddr))) <= 0)
		err_n_die("sendto() failed");
}
