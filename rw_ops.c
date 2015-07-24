#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db_ops.h"

extern struct student * db;
extern insertCounter;
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
void writeData(){
	FILE * fpw;
	fpw=fopen("database.txt","w");
	if(fpw==NULL){
		printf("the file cannot be opened");
		exit(1);
	}
	int i;
	//if there is at least one entry, then this entry will be written in the file
	if(check_db(db)){
		for(i=0;i<SIZE;i++){
			fprintf(fpw,"%s, %s, %d, %s , %s;\n",	
				(db+i)->lastname,(db+i)->firstname,(db+i)->mNr, (db+i)->subject, (db+i)->nationality);
		}
	}
	fclose(fpw);
}


void readData(){
	FILE * fp;
	fp=fopen("database.txt","r");
	if(fp==NULL){
		printf(">>> the file cannot be opened");
		exit(1);
	}
	int i=0;
	char line[120];
	char *fields[5];
	while(fgets(line,120,fp)!=NULL && i<SIZE){
		//parse each line of database
		parseLine(line,fields,5);
		remove_semicolon(fields[4]);
		//save the read data in memory db
		struct student  st=getData(fields[0],fields[1],atoi(fields[2]),fields[3],fields[4]);
		insert_student(&st);	
		i++;
	}
	fclose(fp);	
}

