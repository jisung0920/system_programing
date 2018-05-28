#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>

int main(void){
  int shmid, pid, *cal_num;
  void *shared_memory = (void *)0;

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
      }
  }
}
