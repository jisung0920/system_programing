#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

static void sig_usr(int signum) {
  if(signum == SIGUSR1)
    printf("received SIGUSR1\n");
  else if(signum == SIGUSR2)
    printf("received SIGUSR2\n");
  else{
    fprintf(stderr, "received signal %d\n",signum);
    fflush(stderr);
    abort();
  }
  return;
  /* code */
}

int main(void){
  if(signal(SIGUSR1,sig_usr)==SIG_ERR){
    perror("can't catch siguer1");
    exit(1);
  }
  if(signal(SIGUSR2,sig_usr)==SIG_ERR){
    perror("can't catch siguer2");
    exit(1);
  }
  for(;;)
    pause();
}
