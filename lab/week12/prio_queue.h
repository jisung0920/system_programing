#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/stat.h>
#include <error.h>

#define MSGQKEY (key_t)0111
#define PERMISSION 0777
#define MAXLENGTH 100
#define MAXPRIO 20

struct msg_buf{
  long mtype;
  char mtext[MAXLENGTH+1];
};
