#include <stdio.h>
#include <signal.h>

void sigint_handler(int signo){
  int i;
  for(i =3 ; 0<i;i--){
    printf("%d seconds left\n",i );
    sleep(1);
  }
}

int main(void){
  struct sigaction act;
  act.sa_handler = sigint_handler;
  sigfillset(&act.sa_mask);
  sigaction(SIGINT,&act,NULL);
  while(1){
    printf("====action====\n");
    sleep(1);
  }
}
