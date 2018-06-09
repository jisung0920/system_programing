#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int join (char *com1[], char *com2[]);

int main(){
  char *one[4] = {"ls", "-l", "/usr/lib", NULL};
  char *two[3] = {"grep", "∧d", NULL};
  int ret;
  ret = join (one, two);
  printf ("join returned %d\n", ret);
  exit (0);
}

int join (char *com1[], char *com2[]){
  int p[2], status;
/* 명령을 수행할 자식을 생성한다. */
  switch (fork()){
      case -1: /* 오류 */
        perror ("1st fork call in join");
      case 0: /* 자식 */
        break;
      default: /* 부모 */
        wait(&status);
        return (status);
    }
/* 루틴의 나머지 부분으로 자식에 의해 수행된다. */
/* 파이프를 만든다. */
  if (pipe(p) == -1)
    perror ("pipe call in join");
  switch (fork()){
    case -1:
/* 오류 */
      perror ("2nd fork call in join");
    case 0:
/* 쓰는 프로세스 */
      fprintf(stdout, "%s\n","standard out fd OK!" );
      dup2 (p[1],stdout); /* 표준 출력이 파이프로 가게 한다. */
      close (p[0]); /* 화일 기술자를 절약한다. */
      close (p[1]);
      execvp (com1[0], com1);
/* execvp가 복귀하면, 오류가 발생한 것임. */
      perror("1st execvp call in join");
    default:
/* 읽는 프로세스 */
      dup2(p[0], stdin); /* 표준 입력이 파이프로부터 오게 한다 */
      close (p[0]);
      close (p[1]);
      execvp (com2[0], com2);
      perror ("2nd execvp call in join");
    }
}
