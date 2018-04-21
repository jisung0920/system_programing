#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>


int main(void){

	int fd;
	char *buf = "SystemPrograming task";

	fd = open("./test.txt",O_WRONLY | O_CREAT,0644);
	
	if(write(fd,buf,strlen(buf)) == -1)
		perror("write error");

	printf("original :  %s\n",buf);

	close(fd);
	
	int off = 100;
	
	truncate("./test.txt",off);
	
	fd = open("./test.txt",O_RDONLY);
	read(fd,buf,off);
	write(1,buf,off);
	close(fd);
	putchar('\n');
	return 0;
}
