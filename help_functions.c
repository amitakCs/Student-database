#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_ops.h"
#include "help_functions.h"

bool search_duplicate(int id){
	int i;
	for(i=0;i<SIZE;i++){
		if(id==(db+i)->mNr){
			return 1;
		}
	}
	return 0;
}

int  checkFileIsEmpty(){
	//file pointer
	FILE * fptr;
	int size;

	fptr = fopen("database.txt","r");

	if(fptr == 0){
		printf("cannot open the file\n");
		exit(0);
	}

	fseek(fptr,0,SEEK_END);
	size = ftell(fptr);
	if(size == 1){
		return 1; //file is emtpy. It only contains EOF-character
	}	
	return 0;//file is not empty
}

bool  checkIfDataAvailable(struct student * db){
	int i=0;
	if((db->statusFlag) != 0){
		return 0;//db is not empty
	}
	return 1;//db is empty
}

void parseLine(char * str,char * tokens [], int max_tokens){
    	char del[2]=",";
	char * token;
	token=strtok(str,del);
	int i=0;
	while(token!=NULL&&i<max_tokens){
		//assign the token to the array
		*(tokens+i)=token;
		token=strtok(NULL,del);
		i++;
	}
}

void remove_semicolon(char * str){
	int len=strlen(str);
	if(len && str[len-2]==';'){
		str[len-2]=0;
	}
}

int clear_stdin(FILE * in){
	int ch;
	clearerr(in);
	do{
		ch=getc(in);
	}while(ch!='\n' && ch!=EOF);
	clearerr(in);
}

int  getIdNr(){
	int matNr;
	int c;
	//c must be a  white-space character to be a valid integer
	while(scanf("%d",&matNr)!=1 || ((c=getchar())!=EOF && !isspace(c))){
		printf("please enter a valid Id-Nr: ");
		clear_stdin(stdin);
	}
	return matNr;
}

void remove_newline(char * str){
	size_t str_len=strlen(str);
	if(str_len && str[str_len-1]=='\n'){
		str[str_len-1]=0;
	}
}


