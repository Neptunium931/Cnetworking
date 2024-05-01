#include "server/sendFuitProcess.h"

void
sendFuitProcess (int *sClient, char *buffer, struct fruit *fruits)
{
  int diffCount;
  char *count, *copyBuffer, *name;
  struct fruit *fruit;
  if (buffer == NULL)
  {
    unknownResponse (sClient);
    return;
  }
  copyBuffer = strdup (buffer);
  count = copyBuffer;
  name = strsep (&count, " ");
  if (name == NULL)
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
  diffCount = atoi (count) - getCountFruit (fruit);
  if (!addCount (fruit, diffCount))
  {
    sendFruitResponce (sClient);
  }
  else
  {
    sendFruitResponceError (sClient, TOO_MUCH_FRUITS);
  }
  free (copyBuffer);
}
