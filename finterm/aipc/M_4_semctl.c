#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#define ERR -1
#define UNUSED 0
#define SEMMSL 25
/* for padding unused arguments */
/* default max # of sems in a set */
union semun {
int val;
struct semid_ds *buf;
ushort *array;
}
int main(int argc, char **argv){

  int i, cflag, semid, semval, semnum, nsems;

  struct semid_ds semun_buf;

  ushort semun_array[SEMMSL];

  void semerr(char *);

  union semun sems;

  if (!strcmp(argv[0], "setval"))
    cflag = 1;
  else if (!strcmp(argv[0], "getval"))
    cflag = 2;
  else if (!strcmp(argv[0], "setall"))
    cflag = 3;
  else if (!strcmp(argv[0], "getall"))
    cflag = 4;

  printf("\nPlease enter semid > ");

  scanf("%d", &semid);

  switch(cflag) {
    case 1:
    /* set one semaphore value */
      printf("\nPlease enter semaphore number > ", i);
      scanf("%d", &semnum);
      printf("\nPlease enter desired value for this semaphore > ", i);
      scanf("%d", &semval);
      sems.val = semval;
      if ((semctl(semid, semnum, SETVAL, sems)) == ERR)
        semerr("\nCan't initialize a semaphore value");
      break;

    case 2:
    /* get one semaphore value */
      printf("\nPlease enter semaphore number > ");
      scanf("%d", &semnum);
      if ((semval = semctl(semid, semnum, GETVAL, UNUSED)) == ERR)
        semerr("\nCan't get a semaphore value");
      printf("\nValue of semaphore %d = %d", semnum, semval);
      break;
    case 3:
      /* set values for all semaphores */
      sems.buf = &semun_buf;
      /* initialize the buf pointer */
      if ((semctl(semid, UNUSED, IPC_STAT, sems)) == ERR)
        semerr("\nCan't access semaphore set");
      nsems = sems.buf->sem_nsems; /* get num of semaphores */
      sems.array = semun_array; /* initialize the array pointer */

      for (i = 0; i < nsems; i++) {
        printf("\nPlease enter value for semaphore %d > ", i);
        scanf("%d", &semval);
        sems.array[i] = semval;
      } /* for */

      if ((semctl(semid, UNUSED, SETALL, sems)) == ERR)
        semerr("\nCan't inintialize a semaphore set");
    case 4:
    /* get all semaphores values */
      sems.buf = &semun_buf;
      /* initialize the buf pointer */
      if ((semctl(semid, UNUSED, IPC_STAT, sems)) == ERR)
        semerr("\nCan't access semaphore set");

      nsems = sems.buf->sem_nsems; /* get num of semaphores */
      sems.array = semun_array; /* initialize the array pointer */
      semctl(semid, UNUSED, GETALL, sems);
      for (i = 0; i < nsems; i++)
        printf("Value of semaphore %d = %d\n", i, sems.array[i]);
      break;
  } /* switch */
  exit(0);
} /* main */
void semerr(char *mesg){
  fprintf(stderr, mesg);
  fprintf(stderr, ": errno = %d\n", errno);
  exit(ERR);
} /* semerr */
