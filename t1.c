#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
void access_p(char *perm,mode_t mode){
	int i;
	char permchar[] = "rwx";
	memset(perm,'-',10);
	perm[10] = '\0';

	for(i=0;i<9;i++){	
		if((mode<<i)&0x200)
			perm[i+1]  = permchar[i%3];
	}
}
int main(int argc,char* argv[]){
	char perm[11];
	char pathname[80];
	struct stat statbuf;

	stat(argv[1],&statbuf);
	access_p(perm,statbuf.st_mode);
	printf("%s\n",perm);
	return 0;}

