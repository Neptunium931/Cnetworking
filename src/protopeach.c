#include "protopeach.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int maxFruit = FRUITMAX;

struct fruit
{
  char name[LEN_FRUIT_NAME];
  int count;
  struct fruit *nextFuit;
  struct fruit *prevFuit;
};

struct fruit *
createFirstFruit (char *fname, int fcount)
{
  struct fruit *res = (struct fruit *)calloc (1, sizeof (struct fruit));
  if (res == NULL)
  {
    puts ("null creation ");
  }
  setNameFruit (res, fname);
  res->count = fcount;
  return res;
}

void
createFruit (char *name, int count, struct fruit *headFruit)
{
  if (headFruit == NULL)
  {
    perror ("createFruit headFruit is null\n");
    return;
  }
  while (headFruit->nextFuit != NULL)
  {
    headFruit = headFruit->nextFuit;
  }
  headFruit->nextFuit = createFirstFruit (name, count);
  headFruit->nextFuit->prevFuit = headFruit;
}

void
delFruit (struct fruit *fruit)
{
  if (fruit->prevFuit != NULL)
  {
    // reassign the nextFuit value of the previous fruit if there is a fruit
    // after
    if (fruit->prevFuit->nextFuit != NULL)
    {
      fruit->prevFuit->nextFuit = fruit->nextFuit;
    }
  }
  else
  {
    if (fruit->nextFuit != NULL)
    {
      fruit->nextFuit->prevFuit = NULL;
    }
  }

  if (fruit->nextFuit != NULL)
  {
    // reassign the prevFuit value of the following fruit if there is a
    // previous fruit
    if (fruit->nextFuit->prevFuit != NULL)
    {
      fruit->nextFuit->prevFuit = fruit->prevFuit;
    }
  }
  else
  {
    if (fruit->prevFuit != NULL)
    {
      fruit->prevFuit->nextFuit = NULL;
    }
  }
  free (fruit);
}

char *
getNameFruit (struct fruit *fruit)
{
  if (fruit == NULL)
  {
    return NULL;
  }
  return fruit->name;
}

int
getCountFruit (struct fruit *fruit)
{
  if (fruit == NULL)
  {
    return -1;
  }
  return fruit->count;
}

struct fruit *
getNextFruit (struct fruit *fruit)
{
  return fruit->nextFuit;
}
struct fruit *
getPrevFruit (struct fruit *fruit)
{
  return fruit->prevFuit;
}

struct fruit *
getFirstFruit (struct fruit *fruit)
{
  struct fruit *prevFuit = getPrevFruit (fruit);
  if (prevFuit != NULL)
  {
    getFirstFruit (prevFuit);
  }
  return fruit;
}

int
addCount (struct fruit *fruit, int addNumber)
{
  fruit->count += addNumber;
  if (fruit->count > maxFruit || addNumber < 0)
  {
    fruit->count -= addNumber;
    return -1;
  }
  return 0;
}

int
subCount (struct fruit *fruit, int subNumber)
{
  fruit->count -= subNumber;
  if (fruit->count < 0 || subNumber < 0)
  {
    fruit->count += subNumber;
    return -1;
  }
  return 0;
}

void
setNameFruit (struct fruit *fruit, char *name)
{
  if (strlen (name) > malloc_usable_size (fruit->name))
  {
    return;
  }
  strcpy (fruit->name, name);
}
