#include "clear.h"
#include "protopeach.h"

void
clearFruits (struct fruit *fruits)
{
  if (fruits == NULL)
  {
    return;
  }
  struct fruit *next;
  struct fruit *prev;
  next = getNextFruit (fruits);
  while (next != NULL)
  {
    delFruit (fruits);
    fruits = next;
    next = getNextFruit (fruits);
  }
  prev = getPrevFruit (fruits);
  while (prev != NULL)
  {
    delFruit (fruits);
    fruits = next;
    prev = getPrevFruit (fruits);
  }
  delFruit (fruits);
}
