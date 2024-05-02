#ifndef SOCKET_H
#define SOCKET_H
#include <arpa/inet.h>
#include <sys/socket.h>

int openSocketClient (in_addr_t serverIp, unsigned int port);
void closeSocket (int *sockfd);
void receiveDataFromServer (int socket, char *buffer, int bufferSize);
void sendDataToServer (int socket, const char *buffer, int bufferSize);
#endif /* end of include guard: SOCKET_H */
