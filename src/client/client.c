#include "client/client.h"
#include "client/help.h"
#include "client/matchIpv4.h"
#include "client/socket.h"
#include "matchString.h"
#include "strip.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HISTORY_ENV_NAME "CNETWORKING_HISTORY"
#define DEFAULT_HISTORY_FILE ".Cnetworking_history"

void
initHistory (void)
{
  getVarEnv ((char *)HISTORY_ENV_NAME);
  getVarEnv ((char *)"HOME");
}

char *
getVarEnv (char *name)
{
  char **env_ptr = environ;
  char *varName, *value, *copyEnv;

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

int
main (int argc, char *argv[])
{
  char *input;
  bool run = true;
  struct server *serverInfo;
  initHistory ();

  using_history ();
  read_history (DEFAULT_HISTORY_FILE);
  serverInfo = calloc (1, sizeof (struct server));

  while (run == true)
  {
    char *rest, *token, *copyInput;
    input = readline (">> ");
    // strip (input);
    copyInput = strdup (input);
    rest = copyInput;
    token = strsep (&rest, " ");
    if (input == NULL || matchString (input, (char *)"exit"))
    {
      printf ("\nAu revoir !\n");
      run = false;
      free (input);
      free (copyInput);
      continue;
    }
    else if (strlen (input) == 0)
    {
      free (input);
      free (copyInput);
      continue;
    }
#define MAGIC_HELP "help"
    else if (matchString (token, (char *)MAGIC_HELP))
    {
      printHelp ();
    }
#define MAGIC_DEFINE_IP "set_remote"
    else if (matchString (token, (char *)MAGIC_DEFINE_IP))
    {
      if (!matchIpv4 (rest))
      {
        printf ("'%s' is not ipv4 valide\n", rest);
        free (input);
        free (copyInput);
        continue;
      }
      strcpy (serverInfo->serverIpString, rest);
      serverInfo->serverIp = inet_addr (serverInfo->serverIpString);
      printf ("%s\n", serverInfo->serverIpString);
    }
    add_history (input);
    write_history (DEFAULT_HISTORY_FILE);

    printf ("Commande saisie : #%s#\n", input);

    free (input);
    free (copyInput);
  }
  free (serverInfo);
  return 0;
}
