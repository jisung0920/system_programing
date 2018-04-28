#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
int main(void){

	int fd,newfd;
	fd = open("/etc/passwd",O_RDONLY);
	printf("first fd :%d\n",fd);

	printf("stdout fd :%d\n",STDOUT_FILENO);
//	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	newfd = dup(fd);
	printf("new fd :%d\n",newfd);
	return 0;
}
