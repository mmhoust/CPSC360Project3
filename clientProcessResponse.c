#include "client.h"

void processResponse(char *response) {
     char buffer[MAX];
     char* reader = NULL;
     int length;
int k = 0;
char buf[1024];
char databuf[1024];
memset(&databuf[0],'\0',sizeof(databuf));
     reader = strstr(response, "GPS");
     //GPS response
     if(reader != NULL) {
           reader = strstr(response, "DGPS");
           //DGPS response
           if(reader != NULL) {
                char *i;
		int j = 0;
		int line = 0;
		int length = 0;
		for(i = response; *i; i++)
		{
			if(line < 2)
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
					if(line == 0)
						printf("%s ",buf);
					else if (line == 1)
						length = atoi(buf);
					line++;
					j = 0;
					memset(&buf[0],'\0',sizeof(buf));
				}
			}
			else
			{
				databuf[k] = *i;
				k++;
				//printf("%c",*i);
			}
		}
		//databuf[k] = '\0';
		printf("%s\n",databuf);	
           }
           else {
		char *i;
		int j = 0;
		int line = 0;
		int length = 0;
		for(i = response; *i; i++)
		{
			if(line < 2)
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
					if(line == 0)
						printf("%s ",buf);
					else if (line == 1)
						length = atoi(buf);
					line++;
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
		//databuf[k] = '\0';
		printf("%s\n",databuf);
           }
     }
}
