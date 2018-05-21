#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int ntimes =0;
void p_action(int signum){
  printf("Parent caught signal #%d\n",++ntimes );
}

void c_action(int signum){
  printf("Child caught signal\n",++nntimes );
}

int main(){

  pid_t pid,ppid;

  void p_action(int),c_action(int);

  static struct sigaction pact,cact;

  pact.sa_handler = p_action;

  sigaction(SIGUSR1,&pact,null);
  switch (pid =fork()) {
    case -1:
      perror("fork error");
      exit(1);
    case 0:
      cact.sa_handler = c_action;
      sigaction(SIGUSR1,&cact,NULL);
      ppid = getppid();
      for(;;){
        sleep(1);
        kill(ppid,SIGUSR1);
        pause();
      }
    default:
      for(;;){
        pause();
        sleep(1);
        kill(pid,SIGUSR1);
      }
  }
}
