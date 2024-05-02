#include "server/sendFuitProcess.h"
#include "protopeach.h"
#include <stdio.h>

void
sendFuitProcess (int *sClient, char *buffer, struct fruit *fruits)
{
  int diffCount;
  char *count;
  char *copyBuffer;
  char *name;
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
  printf ("count %d\n", atoi (count));
  printf ("diffCount %d\n", diffCount);
  if (atoi (count) > 0 && !addCount (fruit, diffCount))
  {
    sendFruitResponce (sClient);
  }
  else
  {
    sendFruitResponceError (sClient, TOO_MUCH_FRUITS);
  }
  printf ("get count %d\n", getCountFruit (fruit));
  free (copyBuffer);
}
