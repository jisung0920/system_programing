#include <stdio.h>
#include "q.h"
int main(void)
{
int pid;
switch(pid = fork()) {
case 0: /*child*/
serve();
break; /*actually, serve never exits */
case -1:
perror("fork to start sever failed");
break;
default:
printf("server process pid is %d\n", pid);
}
exit(pid == -1 ? 1 : 0);
}
