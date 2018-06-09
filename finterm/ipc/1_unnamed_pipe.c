#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MSGSIZE 16
static char *msg1 = "hello, world #1";
static char *msg2 = "hello, world #2";
static char *msg3 = "hello, world #3";

int main(void){
  char buf[MSGSIZE];
  int fd[2], i, pid;
/* open unnamed pipe */
  if (pipe(fd) < 0) {
    perror("pipe call");
    exit(1);
  }
  if ((pid = fork()) < 0) {
    perror("fork call");
    exit(2);
  }
/* if child, then close read file
* descriptor and write down pipe
*/
  if (pid == 0) {
      close(fd[0]);
        write(fd[1], msg1, MSGSIZE);
        write(fd[1], msg2, MSGSIZE);
        write(fd[1], msg3, MSGSIZE);
  }
/* if parent, then close write file
* descriptor and read from pipe
*/
  else {
    close(fd[1]);
    for (i = 0; i < 3; i++) {
      read(fd[0], buf, MSGSIZE);
      printf("%s\n", buf);
    }
    wait(NULL);
  }
  exit(0);
}
