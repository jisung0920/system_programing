#include <stdio.h>
#include <sys/types.h>//
#include <signal.h>
#include <stdlib.h>//

int pid;
static char *chdargv[] = {"p1","p2",(char*)0};
static char *chdenv[4];

int main(int argc, char *argv[]){
  int i,cpid1,cpid2,cpid3;
  void wakeup(int),handler(int),trapper(int),parent(int);

  if(!(cpid1 = fork())){
    pid = cpid1 = getpid();
    printf("\nCPID1 = %d\n");
    for(i=1;i<NSIG;i++)
      signal(i,SIG_IGN);
    signal(SIGINT,handler);
    signal(SIGALRM,wakeup);
    alarm((unsigned)2);
    for(;;)
      pause();
    printf("--CPID1 (%d) terminates\n",cpid2 );////
    exit(0);
  }

  else{
    if(!(cpid2 = fork())){
        pid = cpid2 = getpid();
        printf("\n\tCPID2 = %d\n",cpid2);
        for(i=1; i<NSIG; i++)
          signal(i,trapper);
        pause();
        printf("--CPID2 (%d) terminates\n",cpid2);
        exit(0);
    }
    else{
      if(!(cpid3 = fork())){
        pid = cpid3 = getpid();
        printf("\n\t\tCPID3 = %d \n",cpid3 );
        signal(SIGUSR2, trapper);

        chdenv[0] = "HOME=here";
        chdenv[1] = "PATH=/bin";
        chdenv[2] = "MAILX=/usr/lib/xxx";
        chdenv[3] = (char*)0;
        pause();
        printf("--CPID3 (%d) terminates\n",cpid3 );
        exit(0);
      }

    pid = getpid();
    sleep(3);
    printf("\nThis is parent process\n",pid );

    for(i=1;i<NSIG;i++)
      signal(i,parent);
    printf("\n\tSend SIGBUS(%d) to CPID1 (%d)\n",SIGBUS,cpid1);
    kill(cpid1,SIGBUS);
    printf("\n\tSend SIGINT(%d) to CPID1 (%d)\n",SIGINT,cpid1);
    kill(cpid1,SIGINT);
    printf("\n\tSend SIGBUS(%d) to CPID2 (%d)\n",SIGBUS,cpid2);
    kill(cpid2,SIGBUS);
    printf("\n\tSend SIGTERM(%d) to CPID2 (%d)\n",SIGTERM,cpid2);
    kill(cpid2,SIGTERM);
    printf("\n\tSend SIGUSR1(%d) to CPID2 (%d)\n",SIGUSR1,cpid2);
    kill(cpid2,SIGUSR1);
    printf("\n\tSend SIGUSR2(%d) to CPID3 (%d)\n",SIGUSR2,cpid3);
    kill(cpid3,SIGUSR2);

    wait((int*)0);

    }
   }
   return (0);
}

void wakeup(int dummy){
  printf("\n1 (pid = %d) am up now\n", pid);
}

void handler(int dummy){
  printf("\n1 (pid = %d) got an interrupt; will continue\n", pid);
}

void trapper(int i){
  signal(i, trapper);
  if(i==SIGUSR1){
    printf("\n\tGot SIGUSR1(%d); process(%d) will terminate\n",i,pid);
    exit(2);
  }
  else{
    if(i==SIGUSR2){
      printf("\n\t\t(%d) got SIGUSR2(%d); execs a new program\n",i,pid);
      execve("./sigexec",chdargv,chdenv);
      perror("\nTHIS LINE SHOULDN'T BE HERE\n");
    }
    else
      printf("\n\tGot a signal(%d); process(%d) continues\n",i,pid);
  }
}

void parent(int sig){
  printf("\nSignal(%d) recevied by parent (%d)\n",sig,pid);
}
