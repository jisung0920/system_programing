#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void catchint(int signum){
  printf("\nCATCHINT: signum = %d\n",signum);
  printf("CATCHINT: returning\n\n" );
}

int main(){

  static struct sigaction act;
  act.sa_handler = catchint;
  sigfillset(&(act.sa_mask));
  sigaction(SIGINT,&act,NULL);

  printf("sleep call #1\n");
  sleep(1);
  printf("sleep call #2\n");
  sleep(1);
  printf("sleep call #3\n");
  sleep(1);
  printf("sleep call #4\n");
  sleep(1);
  printf("Exiting\n");
  exit(0);
}
