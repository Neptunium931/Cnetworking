#include "server/recvFruitProcess.h"
#include "protopeach.h"
#include <stdio.h>

void
recvFruitProcess (int *sClient, char *buffer, struct fruit *fruits)
{
  char *charCount, *copyBuffer, *name;
  struct fruit *fruit;
  int count;
  size_t line_pos;
  copyBuffer = strdup (buffer);
  charCount = copyBuffer;
  name = strsep (&charCount, " ");
  line_pos = strcspn (name, "\n");
  name[line_pos] = '\0';
  if (name == NULL || charCount != NULL)
  {
    unknownResponse (sClient);
    free (copyBuffer);
    return;
  }
  fruit = findFruit (name, fruits);
  if (fruit == NULL)
  {
    sendFruitResponceError (sClient, FRUITS_NOT_AVAILABLE);
    free (copyBuffer);
    return;
  }
  count = getCountFruit (fruit);
  if (!subCount (fruit, count))
  {
    recvFruitResponce (sClient, count);
  }
  else
  {
    recvFruitResponceError (sClient, TOO_MUCH_FRUITS);
  }
  free (copyBuffer);
}
