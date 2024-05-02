#include "server/server.h"

int
main (int argc, char *argv[])
{
  int *socket;
  int *sClient;
  struct sockaddr_in servAddr;
  struct fruit *fruits;
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons (9001);
  servAddr.sin_addr.s_addr = INADDR_ANY;

  socket = malloc (sizeof (int));
  openSocketServer (servAddr, socket);

  fruits = initFruits ();

  sClient = malloc (sizeof (int));
  *sClient = acceptClientConnetion (socket);

  mainProcess (sClient, fruits);

  clearFruits (fruits);
  close (*sClient);
  free (sClient);

  close (*socket);
  free (socket);
  return 0;
}
