#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
main()
{
int fd;
struct flock my_lock;
/* 쓰기 록의 인수를 지정 */
my_lock.l_type = F_WRLCK;
my_lock.l_whence = SEEK_SET;
my_lock.l_start = 0;
my_lock.l_len = 10;
/* 화일을 개방한다. */
fd = open ("locktest", O_RDWR);
/* 처음 10바이트를 록한다 */
if ( fcntl (fd, F_SETLKW, &my_lock) == -1)
{
perror ("parent: locking");
exit (1);
}
printf ("parent: locked record\n");
switch (fork()){
case -1: /* 오류 */
perror ("fork");
exit (1);
case 0: /* 자식 */
my_lock.l_len = 5;
if ( fcntl (fd, F_SETLKW, &my_lock) == -1)
{
perror ("child: locking");
exit (1);
}
printf ("child: locked\n");
printf ("child: exiting\n");
exit(0);
}
sleep(5);
/* 이제 퇴장(exit)한다. 따라서 록이 해제된다 */
printf ("parent: exiting\n");
exit (0);
} 
