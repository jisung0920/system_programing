#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
int main(void){
	if(chdir("/home/jisung/jisung/cse/system_programing/file_s_c/file.hole")<0)
		printf("error\n");
	else
		printf("success\n");
	
	int fd;
	if((fd = open("/home/jisung/jisung",O_RDONLY))==-1)
		printf("directory open error\n");
	else
		printf("directory file descriptor is %d \n\n",fd);
	exit(0);
}
