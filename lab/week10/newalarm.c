#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

void myalarm(){
  printf("\nding dong dang\n" );
}
void newalarm(int secs){
  sleep(secs);
  pid_t pid,ppid;

  switch (pid =fork()) {
    case -1:
      perror("fork error");
      exit(1);
    case 0:
      ppid = getppid();
      for(;;){
        kill(ppid,SIGALRM);
        raise(SIGQUIT);
      }
  }
}
int main(void){
  int i=0;
  printf("alarm setting\n" );
  signal(SIGALRM,myalarm);
  newalarm(1);
  while(i<5){
    printf("ok\n" );
    pause();
    newalarm(2);
    i++;
  }
}
