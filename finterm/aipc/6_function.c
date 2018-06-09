/*init -- initialization routines*/
#include "share_ex.h"
#define IFLAGS (IPC_CREAT|IPC_EXCL)
#define ERR ((struct databuf *) -1)
static int shmid1, shmid2, semid;
/* getseg -- create + attach shared memory sements */
int getseg(struct databuf **p1, struct databuf **p2)
{
/*create shared memory segments*/
if ((shmid1 = shmget(SHMKEY1, sizeof(struct databuf), 0600|IFLAGS)) < 0) {
perror("shmget");
exit(1);
}
if ((shmid2 = shmget(SHMKEY2, sizeof(struct databuf), 0600|IFLAGS)) < 0) {
perror("shmget");
exit(1);
}
/*attach shared memory segments*/
if ((*p1 = (struct databuf *) shmat(shmid1, 0, 0)) == ERR) {
perror("shmget");
exit(1);
}
if ((*p2 = (struct databuf *) shmat(shmid2, 0, 0)) == ERR) {
perror("shmget");
exit(1);
}
}
/* getsem -- get semaphore set */
int getsem(void)
{
/*create two semaphore set*/
if ((semid = semget(SEMKEY, 2, 0600|IFLAGS)) < 0) {
perror("semget");
exit(1);
}
/*set initial values*/
if (semctl(0, SETVAL, 0) < 0) {
perror("semctl");
exit(1);
}
if (semctl(1, SETVAL, 0) < 0) {
perror("semctl");
exit(1);
}
return(semid);
}
/* remove -- remove shared memory identifiers + sem set id */
int remove(void)
{
if (shmctl(shmid1, IPC_RMID, (struct shmid_ds *)0) < 0) {
perror("shmctl");
exit(1);
}
if (shmctl(shmid2, IPC_RMID, (struct shmid_ds *)0) < 0) {
perror("shmctl");
exit(1);
}
if (semctl(semid, IPC_RMID, (struct semid_ds *)0) < 0) {
perror("semctl");
exit(1);
}
}
