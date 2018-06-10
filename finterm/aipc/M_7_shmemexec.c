#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
struct shmdata {
int ndata;
char sdata[24];
};
struct sembuf lock = {0, -1, IPC_NOWAIT}; /* to make it readable */
struct sembuf unlock = {0, 1, IPC_NOWAIT};
int main(int argc, char *argv[])
{
int shmid, semid;
char *shmptr;
struct shmdata shmbuf;
sscanf(argv[1], "%d", &shmid); /* to get shmem ID from argv[1] */
shmptr = shmat(shmid, (char *)0, 0);
if (shmptr == (char *) -1) {
fprintf(stderr, "shmat failed\n");
exit(1);
}
/* to lock the attched memory with a semaphore */
semid = atoi(argv[2]);
/* another way to convert */
if (semop(semid, &lock, 1) < 0) {
fprintf(stderr, "semop lock failed\n");
exit(2);
}
/* to read data from attached memory to buffer */
memcpy((char *)&shmbuf, shmptr, sizeof(struct shmdata));
printf("In child: %d %s\n", ((struct shmdata *)shmptr)->ndata,
((struct shmdata *)shmptr)->sdata);
shmbuf.ndata = 10;
/* to change value */
/* to update shared memory segment */
memcpy(shmptr, (char *)&shmbuf, sizeof(struct shmdata));
shmdt(shmptr);
/* detach memory */
if (semop(semid, &unlock, 1) < 0) {
fprintf(stderr, "semop unlock failed\n");
exit(3);
}
return(0);
} /* shmemexec.c */
