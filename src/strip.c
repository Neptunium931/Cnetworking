#include "strip.h"
#include <string.h>

void
strip (char *string)
{
  int lenString = strlen (string) - 1;
  if (string[lenString] == ' ' || string[lenString] == '\n')
  {
    string[lenString] = '\0';
    strip (string);
  }
}
