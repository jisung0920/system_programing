#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
int main(void){

	umask(0);
	if(creat("foo",S_IRUSR|S_IWUSR|S_IWGRP|S_IROTH)<0){
		perror("creat error for foo");
		exit(1);
	}

	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	
	if(creat("bar",S_IRUSR|S_IWGRP)<0){
		perror("creat error for bar");
		exit(1);
	}
	exit(0);
}
