#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define SIZE 10

int main(void){
	int fd1;
	char buf[]="abcdefg";
	
	fd1 = creat("tlseek",0644);
	write(fd1,buf,5);
	int n = read(fd1,buf,5);
	
