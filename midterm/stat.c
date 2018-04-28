#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(void){
	struct stat statbuf;

	stat("foo",&statbuf);

	chmod("foo",(statbuf.st_mode & ~S_IXGRP)|S_ISGID);

	return 0;
}
