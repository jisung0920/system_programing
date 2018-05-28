#include <stdio.h>
#include <signal.h>

void catchint(int signo){
  printf("\nCATCH INT: signo=%d\n", signo);
  printf("CATCHINT: returnning \n\n" );
}

main(){
  static struct sigaction act;
  act.sa_handler = catchint;
  // act.sa_handler = SIG_IGN;
  sigfillset(&(act.sa_mask));
  sigaction(SIGINT,&act,NULL);
  printf("sleep call #1\n" );
  sleep(1);
  printf("sleep call #2\n" );
  sleep(1);
  printf("sleep call #3\n" );
  sleep(1);
  printf("sleep call #4\n" );
  sleep(1);
  printf("Exiting\n" );
  exit(0);
}
