#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void myalarm(){
  printf("\nding dong dang\n" );
}

int main(void){
  int i=0;
  printf("alarm setting\n" );
  signal(SIGALRM,myalarm);
  alarm(1);
  while(i<5){
    printf("ok\n" );
    pause();
    alarm(2);
    i++;
  }
}
