#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

struct NanoSenderSession
{
  /* data */
  int sock;
  char* url;
  void (*sendMessage)(struct NanoSenderSession* this,char *msg);
  int (*connect)(struct NanoSenderSession* this);
  int (*disconnect)(struct NanoSenderSession* this);
};

struct NanoSenderSession* newNanoSenderSession(char* url);