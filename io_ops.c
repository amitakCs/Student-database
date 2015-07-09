#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db_ops.h"

struct student * db;
int insertCounter=1;
int size=0;
void init_struct(struct student * st){
	st->statusFlag=0;
}
int   createDb(int s){
	size=s;
	db= (struct student *)calloc(3,sizeof(struct student));
	if(db==NULL){
		printf("dynamic allocation failed");
		return EXIT_FAILURE;
	}
	//initialize the status-flag
	int i;
	for(i=0;i<size;i++){
		init_struct(db+i);
	}
	printf("database was created\n");
}
struct student getData(char * lastname, char * firstname, int matNr, char * subject, char * nationality){
	struct student st;
	int i;
	if(insertCounter<=size){
		//get data
		//0-byte marks the end of the string
		memcpy(st.lastname,lastname,strlen(lastname)+1);
		memcpy(st.firstname,firstname,strlen(firstname)+1);
		memcpy(&st.mNr,&matNr,sizeof(matNr));
		memcpy(st.subject, subject,strlen(subject)+1);
		memcpy(st.nationality,nationality,strlen(nationality)+1);
		//status-flag shows if the current struct get data from user
		st.statusFlag=1;
		return st;
	}
}
//coping input by reference
void insert_student(struct student *  st){
	int db_index=insertCounter-1;
	printf("db_index:%d\n",db_index);
	//if the struct has the status-flag 1, then it is not an empty struct
	//insert that struct into db
	if(!search_duplicate(st->mNr)){
		if(st->statusFlag==1){	
			//allocate the content of the pointer st to the pointer db
			*(db+db_index)=*st;
			insertCounter++;
		}
	}else{	
		puts("--------------------------------------------");
		printf("!!!duplicate id !!!\n");
	}
}

void update_student(int matNr){
	char character;
	char new_lastname[20];
	char new_firstname[20];
	int  new_id;
	char new_subject[30];
	char new_nationality[20];
	int i;
	for (i=0;i<size;i++){
		if( (db+i)->mNr==matNr){
			begin:
			puts("---------------------------------------");
			printf("please, choose one of these options\n");
			printf("(a) lastname\n");
			printf("(b) firstname\n");
			printf("(c) id-Nr\n");
			printf("(d) subject\n");
			printf("(e) nationality\n");
			printf("(g) exit\n");
			printf(">>> ");
			scanf(" %c",&character);
			
			switch(character){
				case 'a':
					puts("------------------------------");
					printf("enter the lastname:       ");
					scanf("%s",new_lastname);
					memcpy((db+i)->lastname,new_lastname,strlen(new_lastname)+1);
					puts("-----------------------------");
					printf("update successfull\n");
					goto begin;
				case 'b':
					puts("------------------------------");
					printf("enter the new firstname:  ");
					scanf("%s",new_firstname);
					printf("%s",new_firstname);
					memcpy((db+i)->firstname, new_firstname,strlen(new_firstname)+1);
					puts("------------------------------");
					printf("update successfull\n");
					goto begin;
				case 'c':
					puts("------------------------------");
					printf("enter the new id-Nr:       ");
					scanf("%d",&new_id);
					getchar();
					(db+i)->mNr=new_id;
					puts("------------------------------");
					printf("update successfull\n");
					goto begin;
				case 'd':
					puts("------------------------------");
					clear_stdin(stdin);
					printf("enter the new subject:    ");
					fgets(new_subject,30,stdin);
					remove_newline(new_subject);
					memcpy((db+i)->subject,new_subject,strlen(new_subject)+1);
					puts("-----------------------------");
					printf("update successfull\n");
					goto begin;
					
				case 'e':
					puts("------------------------------");
					printf("enter the new nationality:   ");
					scanf("%s",new_nationality);
					memcpy((db+i)->nationality,new_nationality,strlen(new_nationality)+1);
					puts("------------------------------");
					printf("update succesfull\n");
					goto begin;
				case 'g':
					break;
				default:
					goto begin;
			}
		}	
	}	
}

bool delete_student(int matNr){
	int new_size=0;
	int indexToRemove;
	int i;
	struct student * db_copy;
		printf("look for the id: %d in the Database:\n",matNr);
	//determine the index to be removed from database
	for (i=0;i<size;i++){
		if((db+i)->mNr==matNr){
			indexToRemove=i;
			new_size=size-1;			
		}
	}
	//make a copy of the content of the array, if the id was found.
	if(new_size!=0){
		printf("begin processing\n");
		//create a new dynamic array
		db_copy= calloc(size,sizeof(struct student));
		//copy elements before the element to be removed
		int i=0;
		int k=0;
		while(i<indexToRemove){
				//index for db_copy
				memcpy((db_copy+k)->lastname,(db+i)->lastname,strlen((db+i)->lastname)+1);
				memcpy((db_copy+k)->firstname,(db+i)->firstname,strlen((db+i)->firstname)+1);
				(db_copy+k)->mNr=(db+i)->mNr;
				memcpy((db_copy+k)->subject,(db+i)->subject,strlen((db+i)->subject)+1);
				memcpy((db_copy+k)->nationality,(db+i)->nationality,strlen((db+i)->nationality)+1);
				i=i+1;
				k=k+1;
		}
		//copy elements after the elements to be removed
		i=indexToRemove+1;
		while(i>indexToRemove && i<=new_size){
			//index for db_copy
			int k=i-1;
			memcpy((db_copy+k)->lastname,(db+i)->lastname,strlen((db+i)->lastname)+1);
			memcpy((db_copy+k)->firstname,(db+i)->firstname,strlen((db+i)->firstname)+1);
			(db_copy+k)->mNr=(db+i)->mNr;
			memcpy((db_copy+k)->subject,(db+i)->subject,strlen((db+i)->subject)+1);
			memcpy((db_copy+k)->nationality,(db+i)->nationality,strlen((db+i)->nationality)+1);
			i=i+1;
			k=k+1;
		}
		db=db_copy;
		//free(db_copy);
		//db_copy=NULL;	
		insertCounter--;			
		return 1;	
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
	//student not found
	return 0;
}

void display_db(){
	printf("%10s|%10s|%10s|%30s|%10s\n","lastname","firstname","enroll. nr","subject","nationality");
	printf("======================================================================================\n");
	int i;
	for(i=0;i<size;i++){
		printf("%10s|%10s|%10d|%30s|%10s\n",			
			(db+i)->lastname,(db+i)->firstname,(db+i)->mNr, (db+i)->subject, (db+i)->nationality);
	}
	
}

bool search_duplicate(int id){
	int i;
	for(i=0;i<size;i++){
		if(id==(db+i)->mNr){
			return 1;
		}
	}
	return 0;
}
