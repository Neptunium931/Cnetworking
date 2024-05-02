#include "client/help.h"
#include <stdio.h>

void
printHelp (void)
{
  puts ("define add of server : set_remote <ipv4>");
  puts ("define port : set_port <port tcp>");
  puts ("connect to the server : connect");
  puts ("send data to the server : send <payload>");
  puts ("payload available : ");
  puts ("- helo <domain>");
  puts ("- sendfruit <fruit> <count>");
  puts ("- recvfruit <fruit>");
  puts ("- chngfruit <fruit> <new fruit>");
  puts ("- howmany <fruit>");
}
