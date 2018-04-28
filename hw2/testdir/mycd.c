#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define SIZE 100
#define LISTSIZE 50

void find_dir(char*);
void print_dir_list(void);
void change_dir(void);

char *target_name;
char *found_list[LISTSIZE];
char cwd_dir_name;

int count = 0;

int main(void){

	char buffer[SIZE];
	int length;

	DIR* dirptr;
	struct dirent* dir;
	char dir_name[SIZE];

	printf("Enter the name of a directory :");
	scanf("%s",buffer);

	length = strlen(buffer);
	target_name = (char*)malloc(sizeof(char) * (length+1));
  strcpy(target_name, buffer);

	printf("%s\n",target_name);

	find_dir(getcwd(NULL,0));

	print_dir_list();

	//change_dir();
	free(target_name);
	return 0;
}


void find_dir(char* dir_name){

	DIR* dirptr;
	struct dirent* dir;

	if((dirptr = opendir(dir_name))==NULL){
		perror("Open directory error\n");
		exit(-1);
	}

	while(dir = readdir(dirptr)){
		if(dir->d_ino != 0){

			if(!strcmp(dir->d_name,"..")||!strcmp(dir->d_name,"."))
				continue;//directory except part - own or parent dir

			struct stat file_info;

			stat(dir->d_name, &file_info);

			if(S_ISDIR(file_info.st_mode)){

				printf(">%s\n",dir_name);

				if(!strcmp(target_name,dir->d_name)){


					found_list[count] = (char*)malloc(sizeof(char)*(strlen(dir->d_name)+1));
					strcpy(found_list[count],dir->d_name);
					count++;
				}
				
				find_dir(dir->d_name);

			}
		}
	}
}
void print_dir_list(void){
		if(count==0)
			printf("There is no such directory\n");
		else{
			int i,select;
			for(i=0;i<count;i++){
				printf(">[%d]  %s\n",i+1,found_list[i]);
			}
			printf("which directory do you want?\n");
			scanf("%d",&select);
		}

}

void change_dir(void){
	if(cwd_dir_name==NULL)
		return ;
	else{
			if(chdir(cwd_dir_name))
	}

}
