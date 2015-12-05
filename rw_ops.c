#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rw_ops.h"
#include "db_ops.h"
#include "help_functions.h"

int insertCounter = 1;

void writeData(){

	//FILE is an object to control the stream
	FILE * fpw;
	fpw = fopen("database.txt","w");

	if (fpw == NULL) {
		printf("(taktak-app) the file cannot be opened for writing");
		exit(1);
	}

	int i;
	//if there is at least one entry in db , then this entry will be written in the file
	if(!checkIfDataAvailable(db)){

		for(i=0;i<SIZE;i++){
			if((db+i)->statusFlag == 1){
				fprintf(fpw,"%s, %s, %d, %s , %s;\n",	
					(db+i)->lastname,(db+i)->firstname,(db+i)->phoneNr, (db+i)->university, (db+i)->nationality);
			}
		}
	}

	fclose(fpw);
}

void  readData() {

	FILE * fpr;
	fpr = fopen("database.txt","r");

	if (fpr == NULL) {

		printf("(taktak) the file cannot be opened for reading\n");
	
	}

	int i=0;
	char line[120];
	char *fields[5];
	while(fgets(line,120,fpr)!=NULL && i<SIZE){

		//parse each line of database
		parseLine(line,fields,5);
		//printf("%s, %s,%s,%s,%s",fields[0],fields[1],fields[2],fields[3],fields[4]);
		remove_semicolon(fields[4]);
		//save the read data in memory db
		struct student  st=getData(fields[0],fields[1],atoi(fields[2]),fields[3],fields[4]);
		insertStudent_0(&st);	
		i++;
	}

	fclose(fpr);
}

