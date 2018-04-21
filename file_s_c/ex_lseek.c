#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIG";

int main(void){

	int fd;
	if ((fd = creat("file.hole",0640))<0){
		perror("creat error");
		exit(1);
	}
	write(fd,buf1,10);

	int i =	lseek(fd,40,SEEK_CUR);
	write(fd,buf2,10);
	printf("lseek = %d\n",i);
	exit(0);
}
