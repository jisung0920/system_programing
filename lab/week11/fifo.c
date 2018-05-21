#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define MSGSIZ 63
char *fifo = "fifo";
int main (int argc, char **argv)
{
  int fd, j, nwrite;
  char msgbuf[MSGSIZ+1];
  if (argc < 2){
    fprintf (stderr, "Usage: sendmessage msg ... \n");
    exit(1);
  }
  if ((fd = open(fifo, O_WRONLY | O_NONBLOCK)) < 0)
    perror ("fifo open failed");

  for ( j = 1; j < argc; j++){
    if (strlen(argv[j]) > MSGSIZ){
      fprintf (stderr, "message too long %s\n", argv[j]);
        continue;
      }
    strcpy (msgbuf, argv[j]);
    if ((nwrite = write (fd, msgbuf, MSGSIZ+1)) == -1)
      perror ("message write failed");
  }
  exit (0);
}
