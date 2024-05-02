#ifndef socket_H
#define socket_H
#include <arpa/inet.h>
#include <sys/socket.h>

void openSocketServer (struct sockaddr_in serv_addr, int *sockfd);
void closeSocket (const int *sockfd);
int acceptClientConnetion (const int *sockfd);
void receiveDataFromClient (int socket, char *buffer, int bufferSize);
void sendDataToClient (int socket, const char *buffer, int bufferSize);

#endif /* end of include guard: socket_H */
