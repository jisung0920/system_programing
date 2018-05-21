#include <stdio.h>
#include <stdlib.h>

void main(void){
  printf("Home direcotry is %s\n",getenv("HOME") );
  putenv("HOME=/");
  printf("New Home direcotry is %s\n",getenv("HOME") );
}
