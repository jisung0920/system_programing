#include <stdio.h>
#include <unistd.h>

int main(void){
	char buf[1024];
	printf("WD :%s \n WD : %s",getcwd(buf,1024),buf);
	return 0;
} 
