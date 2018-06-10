#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern int errno;
#define SEMPERM 0600
#define TRUE 1
#define FALSE 0
union semun{
  int val;
  struct semid_ds *buf;
  ushort *array;
} arg;
/* function prototypes */
int initsem(key_t semkey);
int p(int semid);
int v(int semid);
