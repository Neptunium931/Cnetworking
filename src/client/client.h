#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

struct server
{
  int s;
  char serverIpString[15];
  struct sockaddr_in *servAddr;
  bool connect;
};

void initHistory (void);
char *getVarEnv (char *name);

#endif /* end of include guard: CLIENT_H */
