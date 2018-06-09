#include “share_ex.h”
/*these define p() and v() for semaphores*/
struct sembuf p1 = {0, -1, 0}, p2 = {1, -1, 0};
struct sembuf v1 = {0, 1, 0}, v2 = {1, 1, 0};
void reader(int semid, struct databuf *buf1, struct databuf *buf2)
{
for (;;) {
/*read into buffer buf1*/
buf1->d_nread = read(0, buf1->d_buf, SIZ);
/*synchronization point*/
semop(semid, &v1, 1);
semop(semid, &p2, 1);
/*test here to avoid writer sleeping*/
if(buf1->d_nread <= 0)
return;
buf2->d_nread = read(0, buf2->d_buf, SIZ);
semop(semid, &v1, 1);
semop(semid, &p2, 1);
if (buf2->d_nread <= 0)
return;
}
}
