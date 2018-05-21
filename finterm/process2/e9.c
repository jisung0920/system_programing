#include <stdio.h>

void main(int argc, char *argv[],char *envp[]){
  int i;
  extern char **environ;

  printf("from arg envp\n");
  for(i=0;envp[i];i++)
    puts(envp[i]);
  printf("\n\nFrom global variable environ\n" );
  for (i = 0;environ[i];i++)
    puts(environ[i]);
}
