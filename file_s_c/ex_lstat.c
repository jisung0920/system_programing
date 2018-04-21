#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	int i;
	struct stat buf;
	lstat(argv[argc-1],&buf);

	if(S_ISLNK(buf.st_mode))
		printf("it is symbolic\n");
	return 0;
}
