#include "6_share_ex.h"
void main(void)
{
  int semid, pid;
  struct databuf *buf1, *buf2;
  /*initialize semaphore set*/
  semid = getsem();
  /*create and attach shared memory segments*/
  getseg(&buf1, &buf2);
  switch (pid = fork()) {
    case -1:
      perror("fork");
      exit(1);
    case 0: /*child*/
      writer(semid, buf1, buf2);
      s_remove();
      break;
    default: /*parent*/
      reader(semid, buf1, buf2);
      break;
  }
  exit(0);
}
