#include "matchString.h"

int
matchString (char *stringRef, char *stringCmp)
{
  return ((*stringRef == 0 && *stringCmp == 0)                        ? (1)
          : (*stringRef != 0 && *stringCmp == 0)                      ? (0)
          : (*stringRef == 0 && *stringCmp != 0 && *stringCmp != '*') ? (0)
          : (*stringRef == 0 && *stringCmp != 0 && *stringCmp == '*')
              ? (matchString (stringRef, stringCmp + 1))
          : (*stringRef != 0 && *stringCmp != 0 && *stringCmp == '*')
              ? (matchString (stringRef, stringCmp + 1)
                 || matchString (stringRef + 1, stringCmp))
          : (*stringRef != 0 && *stringCmp != 0 && *stringCmp != '*')
              ? (*stringRef != *stringCmp)
                    ? (0)
                    : (matchString (stringRef + 1, stringCmp + 1))
              : (matchString (stringRef + 1, stringCmp + 1)));
}
