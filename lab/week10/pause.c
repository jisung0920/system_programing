#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int num){
  printf("sigint occur\n");
}

int main(void){
  printf("hello world\n" );
  signal(SIGINT,sig_handler);
  pause();
  printf("Interrupt\n" );
}
