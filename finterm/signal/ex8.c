#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

void pr_mask(const char *str){
  sigset_t sigset;
  if(sigprocmask(0,NULL,&sigset)<0){
    perror("SIGPROCMASK error");
    exit(1);
  }
  printf("%s\n",str );

  if(sigismember(&sigset,SIGINT))
    printf("SIGINT" );
  if(sigismember(&sigset,SIGQUIT))
    printf("SIGQUIT" );

  printf(" \n" );
}
