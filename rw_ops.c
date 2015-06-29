#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db_ops.h"

extern struct student * db;
void writeData(){
	FILE * fpw;
	fpw=fopen("database.txt","wb");
	if(fpw==NULL){
		printf("the file cannot be opened");
		exit(1);
	}
	int i;
	for(i=0;i<SIZE;i++){
		fprintf(fpw,"%s, %s, %d, %s , %s;\n",	
			(db+i)->lastname,(db+i)->firstname,(db+i)->mNr, (db+i)->subject, (db+i)->nationality);
	}
	fclose(fpw);
}

void readData(){
	FILE * fpr;
	char line[20];
	fpr=fopen("database.txt","r");
	if(fpr==NULL){
		printf("the file cannot be opened");
		exit(1);
	}
	while(fgets(line,strlen(line),fpr)){
		//memcpy(db->lastname,line);
		//memcpy();
		//memcpy();				
	}

}
