#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "snp_error_handler.h"
#include "tcp_client.h"

int client_connect(const char* ServerName, const char* PortNumber)
{
   struct addrinfo hints, *res, *p;
   int status, sockfd;
   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   status = getaddrinfo(ServerName, PortNumber, &hints, &res);
   ExitOnError(status, "getaddrinfo");

   for (p = res; p != NULL; p = p->ai_next) {
       sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
       if (sockfd < 0) continue;
       if (connect(sockfd, p->ai_addr, p->ai_addrlen) == 0) break;
       close(sockfd);
   }
   if (p == NULL) {
       fprintf(stderr, "client_connect: failed to connect\n");
       exit(EXIT_FAILURE);
   }
   freeaddrinfo(res);
   return sockfd;
}

int receiveResponse(int communicationSocket, char* buffer, int len)
{
   int total = 0, n;
   while (total < len) {
       n = recv(communicationSocket, buffer + total, len - total, 0);
       if (n <= 0) ExitOnError(n, "recv");
       total += n;
   }
   return total;
}

void sendRequest(int communicationSocket, char* buffer, int len)
{
   int total = 0, n;
   while (total < len) {
       n = send(communicationSocket, buffer + total, len - total, 0);
       if (n < 0) ExitOnError(n, "send");
       total += n;
   }
}

