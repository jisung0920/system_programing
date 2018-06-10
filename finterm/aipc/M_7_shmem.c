#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
struct shmdata {
/* a user-defined data structure for shmem */
int ndata;
char sdata[24];
};
union semun {
int val;
struct semid_ds *buf;
ushort *array;
};
int main(void)
{
int shmid, semid;
char *shmptr, cshmid[10], csemid[10]; /* 10 is arbitrary */
pid_t pid;
union semun sems;
struct shmdata shmbuf = {
/* some data */
11,
"UNIX System Programming"
};
/* to get a shared memory identifier */
shmid = shmget(IPC_PRIVATE, sizeof(struct shmdata), IPC_CREAT|0666);
if (shmid < 0) {
fprintf(stderr, "shmget failed\n");
exit(1);
 }
/* to attach a shared memory segment to the process data area */
/* up to the system to decide where to fit ((char *)0), for r/w (0) */
shmptr = shmat(shmid, (char *)0, 0);
if (shmptr == (char *) -1) {
fprintf(stderr, "shmat failed\n");
exit(2);
}
/* to copy data into attached memory segment */
memcpy(shmptr, (char *)&shmbuf, sizeof(struct shmdata));
/* to create a new semaphore set with one semaphore in it */
semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
if (semid < 0) {
fprintf(stderr, "semget failed\n");
exit(3);
}
/* to initialize the 0th semaphore in the set to 1 */
sems.val = 1;
if ((semctl(semid, 0, SETVAL, sems)) < 0) {
fprintf(stderr, "semctl SETVAL failed\n");
exit(4);
/* to fork a child to read/upate the shared memroy */
switch (pid = fork()) {
case -1:
fprintf(stderr, "fork failed\n");
exit(5);
case 0: /* child */
sprintf(cshmid, "%d", shmid);
/* to convert int to str */
sprintf(csemid, "%d", semid);
execl("./shmemexec", "shmemexec", cshmid, csemid, (char *)0);
exit(6);
/* in case execl() fails */
default: /* parent */
wait((int *)0); /* wait for child to terminate */
printf("In parent: %d %s\n", ((struct shmdata *)shmptr)->ndata,
((struct shmdata *)shmptr)->sdata);
shmdt(shmptr);
/* detach shared memory */
shmctl(shmid, IPC_RMID, (struct shmid_ds *)0); /* remove shm ID */
semctl(semid, 0, IPC_RMID, 0); /* remove sem ID */
}
return(0);
} /* shmem.c */
