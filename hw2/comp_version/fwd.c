/*===========================================================================
	File : fwd.c
	Date : 2018.05.06
	Auther : 정지성 (jisung0920@gmail.com)
	Descirption:
		Search and change directory,using system call interfaces and shell script
		(Hanyang univ -erica / 2018 System Programing / CSE4009 )
	===========================================================================*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define SIZE 100
#define LISTSIZE 100

void find_dir(char*);
int print_dir_list(void);
void change_dir(int);
void deallocate_glo_var(void);
//functions

char *target_name;
char *found_list[LISTSIZE];

char inst[SIZE];

int count = 0;

int main(void){

	char buffer[SIZE];
	int length, selected_num;

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

  selected_num = print_dir_list();
	/*
	print all found directory list
	and get selected number(for change directory)
	*/

  change_dir(selected_num);
	/*
	change direcotry (bash instruction setting or chdir in the process)
	*/

	deallocate_glo_var();
	//deallocate variable

	if(count!=0)
		system(inst);
	//run the shell script

	return 0;
}

void find_dir(char* dir_name){

  DIR* dirptr;
  struct dirent* dir;

  if((dirptr = opendir(dir_name))==NULL){
    perror("Open directory error.\n");
    exit(-1);
  }

  while (dir = readdir(dirptr)) {

    if(dir->d_ino != 0){

      if(!strcmp(dir->d_name,"..")||!strcmp(dir->d_name,"."))
        continue;
      //Filtering special inode entries


      int L = strlen(dir_name) + strlen(dir->d_name) +2;

      char* sub_path = (char*)malloc(sizeof(char) * L);
      sprintf(sub_path,"%s/%s",dir_name,dir->d_name);
      //Set child file path

      struct stat file_info;
      stat(sub_path, &file_info);
      //Get file stat from name

      if(S_ISDIR(file_info.st_mode)){

        if(!strcmp(target_name,dir->d_name)){
          found_list[count] = (char*)malloc(sizeof(char) * L);
          sprintf(found_list[count],"%s/%s",dir_name,dir->d_name);
          count++;
        }
        //If there is matched name, save to the list

        find_dir(sub_path);
        //Recusive call (input : sub directory path)

        free(sub_path);
        //Deallocate used path name

        }
      }
  }

  closedir(dirptr);
  //Close directory ptr
}


int print_dir_list(void){

		int select;

		if(count==0){
			printf("There is no such directory\n");
			return -1;
		}//Cannot find the directory

		else{

			int i;
			for(i=0;i<count;i++)
				printf(">[%d]  %s\n",i+1,found_list[i]);
			//Print list items(target names)

			do{
				getchar();
				printf("Which directory do you want? ");
				scanf("%d",&select);
			}
			while(select<1 || select>=count+1);
			//Get selecting number

			printf(">%s\n",found_list[select-1]);
      //Print selected item
      return select;
		}

}

void change_dir(int select_n){
	if(select_n==-1)
		return ;

	/*
	if(!chdir(found_list[select_n-1]))
		perror("Change directory error.\n");
	//for the first homework mission
	*/

	sprintf(inst,"./cwd_script %s",found_list[select_n-1]);
	//shell script instruction setting(string)
}

void deallocate_glo_var(void){
	int i;
	for(i;i<count;i++)
		free(found_list[count]);
	free(target_name);
}
