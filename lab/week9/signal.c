#include <stdio.h>
#include <signal.h>

int main(void){

    sigset_t mask1, mask2;

    sigemptyset(&mask1);

    sigaddset(&mask1,SIGINT);
    sigaddset(&mask1,SIGQUIT);

    sigfillset(&mask2);

    sigdelset(&mask2,SIGCHLD);

    if(sigismember(&mask1,SIGINT))
      printf("SIGINT is MEMBER of MASK1\n" );
    else
      printf("SIGINT is not MEMBER of MASK1");

    if(sigismember(&mask2,SIGCHLD))
      printf("SIGCHLD is MEMBER of MASK2\n" );
    else
      printf("SIGCHLD is not MEMBER of MASK2\n" );

    return 0;
}
