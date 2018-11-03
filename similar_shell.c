#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK		0
#define ERR 	1

#define DELIMETER " "
#define MAX_SIZE 100
#define END "\0"

char parameter_strings[10][MAX_SIZE];

void determine_command_type(){

}

void take_command_from_user(char* input_string){
	printf("myshell>");
	fgets(input_string,MAX_SIZE,stdin);
	fflush(stdin);
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
	parameter_strings[i][0] = '\0';
}

int main(int argc, char* argv[])
{
	//int i=0;
	char input_string[MAX_SIZE];

	//Take command from user
	take_command_from_user(input_string);

	//Parse taking command into parts
	parse_taking_command(input_string);

	//Built-in commands or not
	determine_command_type();

//	for(i=0; strcmp(parameter_strings[i],END)!=0 ;i++)
//		printf("\n%d text:%s",i+1,parameter_strings[i]);


//	for(i=1;i<argc;i++)
//		sprintf(parameter_strings[i],"%s",argv[i]);
//
//	for(i=1;i<argc;i++)
//		printf("\n%d text:%s",i,parameter_strings[i]);



	return OK;
}
