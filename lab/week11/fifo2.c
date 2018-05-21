#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define MSGSIZ 63
char *fifo = "fifo";
main (int argc, char **argv)
{
  int fd;
  char msgbuf[MSGSIZ+1];

  if (mkfifo(fifo, 0666) == -1){
    if (errno != EEXIST)
      perror("receiver: mkfifo");
  }
  if((fd = open(fifo,O_RDWR))<0)
    perror("fifo open failed");
  for(;;){
    if(read(fd,msgbuf,MSGSIZ)<0)
      perror("message read failed");

    printf("message received : %s\n",msgbuf );
  }
}
