#include <stdio.h>
#include "3_q.h"
int main(int argc, char *argv[]){

  int priority;

  if (argc != 3) {
    fprintf(stderr, "usage: %s objname priority\n", argv[0]);
    exit(1);
  }

  if ((priority = atoi(argv[2])) <= 0 || priority > MAXPRIOR) {
    fprintf(stderr, "invalid priority");
    exit(2);
  }

  if (enter(argv[1], priority) < 0) {
    fprintf(stderr, "enter failure");
    exit(3);
  }
  exit(0);
}
