#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#define SHMKEY1 (key_t)0x10 /*shared mem key*/
#define SHMKEY2 (key_t)0x15 /*shared mem key*/
#define SEMKEY (key_t)0x20 /*semaphore key*/
/*buffer size for reads and writes*/
#define SIZ 5*BUFSIZ
/*will hold data and read count*/
struct databuf {
int d_nread;
char d_buf[SIZ];
};
/* function prototypes */
int getseg(struct databuf **p1, struct databuf **p2);
int getsem(void);
int remove(void);
void reader(int semid, struct databuf *buf1, struct databuf *buf2);
void writer(int semid, struct databuf *buf1, struct databuf *buf2);
