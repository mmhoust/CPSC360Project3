#include "client.h"

int getResponse(int sock) {
      struct sockaddr_in recAddress;
      struct sockaddr_in clientAddress;
      char buffer[MAX];

      socklen_t clientAddressLen = sizeof(clientAddress);

      if (recvfrom(sock, buffer, MAX, 0, (struct sockaddr *) &clientAddress, &clientAddressLen) < 0) {
            printf("ERROR\t%s\n", strerror(errno));
            err_n_die("recvfrom() failed");
      }
      processResponse(buffer);
}
