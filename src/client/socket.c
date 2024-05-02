#include "client/socket.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int
openSocketClient (in_addr_t serverIp, unsigned int port)
{
  struct sockaddr_in servAddr;
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons (port); // use some unused port number
  servAddr.sin_addr.s_addr = serverIp;
  const int sockets = socket (AF_INET, SOCK_STREAM, 0);
  if (connect (sockets, (struct sockaddr *)&servAddr, sizeof (servAddr)) == -1)
  {
    perror ("connection failed");
    exit (EXIT_FAILURE);
  }
  return sockets;
}
void
closeSocket (int *sockfd)
{
}
void
receiveDataFromServer (int socket, char *buffer, int bufferSize)
{
}
void
sendDataToServer (int socket, const char *buffer, int bufferSize)
{
}
