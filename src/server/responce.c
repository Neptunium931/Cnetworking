#include "server/responce.h"
#include <stdio.h>
#include <stdlib.h>

void
heloResponse (const int *sClient, enum response heloResponseChoise)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  char *errorCode = malloc (sizeof (char) * 3);
  strcpy (buffer, "HELO");
  switch (heloResponseChoise)
  {
  case OK:
    strcat (buffer, " OK");
    break;
  case NOK:
    strcat (buffer, " NOK ");
    sprintf (errorCode, "%d", SERVER_REFUSE_HELO);
    strcat (buffer, errorCode);
    break;
  default:
    break;
  }
  free (errorCode);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
}

void
unknownResponse (const int *sClient)
{
  char *buffer = calloc (1, sizeof (char) * 3);
  sprintf (buffer, "%02d", UNKNOWN);
  sendDataToClient (*sClient, buffer, 3);
  free (buffer);
}

void
sendFruitResponceError (const int *sClient, enum Errorcodes errorCode)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  char *errorCodeBuffer = malloc (sizeof (char) * 3);
  strcpy (buffer, "sendfruit NOK ");
  sprintf (errorCodeBuffer, "%02d", errorCode);
  strcat (buffer, errorCodeBuffer);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
  free (errorCodeBuffer);
}
void
sendFruitResponce (const int *sClient)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  strcpy (buffer, "sendfruit");
  strcat (buffer, " OK");
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
}

void
recvFruitResponceError (const int *sClient, enum Errorcodes errorCode)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  char *errorCodeBuffer = malloc (sizeof (char) * 3);
  strcpy (buffer, "recvfruit NOK ");
  sprintf (errorCodeBuffer, "%02d", errorCode);
  strcat (buffer, errorCodeBuffer);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
  free (errorCodeBuffer);
}
void
recvFruitResponce (const int *sClient, int numberFruit)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  char *numberBuffer = malloc (sizeof (char) * 3);
  strcpy (buffer, "recvfruit");
  strcat (buffer, " OK ");
  sprintf (numberBuffer, "%d", numberFruit);
  strcat (buffer, numberBuffer);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
  free (numberBuffer);
}

void
changeFruitResponceError (const int *sClient, enum Errorcodes errorCode)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  char *errorCodeBuffer = malloc (sizeof (char) * 3);
  strcpy (buffer, "chngfruit NOK ");
  sprintf (errorCodeBuffer, "%02d", errorCode);
  strcat (buffer, errorCodeBuffer);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
  free (errorCodeBuffer);
}
void
changeFruitResponce (const int *sClient, char *newName)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  printf ("newName response : %s\n", newName);
  strcpy (buffer, "chngfruit OK ");
  strcat (buffer, newName);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
}

void
howmanyResponceError (const int *sClient, enum Errorcodes errorCode)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  char *errorCodeBuffer = malloc (sizeof (char) * 3);
  strcpy (buffer, "howmany NOK ");
  sprintf (errorCodeBuffer, "%02d", errorCode);
  strcat (buffer, errorCodeBuffer);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
  free (errorCodeBuffer);
}
void
howmanyResponce (const int *sClient, int count)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  char *numberBuffer = malloc (sizeof (char) * 3);
  strcpy (buffer, "howmany OK ");
  sprintf (numberBuffer, "%d", count);
  strcat (buffer, numberBuffer);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
  free (numberBuffer);
}
