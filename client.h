#define MAX 1024
#define PORT 5000

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/int.h>
#include <errno.h>
#include <unistd.h>

int getResponse(int sock);
void processResponse(char *response);
