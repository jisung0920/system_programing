#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
enum { ERR = -1,
REQ = -1,
/* need one instance */
REL = 1,
/* release one instance */
UNUSED = 0,
/* for padding unused arguments */
SEMOPM = 10,
/* default max # of sem ops at a time */
R1 = 0,
/* reource type 1 */
R2 = 1,
/* reource type 2 */
NUMR1 = 1,
/* # of resource type R1 */
NUMR2 = 3,
/* # of resource type R2 */
SEMID = 'a',
/* any arbitrary char */
SEMMSL = 25
/* default max # of sems in a set */
};
char SEMKEY[] = "semkey"; /* pathname used as part of semaphore key */
union semun {
int val;
struct semid_ds *buf;
ushort *array;
};
unsigned nsops = 1;
struct sembuf sembuf[SEMOPM], *semoprs = sembuf;
#define semkey(x, y) (key_t)ftok(x, y)
#define P(device)
{ int pid = getpid();\
printf("Process %d requests resources: wait ...\n", \
pid); \
semoprs->sem_num = device; \
semoprs->sem_op = REQ; \
semoprs->sem_flg = UNUSED; \
semop(semid, semoprs, nsops);\
printf("Resources allocated (pid=%d)\n", pid); }
#define V(device)
{ int pid = getpid();\
printf("Proc %d will release resources: ... good news\
\n", pid); \
semoprs->sem_num = device; \
semoprs->sem_op = REL; \
semoprs->sem_flg = UNUSED; \
semop(semid, semoprs, nsops);\
printf("Resources released (pid= %d)\n", pid); }
#define Pn(device, no) { int pid = getpid();\
printf("Process %d requests resources: wait ...\n", \
pid); \
semoprs->sem_num = device; \
semoprs->sem_op = REQ * no; \
semoprs->sem_flg = UNUSED; \
semop(semid, semoprs, nsops);\
printf("Resources allocated (pid=%d)\n", pid); }
#define Vn(device, no) { int pid = getpid();\
printf("Proc %d will release resources: ... good news\
\n", pid); \
semoprs->sem_num = device; \
semoprs->sem_op = REL * no; \
semoprs->sem_flg = UNUSED; \
semop(semid, semoprs, nsops);\
printf("Resources released (pid=%d)\n", pid); }
