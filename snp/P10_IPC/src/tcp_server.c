#include "tcp_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <unistd.h>


#include "snp_error_handler.h"
#include "stdbool.h"


static int ListeningSocket = 0;
static int connectedSocket = 0; 

void server_init(char* portNumber){
   struct addrinfo hints, *res, *p;
   int status;
   int sockfd;
   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;
   status = getaddrinfo(NULL, portNumber, &hints, &res);
   ExitOnError(status, "getaddrinfo");

   for(p = res; p != NULL; p = p->ai_next) {
       sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
       if (sockfd < 0) continue;
       int opt = 1;
       setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
       if (bind(sockfd, p->ai_addr, p->ai_addrlen) == 0) break;
       close(sockfd);
   }
   if (p == NULL) {
       perror("server_init: bind");
       exit(EXIT_FAILURE);
   }
   freeaddrinfo(res);
   if (listen(sockfd, 5) < 0) {
       perror("listen");
       exit(EXIT_FAILURE);
   }
   ListeningSocket = sockfd;
}

int getRequest(char* requestBuffer, int max_len)
{
   struct sockaddr_storage client_addr;
   socklen_t addrlen = sizeof client_addr;
   connectedSocket = accept(ListeningSocket, (struct sockaddr*)&client_addr, &addrlen);
   if (connectedSocket < 0) {
       perror("accept");
       exit(EXIT_FAILURE);
   }
   int n = recv(connectedSocket, requestBuffer, max_len, 0);
   if (n < 0) {
       perror("recv");
       exit(EXIT_FAILURE);
   }
   return n;
}

void sendResponse(char* response, int resp_len)
{
   int total = 0, n;
   while (total < resp_len) {
       n = send(connectedSocket, response + total, resp_len - total, 0);
       if (n < 0) {
           perror("send");
           exit(EXIT_FAILURE);
       }
       total += n;
   }
}

void server_close_connection(void)
{
   if (connectedSocket > 0) {
       close(connectedSocket);
       connectedSocket = 0;
   }
}

