#include "client/client.h"
#include "client/help.h"
#include "client/matchIpv4.h"
#include "client/socket.h"
#include "getVarEnv.h"
#include "matchString.h"
#include "strip.h"
#include <netinet/in.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define HISTORY_ENV_NAME "CNETWORKING_HISTORY"
#define DEFAULT_HISTORY_FILE ".Cnetworking_history"

void
initHistory (void)
{
  getVarEnv ((char *)HISTORY_ENV_NAME);
  getVarEnv ((char *)"HOME");
}

int
main (int argc, char *argv[])
{
  char *input;
  bool run = true;
  struct server *server;
  char *buffer;
  initHistory ();

  using_history ();
  read_history (DEFAULT_HISTORY_FILE);
  server = calloc (1, sizeof (struct server));
  server->servAddr = calloc (1, sizeof (struct sockaddr_in));

  buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  while (run == true)
  {
    char *rest;
    char *token;
    char *copyInput;
    input = readline (">> ");
    if (input == NULL || matchString (input, (char *)"exit"))
    {
      printf ("\nAu revoir !\n");
      run = false;
      free (input);
      continue;
    }
    if (strlen (input) == 0)
    {
      free (input);
      continue;
    }
    strip (input);
    copyInput = strdup (input);
    rest = copyInput;
    token = strsep (&rest, " ");
#define MAGIC_HELP "help"
    if (matchString (token, (char *)MAGIC_HELP))
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
      strcpy (server->serverIpString, rest);
      server->servAddr->sin_addr.s_addr = inet_addr (server->serverIpString);
      printf ("%s\n", server->serverIpString);
    }
    else if (server->servAddr->sin_addr.s_addr == 0)
    {
      puts ("not remote set");
      puts ("use : set_remote <serverIp>");
    }
#define MAGIC_DEFINE_PORT "set_port"
    else if (matchString (token, (char *)MAGIC_DEFINE_PORT))
    {
      server->servAddr->sin_port = htons (atoi (rest));
      printf ("%d\n", server->servAddr->sin_port);
    }
#define MAGIC_CONNECT "connect"
    else if (matchString (token, (char *)MAGIC_CONNECT))
    {
      server->s = socket (AF_INET, SOCK_STREAM, 0);
      server->servAddr->sin_family = AF_INET;
      if (connect (server->s, server->servAddr, sizeof (*server->servAddr)))
      {
        perror ("Error : connect");
      }
      else
      {
        server->connect = true;
      }
    }
    else if (!server->connect)
    {
      puts ("not connected");
      puts ("use : connect");
    }
#define MAGIC_SEND "send"
    else if (matchString (token, (char *)MAGIC_SEND))
    {
      memset (buffer, '\0', BUFFER_SIZE);
      printf ("rest %s\n", rest);
      strcpy (buffer, rest);
      send (server->s, buffer, strlen (buffer), 0);
    }
    printf ("rest %s\n", rest);
    add_history (input);
    write_history (DEFAULT_HISTORY_FILE);

    printf ("Commande saisie : #%s#\n", input);

    free (input);
    free (copyInput);
  }
  free (buffer);
  free (server->servAddr);
  free (server);
  return 0;
}
