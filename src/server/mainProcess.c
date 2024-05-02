#include "server/mainProcess.h"

void
mainProcess (int *sClient, struct fruit *fruits)
{
  char *buffer;
  bool run;
  struct state state;
  buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  run = true;
  state.helo = false;
  while (run)
  {
    char *rest;
    char *token;
    char *copyBuffer;
    memset (buffer, '\0', BUFFER_SIZE);
    receiveDataFromClient (*sClient, buffer, malloc_usable_size (buffer));
#define HELO_MAGIC "helo"
    copyBuffer = strdup (buffer);
    rest = copyBuffer;
    token = strsep (&rest, " ");
    if (!state.helo && matchString (token, (char *)HELO_MAGIC)
        && matchDomain (rest))
    {
      printf ("%s\nOK\n", buffer);
      heloResponse (sClient, OK);
      state.helo = true;
    }
    else if (state.helo && matchString (token, (char *)HELO_MAGIC)
             && matchDomain (rest))
    {
      printf ("%s\nNOK\n", buffer);
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
#define RECV_MAGIC "recvfruit"
    else if (state.helo && matchString (token, (char *)RECV_MAGIC))
    {
      recvFruitProcess (sClient, rest, fruits);
    }
#define CHANGE_MAGIC "chngfruit"
    else if (state.helo && matchString (token, (char *)CHANGE_MAGIC))
    {
      changeFruitProcess (sClient, rest, fruits);
    }
#define HOWMANY_MAGIC "howmany"
    else if (state.helo && matchString (token, (char *)HOWMANY_MAGIC))
    {
      howmanyProcess (sClient, rest, fruits);
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
      printf ("%s\n", buffer);
      heloResponse (sClient, NOK);
      run = false;
      free (copyBuffer);
      continue;
    }
    free (copyBuffer);
  }
  free (buffer);
}
