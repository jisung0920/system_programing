#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MSGSIZ 63
char *fifo = "fifo";
int main (int argc, char **argv){

  int fd;
  char msgbuf[MSGSIZ+1];
  /* fifo가 이미 존재하지 않으면, 생성한다 */
  if (mkfifo(fifo, 0666) == -1){
    if (errno != EEXIST)
      perror ("receiver: mkfifo");
  }

  if ((fd = open(fifo, O_RDWR)) < 0)
    perror ("fifo open failed");
  /* 메시지를 받는다 */
  for(;;){
    if (read(fd, msgbuf, MSGSIZ+1) <0)
      perror ("message read failed");
    /*
    * 메시지를 프린트한다 ; 실제로는 보다 흥미 있는 일이 수행된다.
    */
    printf ("message received:%s\n", msgbuf);
  }
}
