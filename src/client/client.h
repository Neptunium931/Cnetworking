#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

#define LEN_IP_STRING 15
struct server
{
  int s;
  char serverIpString[LEN_IP_STRING];
  struct sockaddr_in *servAddr;
  bool connect;
};

void initHistory (void);

#endif /* end of include guard: CLIENT_H */
