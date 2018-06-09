#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#define MSGSIZE 6
char *msg1 = "hello";
char *msg2 = "bye!!";
void parent(int [][2]);
int child(int []);
int main(){
  int pip[3][2];
  int i;
  for (i = 0; i < 3; i++){
      if (pipe(pip[i]) == -1)
        perror("pipe call");
      switch (fork()){
        case -1: /* 오류 */
          perror("fork call");
        case 0: /* 자식 */
          child(pip[i]);
        }
  }
  parent(pip);
  exit (0);
}

void parent(int p[3][2]) /* 부모의 코드 */{
  char buf[MSGSIZE], ch;
  fd_set set, master;
  int i;
/* 모든 원하지 않는 화일 기술자를 닫는다 */
  for (i = 0; i < 3; i++)
    close (p[i][1]);
/* select 시스템 호출의 비트 마스크를 설정한다. */
  FD_ZERO (&master);
  FD_SET (0, &master);
  for (i = 0; i <3; i++)
    FD_SET (p[i][0], &master);
  while (set = master, select (p[2][0]+1, &set, NULL, NULL, NULL) > 0){
/* 표준 입력, 즉 화일 기술자 0에 있는 정보를 잊어버리면 안됨. */
    if (FD_ISSET(0, &set)){
      printf ("From standard input..."); read (0, &ch, 1); printf ("%c\n", ch);
    }
    for (i = 0; i < 3; i++){
      if (FD_ISSET(p[i][0], & set)){
        if (read(p[i][0], buf,MSGSIZE)>0){
          printf ("Message from child%d\n", i);
          printf ("MSG=%s\n",buf);
        }
      }
    }
    if (waitpid (-1, NULL,WNOHANG) == -1)
    return;
  }
}

int child(int p[2]){
  int count;
  close (p[0]);
  for (count = 0; count < 2; count++){
    write (p[1], msg1, MSGSIZE);
/* 임의의 시간 동안 중지한다. */
    sleep (getpid() % 4);
  }
/* 최종 메시지를 보낸다. */
  write (p[1], msg2, MSGSIZE);
  exit (0);
}
