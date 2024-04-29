#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <stdio.h>

struct server
{
  int s;
  char serverIpString[15];
  in_addr_t serverIp;
  unsigned int port;
};

void initHistory (void);
char *getVarEnv (char *name);

#endif /* end of include guard: CLIENT_H */
