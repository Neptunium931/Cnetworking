#include "server/socket.h"
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void
openSocketServer (struct sockaddr_in serv_addr, int *sockfd)
{
  *sockfd = socket (AF_INET, SOCK_STREAM, 0);
  if (*sockfd < 0)
  {
    perror ("impossible d'ouvrir le socket\n");
    exit (-1);
  }
  int socketOpt = 1;
  // Permettre la réutilisation de l'adresse du socket
  if (setsockopt (*sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socketOpt,
                  sizeof (socketOpt)))
  {
    perror ("setsockopt");
    exit (-1);
  }

  if (bind (*sockfd, (struct sockaddr *)&serv_addr, sizeof (serv_addr)) < 0)
  {
    perror ("impossible de faire le bind\n");
    exit (-1);
  }
  listen (*sockfd, 1);
}

void
closeSocket (const int *sockfd)
{
  close (*sockfd);
}

int
acceptClientConnetion (const int *sockfd)
{
  return accept (*sockfd, NULL, NULL);
}

void
receiveDataFromClient (int socket, char *buffer, int bufferSize)
{
  ssize_t bytesRead;
  char *tmpBuffer = calloc (1, sizeof (char) * bufferSize);

  if (tmpBuffer == NULL)
  {
    perror ("Erreur lors de l'allocation de mémoire pour tmpBuffer");
    return;
  }
  bytesRead = recv (socket, tmpBuffer, bufferSize, 0);
  if (bytesRead < 0)
  {
    perror ("recv");
    exit (EXIT_FAILURE);
  }
  strncat (buffer, tmpBuffer, bytesRead);
  memset (tmpBuffer, '\0', bufferSize);
  free (tmpBuffer);
}

void
sendDataToClient (int socket, const char *buffer, int bufferSize)
{
  ssize_t totalSent = 0;
  ssize_t bytesSent;

  while (totalSent < bufferSize)
  {
    bytesSent = send (socket, buffer + totalSent, bufferSize - totalSent, 0);
    if (bytesSent == -1)
    {
      perror ("Erreur lors de l'envoi des données");
      exit (-1);
    }
    totalSent += bytesSent;
  }
}
