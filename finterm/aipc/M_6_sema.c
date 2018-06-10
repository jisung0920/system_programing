#include "sema.h"
int main(void)
{
int pid;
struct sembuf sembuf[SEMOPM], *semoprs = sembuf;
union semun sems;
key_t key = semkey(SEMKEY, SEMID);
/* no error checking */
int semid = semget(key, UNUSED, UNUSED); /* no error checking */
sems.val=NUMR1;
semctl(semid, R1, SETVAL, sems); /* no error checking */
sems.val=NUMR2;
semctl(semid, R2, SETVAL, sems); /* no error checking */
if (!fork()) { /* 1st child */
pid = getpid();
P(R1);
/* needs one instance of R1 */
printf("\n\t(%d): GOT it *** \n\t\t*** Using it \n\n", pid);
sleep(5);
V(R1);
/* done with it */
printf("\n\t(%d):DOING something else\n\t\t\t...\n", pid);
Pn(R2, 2);
/* needs two instances of R2 */
printf("\n\t(%d): GOT'em *** \n\t\t*** Using'em \n\n", pid);
sleep(10);
Vn(R2, 2);
/* done with'em */
exit(0);
}
if (!fork()) { /* 2nd child */
pid = getpid();
Pn(R2, 2);
/* needs two instances of R2 */
printf("\n\t(%d): Got'em ***\n\t\t*** Using'em \n\n", pid);
sleep(3);
Vn(R2, 2);
/* done with'em */
printf("\n\t(%d):Doing something else\n\t\t\t...\n", pid);
P(R1);
/* needs one instance of R1 */
printf("\n\t(%d): Got it ***\n\t\t*** Using it \n\n", pid);
sleep(6);
V(R1);
/* done with it */
exit(0);
}
wait((int *)0);
exit(0);
}
