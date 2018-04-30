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
int print_dir_list(void);
void change_dir(int);
void deallocate_glo_var(void);

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
	scanf("%s",buffer);// get target name

	length = strlen(buffer);
	target_name = (char*)malloc(sizeof(char) * (length+1));
  strcpy(target_name, buffer);
	//keep target name using global variable

	find_dir(getcwd(NULL,0));
	/*
	find directory matched target name, using current path
	if find dir, save to 'found_list'
	*/


	/*
	print all found directory list
	and get selected number(for change directory)
	*/

	change_dir(	print_dir_list());
	printf("get : %s\n",getcwd(NULL,0));
	deallocate_glo_var();
	//deallocate variable

	return 0;
}
void find_dir(char* dir_name){

	printf("find dir function : %s========\n",dir_name);
	DIR* dirptr;
	struct dirent* dir;

	if((dirptr = opendir(dir_name))==NULL){
		perror("Open directory error\n");
		exit(-1);
	}
	//directory stream open

	while(dir = readdir(dirptr)){
		if(dir->d_ino != 0){

			if(!strcmp(dir->d_name,"..")||!strcmp(dir->d_name,"."))
				continue;
			//directory except part - own or parent dir

			struct stat file_info;
			stat(dir->d_name, &file_info);
			//get file state from name

			if(S_ISDIR(file_info.st_mode)){

				int mLength = strlen(dir->d_name) + strlen(dir_name);

				if(!strcmp(target_name,dir->d_name)){
					found_list[count] = (char*)malloc(sizeof(char)*mLength+2);
					sprintf(found_list[count],"%s/%s",dir_name,dir->d_name);
					count++;
				}//If there is matching name, save to the list

				char* sub_path = (char*)malloc(sizeof(char)*(mLength+2));
				sprintf(sub_path,"%s/%s",dir_name,dir->d_name);
				//path setting(allocation)

				find_dir(sub_path);
				//recusive call(input:sub directory path)

				free(sub_path);
				//deallocate used path name
			}
			//If there is directory, search recusively
		}

	}
	//read directory and save taget name

	// closedir(dirptr);
}


int print_dir_list(void){

		int select;

		if(count==0){
			printf("There is no such directory\n");
			return -1;
		}

		else{
			int i;
			for(i=0;i<count;i++)
				printf(">[%d]  %s\n",i+1,found_list[i]);
			//print list items(target names)

			printf("which directory do you want? ");
			scanf("%d",&select);

			printf(">%s\n",found_list[select-1]);
			return select;
		}

}

void change_dir(int select_n){
	if(select_n==-1||select_n>=count)
		return ;
	if(chdir(found_list[select_n-1]))
		return ;

}

void deallocate_glo_var(void){
	int i;
	for(i;i<count;i++)
		free(found_list[count]);
	free(target_name);
}
