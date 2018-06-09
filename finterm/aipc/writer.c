#include “shared_ex.h”
extern struct sembuf p1, p2; /*defined in reader.c*/
extern struct sembuf v1, v2; /*defined in reader.c*/
void writer(int semid, struct databuf *buf1, struct databuf *buf2)
{
for (;;) {
semop(semid, &p1, 1);
semop(semid, &v2, 1);
if(buf1 ->d_nread <= 0)
return;
write(1, buf1->d_buf, buf1->d_nread);
semop(semid, &p1, 1);
semop(semid, &v2, 1);
if(buf2->d_nread <= 0)
return;
write(1, buf2->d_buf, buf2->d_nread);
}
}
