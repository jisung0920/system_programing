#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
int main(void){

	struct stat statbuf;

	if(stat("foo",&statbuf)<0){
		perror("stat error for foo");
		exit(1);
	}
	if(chmod("foo",(statbuf.st_mode & ~S_IXGRP | S_ISGID))<0){
		perror("chmod error for foo");
		exit(1);
	}
	exit(0);
}
