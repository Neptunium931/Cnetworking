#include "server/changeFruitProcess.h"
#include "matchString.h"
#include "protopeach.h"
#include "server/findFruit.h"
#include <stdio.h>

void
changeFruitProcess (int *sClient, char *buffer, struct fruit *fruits)
{
  char *newName;
  char *copyBuffer;
  char *name;
  struct fruit *fruit;
  copyBuffer = strdup (buffer);
  newName = copyBuffer;
  name = strsep (&newName, " ");
  if (name == NULL || newName == NULL || findFruit (newName, fruits) != NULL)
  {
    unknownResponse (sClient);
    free (copyBuffer);
    return;
  }
  fruit = findFruit (name, fruits);
  if (fruit == NULL)
  {
    changeFruitResponceError (sClient, FRUITS_NOT_AVAILABLE);
    free (copyBuffer);
    return;
  }
  setNameFruit (fruit, newName);
  if (!matchString (newName, getNameFruit (fruit)))
  {
    changeFruitResponceError (sClient, FRUITS_NOT_AVAILABLE);
    free (copyBuffer);
    return;
  }
  changeFruitResponce (sClient, getNameFruit (fruit));
  free (copyBuffer);
}
