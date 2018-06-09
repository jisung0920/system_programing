#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void g_exit(int s){
  unlink("tempfile");
  fprintf(stderr, "interrupt - exiting\n" );
  exit(1);
}

main(){
  static struct sigaction act;
  act.sa_handler = g_exit;
  sigaction(SIGINT,&act,NULL);
}
