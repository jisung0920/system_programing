#include <stdio.h>
#include <signal.h>

struct sigaction act_new;
struct sigaction act_old;

void sigint_handler(int signo){
  printf("Press the CTRL-C key.\n");
  printf("Press again to exit.\n");
  sigaction(SIGINT,%act_old,%act_new);
}

int main(void){
  act_new.sa_handler = sigint_handler;
  
}
