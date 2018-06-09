#include <stdio.h>
#include <signal.h>

main(){
  sigset_t set1,set2;
  sigfillset(&set1);
  sigdelset(&set2,SIGINT);
  sigdelset(&set2,SIGQUIT);

  sigprocmask(SIG_SETMASK,&set1,NULL);

  sigprocmask(SIG_UNBLOCK,&set2,NULL);
  
  sigprocmask(SIG_UNBLOCK,&set1,NULL);
}
