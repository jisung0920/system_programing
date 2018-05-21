#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int count;

void catch_sigint(int signum){
  printf("\n(count = %d) CTRL -C pressed! \n",count);
  return ;
}

int main(int argc, char* argv[]){
  sigset_t masksets;
  sigfillset(&masksets);
  signal(SIGINT, catch_sigint);

  for(count = 0 ; count <30; count++){
    if(count<10)
      sigprocmask(SIG_SETMASK, &masksets, NULL);
      else if(count>=10 && count <20)
      sigprocmask(SIG_UNBLOCK, &masksets, NULL);
      else if(count>= 20){
        sigemptyset(&masksets);
        sigaddset(&masksets, SIGINT);
        sigpromask(SIG_BLOCK, &masksets, NULL);
      }

      printf("test %d\n",count );
      sleep(1);
    }
    return 0;
}
