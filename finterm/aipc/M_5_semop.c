#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define ERR -1
#define UNUSED 0
#define SEMOPM 10
/* for padding unused arguments */
/* default max # of sem ops at a time */
extern
int errno;
int main(int argc, char **argv)
{
int i, cflag, semid, semnum, semopr;
unsigned nsops = 1; /* # of simu sem ops; let's do one at a time */
struct sembuf sembuf[SEMOPM];
struct sembuf *semoprs = &sembuf[0]; /* to deal with one at a time */
void semerr(char *);
if (!strcmp(argv[0], "semreq"))
/* request resources */
cflag = 1;
else if (!strcmp(argv[0], "semrel")) /* release resources */
cflag = 2;
else if (!strcmp(argv[0], "semzro")) /* test for zero */
cflag = 3;
printf("\nPlease enter semid > ");
scanf("%d", &semid);
switch(cflag) {
case 1:
/* process requests resources */
printf("\nPlease enter semaphore number > ");
scanf("%d", &semnum);
printf("\nPlease enter number of instances requested > ");
scanf("%d", Science
&semopr);
semopr = (- semopr);
/* minus means requested */
semoprs->sem_num = semnum; /* set up sembuf elements */
semoprs->sem_op = semopr;
semoprs->sem_flg = IPC_NOWAIT; /* otherwise process may block */
if (semop(semid, semoprs, nsops) == ERR)
semerr("Can't allocate requested resources");
else
printf("Requested resources granted\n");
break;
case 2:
/* process releases resources */
printf("\nPlease enter semaphore number > ");
scanf("%d", &semnum);
printf("\nPlease enter number of resources to be released > ");
scanf("%d", &semopr);
semoprs->sem_num = semnum; /* set up sembuf elements */
semoprs->sem_op = semopr;
semoprs->sem_flg = IPC_NOWAIT; /* otherwise process may block */
if ((semop(semid, semoprs, nsops)) == ERR)
semerr("Resources not released");
else
printf("Resources released\n");
break;
case 3:
/* test for zero */
printf("\nPlease enter semaphore number being waited > ");
scanf("%d", &semnum);
semoprs->sem_num = semnum; /* set up sembuf elements */
semoprs->sem_op = 0; /* test for zero */
semoprs->sem_flg = IPC_NOWAIT; /* otherwise process may block */
if (semop(semid, semoprs, nsops))
/* if it is non zero */
printf("Sem %d is nonzero\n", semnum);
else
printf("Sem %d is zero\n", semnum);
break;
} /* switch */
exit(0);
} /* main */
void semerr(char *mesg)
{
fprintf(stderr, mesg);
fprintf(stderr, ": errno = %d\n", errno);
exit(ERR);
} /* semerr */
