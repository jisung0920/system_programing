#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

static void sig_quit(int);

int main(void){
  sigset_t newmask, oldmask, pendmask;

  if(signal(SIGQUIT,sig_quit)==SIG_ERR){
    perror("cant catch sigquit");
    exit(1);
  }
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGQUIT);

  sigprocmask(SIG_BLOCK,&newmask,&oldmask);

  sigismember(&pendmask,SIGQUIT);

  sigprocmask(SIG_SETMASK,&oldmask,NULL);

  printf("SIGQUIT unblocked\n");

  sleep(5);

  exit(0);
}

static void sig_quit(int signo){
  printf("caught SIGQUIT\n");
  if(signal(SIGQUIT,SIG_DFL)==SIG_ERR){
    perror("cant reset SIGQUIT");
    exit(1);
  }
  return;
}
