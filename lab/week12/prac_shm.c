#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int shmid;
int flag;
void rmshm(int s){
  // struct shmid_ds *buf;

  shmctl(shmid, IPC_RMID,NULL );
  printf("remove shared_memory\n");

  printf("child exit\n" );
  flag =-1;
  exit(1);

}





int main(void){
  int pid, *cal_num;
  flag =1;
  void *shared_memory = (void *)0;

  signal(SIGINT,SIG_IGN);
  // static struct sigaction act;
  // act.sa_handler = rmshm;
  // sigaction(SIGINT,&act,NULL);

  shmid = shmget((key_t)1234,sizeof(int),0666|IPC_CREAT);

  if(shmid==-1){
    perror("shmget failed:");
    exit(0);
  }
  shared_memory = shmat(shmid,(void *)0,0);
  if(shared_memory == (void *)-1){
    perror("shmat failed: ");
    exit(0);
  }

  cal_num = (int *)shared_memory;
  if((pid=fork())==0){
    signal(SIGINT,rmshm);
    *cal_num = 1;
    while(1){
      *cal_num += 1;
      printf("[CHILD] %d\n",*cal_num );
      sleep(1);
    }
  }else if(pid>0){
      while(1){
        sleep(1);
        printf("[PARENT] %d\n",*cal_num );

        if(waitpid(pid,NULL,WNOHANG)!=0){
          printf("PARENT exit\n" );
          exit(1);
        }
        // if(shmget(shmid,30,IPC_EXCL)==-1){
        //   printf("no shared_memory\n" );
        //   exit(1);
        // }
      }
  }
}
