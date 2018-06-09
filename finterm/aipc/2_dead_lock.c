#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
main()
{
int fd;
struct flock first_lock;
struct flock second_lock;
first_lock.l_type = F_WRLCK;
first_lock.l_whence = SEEK_SET;
first_lock.l_start = 0;
first_lock.l_len = 10;
second_lock.l_type = F_WRLCK;
second_lock.l_whence = SEEK_SET;
second_lock.l_start = 10;
second_lock.l_len = 5;
fd = open ("locktest", 0_RDWR);
if ( fcntl (fd, F_SETLKW, &first_lock) == -1) /* A */
fatal ("A");
printf ("A: lock succeeded (proc %d)\n", getpid());
switch (fork()){
case -1:
/* 오류 */
fatal ("error on fork");
case 0:
/* 자식 */
if ( fcntl (fd, F_SETLKW, &second_lock) == -1) /* B */
fatal ("B");
printf ("B: lock succeeded (proc %d)\n", getpid());
if ( fcntl (fd, F_SETLKW, &first_lock) == -1) /* C */
fatal ("C");
printf ("C: lock succeeded (proc %d)\n", getpid());
exit (0);
default:
/* 부모 */
printf ("parent sleeping\n");
sleep (10);
if ( fcntl (fd, F_SETLKW, &second_lock) == -1) /* D */
fatal ("D");
printf ("D: lock succeeded (proc %d)\n", getpid());
}
} 
