#include "client/matchIpv4.h"
#include <pcre.h>
#include <stdio.h>
#include <string.h>

bool
matchIpv4 (char *domain)
{
  const char *pattern
      = "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?["
        "0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-"
        "4][0-9]|[01]?[0-9][0-9]?$)";

  pcre *rex;
  const char *error;
  int erroffset;
  int findRexCount;

  rex = pcre_compile (pattern, 0, &error, &erroffset, NULL);
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
