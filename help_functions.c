#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_ops.h"
#include "help_functions.h"

bool search_duplicate(int id) {
	int i;
	for (i=0;i<SIZE;i++) {
		if (id==(db+i)->phoneNr) {

			return 1;
		}
	}
	return 0;
}

int  checkFileIsEmpty() {
	//file pointer
	FILE * fptr;
	int size;

	fptr = fopen("database.txt","r");

	if (fptr == NULL) {

		printf("(taktak-app) the database does not exist\n(taktak-app) create an empty database\n");
		fptr = fopen("database.txt", "w");
		
 		if(fptr == NULL) {

			printf("(taktak-app) Unfortunately, a new database cannot be created\n");
			exit(0);

		} 
		return 0;
	}

	fseek(fptr,0,SEEK_END);
	size = ftell(fptr);

	if (size == 1) {
		return 1; //file is empty. It only contains EOF-character
	}	
	return 0;//file is not empty
}

bool  checkIfDataAvailable(struct student * db){

	if ((db->statusFlag) != 0) {
		return 0;//db is not empty
	}

	return 1;//db is empty
}

void parseLine(char * str,char * tokens [], int max_tokens) {
    	char del[2]=",";
	char * token;
	token=strtok(str,del);
	int i=0;
	while (token!=NULL&&i<max_tokens) {

		//assign the token to the array
		*(tokens+i)=token;
		token=strtok(NULL,del);
		i++;
	}
}

void remove_semicolon(char * str) {

	int len = strlen(str);
	if (len && str[len-2]==';') {
		str[len-2]=0;
	}
}

int clear_stdin(FILE * in) 
{
	int ch;
	clearerr(in);

	do{
		ch=getc(in);
	}while(ch != '\n' && ch != EOF);
	clearerr(in);
}

int  getPhoneNr(){
	int phoneNr;
	int c;
	//c must be a  white-space character to be a valid integer
	while (scanf("%d",&phoneNr) != 1 || ((c=getchar()) !=EOF && !isspace(c))) {
		printf("please enter a valid phone-Nr: ");
		clear_stdin(stdin);
	}

	return phoneNr;
}

void remove_newline(char * str){
	size_t str_len=strlen(str);
	if(str_len && str[str_len-1]=='\n'){
		str[str_len-1]=0;
	}
}


