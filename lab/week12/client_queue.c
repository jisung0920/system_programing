#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "prio_queue.h"

int msg_put(int msgq_id, char *request, int prio){
  int len;
  struct msg_buf req_msg;
  if((len=strlen(request))>MAXLENGTH){
    perror("[c]request name too long");
    return -1;
  }
  req_msg.mtype = (long)prio;
  strncpy(req_msg.mtext,request,MAXLENGTH);

  if(msgsnd(msgq_id,&req_msg,len,0)==-1){
    perror("[c]message send failed");
    return -1;
  }
  else
    return 0;

}

int main(int argc, char* argv[]){
  int msg_prio,msgq_id,running = 1;
  char request[MAXLENGTH+1];

  msgq_id = msgget(MSGQKEY,PERMISSION|IPC_CREAT);

  printf("%d\n",msgq_id );
  if(msgq_id == -1){
    perror("[c]msg queue create failed");
    exit(1);
  }
  while(running){
    strncpy(request, argv[1],MAXLENGTH);
    printf("[c]argv[1]:%s\n",request );
    msg_prio = atoi(argv[2]);
    printf("[c]argv[2]:%d\n",msg_prio );

    if(msg_put(msgq_id,request,msg_prio)<0){
      perror("[c]msg send failed");
      exit(1);
    }
    if(!strcmp(request,"end")){
      printf("[c]>>>>>>>>>>NULL<<<<<<<<\n" );
      strcpy(request,"end");
      msg_prio = MAXPRIO;

      if(msg_put(msgq_id,request,msg_prio)<0){
        perror("[c]msg send failed");
        exit(1);
      }
    }
    running = 0;

  }
  exit(0);

}
