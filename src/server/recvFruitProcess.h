#ifndef recvFruitProcess_H
#define recvFruitProcess_H
#include "findFruit.h"
#include "protopeach.h"
#include "server/responce.h"

void recvFruitProcess (int *sClient, char *buffer, struct fruit *fruits);
#endif /* end of include guard: recvFruitProcess_H */
