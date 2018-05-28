#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "prio_queue.h"

int msg_service(int msgq_id){
  int len;
  struct msg_buf req_msg;
  if((len = msgrcv(msgq_id,&req_msg,MAXLENGTH,(-1*MAXPRIO),MSG_NOERROR))==-1){
    perror("[s]message rcv failed");
    return -1;
  }
  else{
    req_msg.mtext[len] = '\0';
    printf("[s]===>%s\n",req_msg.mtext );

    if(strcmp(req_msg.mtext,"end")==0){
      printf("\n[s]!!!!!!\n");
      return -1;
    }
    else{
      printf("\n[s]priority: %ld name:%s\n",req_msg.mtype ,req_msg.mtext);
      return 0;
    }
  }

}

int main(void){
  int msg_prio,msgq_id,re_value,running = 1;

  msgq_id = msgget(MSGQKEY,PERMISSION|IPC_CREAT);

  if(msgq_id == -1){
    perror("[s]msg queue create failed");
    exit(1);
  }
  while(running){
    re_value = msg_service(msgq_id);

    if(re_value<0){
      perror("[s]msg service failed");
      exit(1);
    }
    else if(re_value==0)
      running = 0;
  }
  if(msgctl(msgq_id,IPC_RMID,0)==-1){
    perror("[s]msgq remove failed");
    exit(1);
  }
}
