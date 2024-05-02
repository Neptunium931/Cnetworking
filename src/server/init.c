#include "server/init.h"
#include "protopeach.h"

struct fruit *
initFruits (void)
{
  char *name = calloc (1, sizeof (char) * LEN_FRUIT_NAME);
  struct fruit *fruits = NULL;

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
