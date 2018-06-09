#include <stdio.h>
#include "pv.h"
int handlesem(key_t skey)
{
int semid, pid = getpid();
if ((semid = initsem(skey)) < 0)
exit(1);
printf("\nprocess %d before critical section\n", pid);
p(semid);
printf("process %d in critical section\n", pid);
sleep(10); /*in real life do something interesting*/
printf("process %d leaving critical section\n", pid);
v(semid);
printf("process %d exiting\n", pid);
exit(0);
}
void main(void)
{
key_t semkey = 0x200;
if (fork() == 0)
handlesem(semkey);
if (fork() == 0)
handlesem(semkey);
if (fork() == 0)
handlesem(semkey);
}
