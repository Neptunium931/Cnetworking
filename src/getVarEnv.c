#include "getVarEnv.h"
#include "matchString.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *
getVarEnv (char *name)
{
  char **env_ptr = environ;
  char *varName;
  char *value;
  char *copyEnv;

  while (*env_ptr != NULL)
  {
    copyEnv = strdup (*env_ptr);
    value = copyEnv;
    varName = strsep (&value, "=");
    if (varName == NULL || value == NULL)
    {
      free (copyEnv);
      continue;
    }
    if (matchString (varName, name))
    {
      printf ("%s\n", *env_ptr);
    }
    env_ptr++;
    free (copyEnv);
  }
  return NULL;
}
