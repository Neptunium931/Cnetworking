#include "server/matchDomain.h"
#include <pcre.h>
#include <stdio.h>
#include <string.h>

bool
matchDomain (char *domain)
{
  const char *pattern = "(?=^.{4,253}\\.?)(^((?!-)[a-zA-Z0-9-]{1,63}(?<!-)\\.)"
                        "+[a-zA-Z]{2,63}\\.?$)";

  const char *error;
  int erroffset;
  int findRexCount;

  pcre *rex = pcre_compile (pattern, 0, &error, &erroffset, NULL);
  if (rex == NULL)
  {
    fprintf (stderr, "PCRE compilation failed at offset %d: %s\n", erroffset,
             error);
    return false; // Pattern compilation failed
  }

  findRexCount = pcre_exec (rex, NULL, domain, strlen (domain), 0, 0, NULL, 0);
  pcre_free (rex);

  if (findRexCount < 0)
  {
    return false; // String does not match the pattern
  }
  return true; // String matches the pattern
}
