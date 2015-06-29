#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db_ops.h"

struct student * db;
struct student * ptrDb;
static int insertCounter=1;
int size=0;
int   createDb(int s){
	size=s;
	db= (struct student *)calloc(3,sizeof(struct student));
	if(db==NULL){
		printf("dynamic allocation failed");
		return EXIT_FAILURE;
	}
	ptrDb=db;
	printf("database was created\n");
}
struct student getData(char * lastname, char * firstname, int matNr, char * subject, char * nationality){
	struct student st;
	int i;
	if(insertCounter<=size){
		//get data
		st.statusFlag=1;//flag to show, whether the program gets data or not 
		//0-byte marks the end of the string
		memcpy(st.lastname,lastname,strlen(lastname)+1);
		memcpy(st.firstname,firstname,strlen(firstname)+1);
		memcpy(&st.mNr,&matNr,sizeof(matNr));
		memcpy(st.subject, subject,strlen(subject)+1);
		memcpy(st.nationality,nationality,strlen(nationality)+1);
		//printf("%s,%s,%d,%s,%s\n",st.lastname,st.firstname,st.mNr,st.subject,st.nationality);
		return st;
	}else if(insertCounter>size){
		st.statusFlag=0;
		return st;
	}
}
//coping input by reference
void insert_student(struct student *  st){
	
	printf("statusFlag:%d\n",st->statusFlag);
	if(st->statusFlag==1){	
		*ptrDb=*st;
		insertCounter++;
		ptrDb++;	
	}else{	
		printf("##########################################################\n");
		printf("no insert is possible, The maximum size has been reached\n");
		printf("##########################################################\n");
	}
}

void update_student(int matNr){
	char character;
	char new_lastname[20];
	char new_firstname[20];
	int  new_MatNr;
	int i;
	for (i=0;i<size;i++){
		if( (db+i)->mNr==matNr){
			begin:
			printf("please, choose the  information you want to update\n");
			printf("(a) lastname\n");
			printf("(b) firstname\n");
			printf("(c) Matriculation number\n");
			printf("(d) exit\n");
			scanf(" %c",&character);
			
			switch(character){
				case 'a':
					printf("enter the lastname\n");
					scanf("%s",new_lastname);
					memcpy((db+i)->lastname,new_lastname,strlen(new_lastname));
					printf("update successfull\n");
					break;
				case 'b':
					printf("enter the new firstname\n");
					scanf("%s",new_firstname);
					printf("%s",new_firstname);
					memcpy((db+i)->firstname, new_firstname,strlen(new_firstname));
					printf("update successfull\n");
					break;
				case 'c':
					printf("enter the new matriculation number\n");
					scanf("%d",&new_MatNr);
					(db+i)->mNr=new_MatNr;
					printf("update successfull\n");
					break;
				case 'd':
					break;
				default:
					goto begin;
			}
		}	
	}	
}


bool delete_student(int matNr){
	int new_size=size-1;
	int indexToRemove;
	int i;
	printf("now: %d\n",(db+1)->mNr);
	printf("look for the matriculation number: %d in the Database:\n",matNr);
	for (i=0;i<size;i++){
		printf("new %d\n",(db+i)->mNr);
		if((db+i)->mNr==matNr){
			printf("student found, i: %d\n",i);
			printf("new database size: %d:\n",new_size);
			indexToRemove=i+1;
			memset((db+i)->lastname,0,20);
			memset((db+i)->firstname,0,20);
			(db+i)->mNr=0;
			return 1;				
		}
	}	
	return 0;			
}

void display_result(bool  res, bool operation){
	//search Operation
	if(operation ==1){
		if(res==1){
			printf("the searched Student is in the database\n");

		}else if(res==0){
			printf("the searched Student is not in the database\n");
		}
	}else if(operation==0){//delete Operation
		if(res==1){
			printf("delete-operation succeded\n");

		}else if(res==0){
			printf("delete-operation failed\n");
		}			
	}	
}


bool search_student(int matNr){
	int i;
	for (i=0;i<size;i++){
		if((db+i)->mNr==matNr){
			return 1;			
		}
	}
	return 0;
}

void display_db(){
	printf("%10s|%10s|%10s|%30s|%10s\n","lastname","firstname","enroll. nr","subject","nationality");
	printf("========================================================\n");
	int i;
	for(i=0;i<SIZE;i++){
	printf("%10s|%10s|%10d|%30s|%10s\n",			
			(db+i)->lastname,(db+i)->firstname,(db+i)->mNr, (db+i)->subject, (db+i)->nationality);
	}
}


