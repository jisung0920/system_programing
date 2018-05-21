#include <stdio.h>
#include <stdlib.h>

#define CMDLEN 80

void main(void){
  char cmdstr[CMDLEN];

  printf("Enter command to run : ");
  fflush(stdout);
  gets(cmdstr);
  system(cmdstr);
}
