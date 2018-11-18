#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_stm.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "queue.h"

#define OK		0
#define ERR 	1

#define DELIMETER " \n"
#define PATH_DELIMETER ":"
#define ELEMENT_SIZE 10
#define MAX_SIZE 100
#define END "\0"
#define LIST_SIZE 6

//static int history_count=0;

char parameter_strings[ELEMENT_SIZE][MAX_SIZE];
char paths[10][MAX_SIZE];
char history_of_command[ELEMENT_SIZE][MAX_SIZE];
char *argv2[1];

int system_command_flag = ERR;

//koruma yapan fonksiyon eklenicek command alanalr için ve boşluk için

void parse_path(char* path_for_findloc){
	int i=0;
	char *str_ptr;

	str_ptr = strtok(path_for_findloc,PATH_DELIMETER);
	while(str_ptr != NULL){
		strcpy(paths[i],str_ptr);
		str_ptr = strtok(NULL,PATH_DELIMETER);
		i++;
	}
}

int system_command(){

	argv2[0] = "";
	argv2[1] = NULL;

	//printf("I am system_command.");

	system_command_flag = OK;

	return OK;
}

void cd(){
	char *argv2[3];
	//int ret;
	argv2[0] = "ls";
	argv2[1] = "-ltrh";
	argv2[2] = NULL;
	struct stat cd;

	//printf("\nI am cd.\n");

	//printf("\nparameter_strings[1]:%s:\n",parameter_strings[1]);

	if(strcmp(parameter_strings[1],"")!=0 && stat(parameter_strings[1],&cd) == 0){
		chdir(parameter_strings[1]);
	}else{
		chdir(getenv("HOME"));
	}
	//printf("HEYY ret:%d",ret);

	execvp("ls",argv2);
}

void dir(){
    char path[128];
    //printf("I am dir.");
    getcwd(path,sizeof(path));
    printf("Your path is:%s\n",path);
}

void History(){
	//int i=0;
	//printf("I am history.");
//	for(i=0;i<history_count;i++)
//		printf("[%d] %s",i+1,history_of_command[i]);

//	while(headPtr!=NULL){			//taking task nodes with dequeue from queue
//		Task_dequeue(&headPtr,&tailPtr,&task_node);
//		printf("\n[%d] %s",task_node.task_num,task_node.value);
//	}

}

int findloc(){
	int i=0;
	struct stat fl;
	//printf("I am findloc.");

	parse_path(getenv("PATH"));
	for(i=0;(strcmp(paths[i],"")!=0);i++){
		strcat(paths[i],"/");
		strcat(paths[i],parameter_strings[1]);
		//boş verebilir korumaya girilecek.
		if(stat(paths[i],&fl) == 0 && (fl.st_mode & S_IXUSR)){
			printf("\n%s\n",paths[i]);
			return OK;
		}
	}
	printf("This command are not found as executable file.");
	return ERR;
}

void bye(){
	//printf("I am exit.");
	exit(EXIT_SUCCESS);
}

void (*callback(int x)) (void){
	void* array[LIST_SIZE]={system_command,cd,dir,History,findloc,bye};
	void* ret=NULL;

	ret= array[x];
	return ret;
}

int determine_command_type_index(){
	int i=0;
	int ret=0;
	char command_list[LIST_SIZE][16]={"system_command","cd","dir","history","findloc","bye"};
	//printf("parameter_strings[0]:%s:",parameter_strings[0]);
	for(i=0;i!=LIST_SIZE;i++){
		if(strcmp(parameter_strings[0],command_list[i])==0){
			ret= i;
			return ret;
		}
	}

	return ret;

}

void take_command_from_user(char* input_string){
	printf("myshell>");
	fgets(input_string,MAX_SIZE,stdin);
	fflush(stdin);

	if (strlen (input_string) > 0)
		if (input_string[strlen (input_string) - 1] == '\n')
			input_string[strlen (input_string) - 1] = '\0';
}

void parse_taking_command(char* input_string){
	int i=0;
	char *str_ptr;

	str_ptr = strtok(input_string,DELIMETER);
	while(str_ptr != NULL){
		strcpy(parameter_strings[i],str_ptr);
		str_ptr = strtok(NULL,DELIMETER);
		i++;
	}
	//parameter_strings[i][0] = '\0';
}

int main(int argc, char* argv[])
{
	//int i=0;
	while(1){
		char input_string[MAX_SIZE];
		int ret,valid_command=OK;
		void (*pf)(void);
		pid_t pid;

		//char (*ptr)();

		//Take command from user
		do
		take_command_from_user(input_string);
		while(!strcmp(input_string,""));
		//Record to history
		//Task_queue(input_string);

		//Parse taking command into parts
		parse_taking_command(input_string);

		//Built-in commands or not
		ret = determine_command_type_index();
		//printf("ret:%d",ret);
		//Call command function
		pf=callback(ret);
		if(pf!=NULL)
			pf();

		if(system_command_flag==OK){
			pid = fork();

			if(pid < 0){
				printf("Fork Failed.");
				return ERR;
			}

			if(pid == 0){
				valid_command = execvp(parameter_strings[0],argv2);
				if(valid_command!=OK){
					printf("%s: command not found\n",parameter_strings[0]);
					valid_command = OK;
				}
				exit(EXIT_SUCCESS);
			}else{
				wait(NULL);
				system_command_flag = ERR;
			}
		}
		//boşalt
		memset(input_string,0x00,sizeof(input_string));
		memset(parameter_strings,0x00,sizeof(parameter_strings));
	}
	return OK;
}
