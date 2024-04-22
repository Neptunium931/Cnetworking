#include "server/server.h"
#include "protopeach.h"
#include "server/findFruit.h"
#include "server/matchString.h"
#include "server/socket.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct fruit *
initFruits (void)
{
  char *name = calloc (1, sizeof (char) * 20);
  struct fruit *fruits;
  maxFruit = 20;

  strcpy (name, "peach");
  fruits = createFirstFruit (name, 0);

  strcpy (name, "mango");
  createFruit (name, 0, fruits);

  strcpy (name, "kiwi");
  createFruit (name, 0, fruits);

  strcpy (name, "watermelon");
  createFruit (name, 0, fruits);

  strcpy (name, "tomato");
  createFruit (name, 0, fruits);

  strcpy (name, "ananas");
  createFruit (name, 0, fruits);

  free (name);
  return fruits;
}

bool
matchDomain (char *domain)
{
  return true;
}

void
heloResponse (int *sClient, enum response heloResponseChoise)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  char *errorCode = malloc (sizeof (char) * 3);
  strcpy (buffer, "HELO");
  switch (heloResponseChoise)
  {
  case OK:
    strcat (buffer, " OK");
    break;
  case NOK:
    strcat (buffer, " NOK ");
    sprintf (errorCode, "%d", SERVER_REFUSE_HELO);
    strcat (buffer, errorCode);
    break;
  default:
    break;
  }
  free (errorCode);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
}

void
unknownResponse (int *sClient)
{
  char *buffer = calloc (1, sizeof (char) * 3);
  sprintf (buffer, "%02d", UNKNOWN);
  sendDataToClient (*sClient, buffer, 3);
}

void
sendFruitResponceError (int *sClient, enum Errorcodes errorCode)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  char *errorCodeBuffer = malloc (sizeof (char) * 3);
  strcpy (buffer, "sendfruit NOK ");
  sprintf (errorCodeBuffer, "%02d", errorCode);
  strcat (buffer, errorCodeBuffer);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
  free (errorCodeBuffer);
}
void
sendFruitResponce (int *sClient)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  strcpy (buffer, "sendfruit");
  strcat (buffer, " OK");
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
}

void
sendFuitProcess (int *sClient, char *buffer, struct fruit *fruits)
{
  char *count, *copyBuffer, *name;
  struct fruit *fruit;
  copyBuffer = strdup (buffer);
  count = copyBuffer;
  name = strsep (&count, " ");
  if (name == NULL || count == NULL)
  {
    unknownResponse (sClient);
    return;
  }
  fruit = findFruit (name, fruits);
  if (fruit == NULL)
  {
    sendFruitResponceError (sClient, FRUITS_NOT_AVAILABLE);
    return;
  }
  if (!addCount (fruit, atoi (count)))
  {
    sendFruitResponce (sClient);
  }
  else
  {
    sendFruitResponceError (sClient, TOO_MUCH_FRUITS);
  }
}

int
main (int argc, char *argv[])
{
  int *s, *sClient;
  char *buffer, *copyBuffer;
  char *rest, *token;
  bool run;
  struct state state;
  struct sockaddr_in servAddr;
  struct fruit *fruits;
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons (9001);
  servAddr.sin_addr.s_addr = INADDR_ANY;

  s = malloc (sizeof (int));
  openSocketServer (servAddr, s);

  fruits = initFruits ();

  sClient = malloc (sizeof (int));
  *sClient = acceptClientConnetion (s);
  buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  run = true;
  state.helo = false;

  while (run)
  {
    memset (buffer, '\0', BUFFER_SIZE);
    receiveDataFromClient (*sClient, buffer, sizeof (buffer));
    if (buffer[0] == 'q')
    {
      run = false;
      continue;
    }
#define HELO_MAGIC "helo"
    copyBuffer = strdup (buffer);
    rest = copyBuffer;
    token = strsep (&rest, " ");
    if (!state.helo && matchString (token, (char *)HELO_MAGIC)
        && matchDomain (rest))
    {
      printf ("%s", buffer);
      heloResponse (sClient, OK);
      state.helo = true;
    }
    else if (state.helo && matchString (token, (char *)HELO_MAGIC)
             && matchDomain (rest))
    {
      printf ("%s", buffer);
      heloResponse (sClient, NOK);
      run = false;
      free (copyBuffer);
      continue;
    }
#define SEND_MAGIC "sendfruit"
    else if (state.helo && matchString (token, (char *)SEND_MAGIC))
    {
      sendFuitProcess (sClient, rest, fruits);
    }
    else if (state.helo)
    {
      printf ("%s", buffer);
      unknownResponse (sClient);
      run = false;
      free (copyBuffer);
      continue;
    }
    else
    {
      printf ("%s", buffer);
      heloResponse (sClient, NOK);
      run = false;
      free (copyBuffer);
      continue;
    }
    free (copyBuffer);
  }
  free (buffer);

  close (*sClient);
  free (sClient);

  close (*s);
  free (s);
  return 0;
}
