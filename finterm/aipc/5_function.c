#include "5_pv.h"

int initsem(key_t semkey){
  int status = 0, semid;
  if ((semid = semget(semkey, 1, SEMPERM|IPC_CREAT|IPC_EXCL)) == -1) {

    if (errno == EEXIST)
      semid = semget(semkey, 1, 0);
  }
  else /* if created ..*/{
    union semun arg;
    arg.val = 1;
    status = semctl(semid, 0, SETVAL, arg);
  }

  if (semid == -1 || status == -1) {
    perror("initsem failed");
    return (-1);
  }
  else
    return semid; /*all okay*/
}


int p(int semid){
  struct sembuf p_buf;
  p_buf.sem_num = 0;
  p_buf.sem_op = -1;
  p_buf.sem_flg = SEM_UNDO;
  if (semop(semid, &p_buf, 1) == -1) {
    perror("p(semid) failed");
    exit(1);
    }
  else
    return(0);
}

int v(int semid){
  struct sembuf v_buf;
  v_buf.sem_num = 0;
  v_buf.sem_op = 1;
  v_buf.sem_flg = SEM_UNDO;
  if (semop(semid, &v_buf, 1) == -1) {
    perror("v(semid) failed");
    exit(1);
  }
  else
    return(0);
}
