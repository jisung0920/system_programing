#include <stdio.h>
#include <signal.h>

int main(void){
  sigset_t mask1,mask2;

  sigemptyset(&mask1);

  sigaddset(&mask1,SIGINT);
  sigaddset(&mask1,SIGQUIT);

  sigfillset(&mask2);
  sigdelset(&mask2,SIGCHLD);
  
}
