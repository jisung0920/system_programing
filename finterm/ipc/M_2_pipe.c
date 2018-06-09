#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

#define NPNAM "fifo"
#define BSIZ BUFSIZ
#define ERR -1
#define EMPTY 0
char *mesg[] = {"yesterday", "today", "tomorrow"};

int main(void){
  int npid;
  int npcreate(char *, int),npread(int, char *), npwrite(int, int, char *[]);
  if ((npcreate(NPNAM, 0664)) == ERR) /* to create a fifo */
    nperror(1, "Can't create named pipe\n");
  if (fork() == 0) { /* writer */
    if ((npid = open(NPNAM, O_WRONLY)) == ERR)
      nperror(2, "Can't open named pipe\n");
    if (npwrite(npid, sizeof(mesg)/sizeof(char *), mesg) == ERR)
      nperror(3, "Can't write named pipe\n");
    exit(0);
  }
  if (fork() == 0) { /* reader */
    char rbuf[BSIZ];
    if ((npid = open(NPNAM, O_RDONLY)) == ERR)
    nperror(4, "Can't open named pipe\n");
    while(1) {
      switch(npread(npid, rbuf)) {
        case ERR:
          nperror(5, "Can't read named pipe\n");
        case EMPTY:
          break;
        default:
          printf("Got: %s\n", rbuf);
          continue;
        }
      break;
    }
    exit(0);
  }
  wait((int *)0);
  return(0);
} /* main */
int npcreate(char *npnam, int perms){
  umask(0); /* permissions to be determined by perms */
  return(mkfifo(npnam, perms)); /* either one of these two works */
/* return(mknod(npnam, 010000 | perms)); 010000: fifo special */
} /* npcreat */
int nperror(int errno, char *errmsg){
  write(2, errmsg, strlen(errmsg));
  exit(errno);
} /* nperror */
int npread(int npid, char *rbuf){
  return(read(npid, rbuf, BSIZ));
} /* npread */
int npwrite(int npid, int siz, char *mesg[]){
  int i;
  for (i = 0; i < siz; i++) {
    if (write(npid, mesg[i], strlen(mesg[i])+1) == ERR)
      return(ERR);
    sleep(1);
  } /* write out one mesg at a time */
  return(0);
} /* npwrite */
