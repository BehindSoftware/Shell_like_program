#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_stm.h"
#include <unistd.h>

#define OK		0
#define ERR 	1

#define DELIMETER " \n"
#define MAX_SIZE 100
#define END "\0"
#define LIST_SIZE 6

char parameter_strings[10][MAX_SIZE];

void system_command(){
	printf("I am system_command.");
}

void cd(){
	char *argv2[3];
	int ret;
	argv2[0] = "ls";
	argv2[1] = "-ltrh";
	argv2[2] = NULL;

	printf("\nI am cd.\n");

	printf("\nparameter_strings[1]:%s:\n",parameter_strings[1]);

	if(strcmp(parameter_strings[1],"")==0){
		ret = chdir(getenv("HOME"));
	}else{
		ret = chdir(parameter_strings[1]);
	}
	printf("ret:%d",ret);

	execvp("ls",argv2);
}

void dir(){
	printf("I am dir.");
}

void History(){
	printf("I am history.");
}

void findloc(){
	printf("I am findloc.");
}

void exit2(){
	printf("I am exit.");
}

void (*callback(int x)) (void){
	void* array[LIST_SIZE]={system_command,cd,dir,History,findloc,exit2};
	void* ret=NULL;

	ret= array[x];
	return ret;
}

int determine_command_type_index(){
	int i=0;
	int ret=0;
	char command_list[LIST_SIZE][16]={"system_command","cd","dir","history","findloc","exit"};
	printf("parameter_strings[0]:%s:",parameter_strings[0]);
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
	char input_string[MAX_SIZE];
	int ret;
	void (*pf)(void);
	//char (*ptr)();

	//Take command from user
	take_command_from_user(input_string);

	//Parse taking command into parts
	parse_taking_command(input_string);

	//Built-in commands or not
	ret = determine_command_type_index();
	printf("ret:%d",ret);
	//Call command function
	pf=callback(ret);
	if(pf!=NULL)
		pf();

//	for(i=0; strcmp(parameter_strings[i],END)!=0 ;i++)
//		printf("\n%d text:%s",i+1,parameter_strings[i]);


//	for(i=1;i<argc;i++)
//		sprintf(parameter_strings[i],"%s",argv[i]);
//
//	for(i=1;i<argc;i++)
//		printf("\n%d text:%s",i,parameter_strings[i]);



	return OK;
}
