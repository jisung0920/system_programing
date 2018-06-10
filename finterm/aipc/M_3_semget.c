#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#define ERR -1
#define UNUSED 0
#define SEMMSL 25
#define SEMKEY "semkey"
#define SEMID 'a'
#define semkey(x, y) (key_t)ftok(x, y)
int main(int argc, char **argv)
{
  int semid, nsems;
  key_t key;
  if ((key = semkey(SEMKEY, SEMID)) == ERR) { /* needs every time */
    printf("\nCan't assemble a key: "); /* key is used to generate semid*/
    printf("Error no = %d", errno);
    exit(ERR);
  } /* key better be unique */

  if (!strcmp(argv[0], "csem")) {
  /* to create a semaphore set */
    printf("\nPlease enter number of semaphores desired > ");
    scanf("%d", &nsems);
    if ((semid =semget(key, nsems, IPC_CREAT | IPC_EXCL | 0666)) == ERR){
      printf("\nCan't create a semaphore set: ");
      printf("Error no = %d\n", errno);
      exit(ERR);
    }
    printf("\nA semaphore set with ID = %d is created OK\n", semid);
  }

  else if (!strcmp(argv[0], "semid")) {
  /* get semaphore set ID */
    if ((semid = semget(key, UNUSED, UNUSED)) == ERR) {
      printf("\nSemaphore set with the specified key does not exit: ");
      printf("Error no = %d\n", errno);
      exit(ERR);
    }
    printf("\nSemaphore set ID = %d\n", semid);
  }

  else if (!strcmp(argv[0], "rsem")) {
  /* to remove a semaphore set */
    semid = semget(key, UNUSED, UNUSED); /* get semid for given key */
    if ((semctl(semid, UNUSED, IPC_RMID, UNUSED)) == ERR) {
      printf("\nSemaphore set %d not removed: ", semid);
      printf("Error no = %d\n", errno);
      exit(ERR);
    }
    printf("\nSemaphore set %d is removed\n", semid);
  }
  exit(0);
} /* main */
