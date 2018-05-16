#include <stdio.h>
extern char **environ;

int main(int argc, char *argv[]){
  char **env;
  int i;
  printf("\nParameters are : \n" );
  for(i=0;i<argc;i++)//
    printf("%2d:%s\n",i,argv[i] );
  printf("\nEnviroment variable are : \n" );
  for(env = environ;*env !=(char*)0;env++)
    printf("%s\n",*env );
  return (0);
}
