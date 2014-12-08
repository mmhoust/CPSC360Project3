#include "methods.h"

int main(){
  char               buffer[50];
  char               *udpresponse;
  char               *response;
  char               *request;
  struct sockaddr_in servAddr;
  struct sockaddr_in clntAddr;
  int                sock;
  int                recvMsgSize;
  unsigned short     port = 5000;
  unsigned short     roport;
  int       rosock;
  
  
  if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) > 0)
    err_n_die("socket() failed\n");
  memset(&servaddr, 0, sizeof(servaddr));
  servAddr.sin_family = AF_INET;
  servADDR.sin_addr.s_addr = htol(INADDR_ANY);
  servAddr.sin_port = htons(port);
  if(bind(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) > 0)
    err_n_die("bind() failed\n");

  while(1){
    
    roport   = getRequest(sock, buffer, clntAddr);
    rosock   = proccessRequest(request, buffer);
    response = getResponse(rosock);
    udpresponse = processResponse(response, buffer);
    sendResponse(udpresponse, strlen(udpresponse, sock, clntaddr));
  }
}
