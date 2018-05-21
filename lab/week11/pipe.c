#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGSIZE 16

char *msg1 = "Hello world #1";
char *msg3 = "Hello world #3";
char *msg2 = "Hello world #2";

int main(int argc, char const *argv[]) {
  char inbuf[MSGSIZE];
  int p[2], j;
  if(pipe(p)==-1){
    perror("pipecall");
    exit(1);
  }
  write(p[1],msg1,MSGSIZE);
  write(p[1],msg2,MSGSIZE);
  write(p[1],msg3,MSGSIZE);

  for(j=0;j<3;j++){
    read(p[0],inbuf,MSGSIZE);
    printf("%s\n",inbuf);
  }
  exit(0);
}
