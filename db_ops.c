#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db_ops.h"
#include "help_functions.h"
#include "rw_ops.h"

struct student * db = NULL;
int insertCnt = 0;

//init struct
void init_struct(struct student * st){
	st->statusFlag=0;
}

void  createDb(int size){
	

	if(checkFileIsEmpty() == 1){

		createEmptyDb(size);

	}else if(checkFileIsEmpty() == 0){

		db = (struct student *) calloc(size,sizeof(struct student));
		readData();	
	
	}
}

void  createEmptyDb(int s){

	db = (struct student *) calloc(s,sizeof(struct student));

	if(db == NULL){
		printf("size: %d\n",s);
		printf("dynamic allocation failed\n");
		exit(0);
	}

	//initialize the status-flag
	int i;
	for(i = 0; i < s; i++){

		init_struct(db+i);

	}
	printf("an empty database was created\n");
}

struct student getData(char * lastname, char * firstname, int phoneNr, char * university, char * nationality){

	struct student st;
	
	if(insertCnt <= SIZE){
	
		//0-byte marks the end of the string
		memcpy(st.lastname,lastname,strlen(lastname)+1);
		memcpy(st.firstname,firstname,strlen(firstname)+1);
		memcpy(&st.phoneNr,&phoneNr,sizeof(phoneNr));
		memcpy(st.university, university,strlen(university)+1);
		memcpy(st.nationality,nationality,strlen(nationality)+1);

		//status-flag shows if the current struct get data from user
		st.statusFlag=1;

		return st;
	}
	return st;
}

//insert student while reading from an available database
void insertStudent_0(struct student * st){

	*(db+insertCnt) =  *st;
	(db+insertCnt)->statusFlag = 1;
 	insertCnt++;
}

//insert a new Student after reading data from an available Database: coping input by reference
void insertStudent_1(struct student *  st){

	//if the struct has the status-flag 1, then it is not an empty struct
	//insert that struct into db
	if(!search_duplicate(st->phoneNr)){

		if(st->statusFlag==1){
			
			//allocate the content of the pointer st to the pointer db
			*(db+(insertCnt))=*st;
			insertCnt++;
		}

	}else{
	
		puts("-------------------------------------# Student-Database #-------------------------------------");
		printf("!!!duplicate id !!!\n");

	}
}

//modify the content of a student
void update_student(int phoneNr){

	char character;
	char new_lastname[20];
	char new_firstname[20];
	int  new_phoneNr;
	char new_university[30];
	char new_nationality[20];

	int i;
	for (i = 0; i<SIZE ;i++){

		if ((db+i)->phoneNr == phoneNr) {
			begin:
			puts("-------------------------------------# Student-Database #-------------------------------------");
			printf("please, choose one of these options\n");
			printf("(a) lastname\n");
			printf("(b) firstname\n");
			printf("(c) phone-Nr\n");
			printf("(d) university\n");
			printf("(e) nationality\n");
			printf("(g) exit\n");
			printf(">>> ");
			scanf(" %c",&character);
			
			switch(character){

				case 'a':

					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("enter the lastname:       ");
					scanf("%s",new_lastname);
					memcpy((db+i)->lastname,new_lastname,strlen(new_lastname)+1);
					puts("------------------------# Student-Database #------------------------");
					printf("update successfull\n");
					goto begin;

				case 'b':

					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("enter the new firstname:  ");
					scanf("%s",new_firstname);
					printf("%s",new_firstname);
					memcpy((db+i)->firstname, new_firstname,strlen(new_firstname)+1);
					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("update successfull\n");
					goto begin;

				case 'c':

					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("enter the new phone-Nr:       ");
					scanf("%d",&new_phoneNr);
					getchar();
					(db+i)->phoneNr = new_phoneNr;
					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("update successfull\n");
					goto begin;

				case 'd':

					puts("-------------------------------------# Student-Database #-------------------------------------");
					clear_stdin(stdin);
					printf("enter the new university:    ");
					fgets(new_university,30,stdin);
					remove_newline(new_university);
					memcpy((db+i)->university ,new_university,strlen(new_university)+1);
					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("update successfull\n");
					goto begin;
					
				case 'e':

					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("enter the new nationality:   ");
					scanf("%s",new_nationality);
					memcpy((db+i)->nationality,new_nationality,strlen(new_nationality)+1);
					puts("-------------------------------------# Student-Database #-------------------------------------");
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

bool delete_student(int phoneNr){
	int new_size=0;
	int indexToRemove;
	int i;
	struct student * db_copy;
		printf("look for the phone-number: %d in the Database:\n",phoneNr);
	//determine the index to be removed from database
	for (i=0; i<SIZE ;i++){
		if((db+i)->phoneNr ==  phoneNr){
			indexToRemove = i;
			new_size = SIZE-1;			
		}
	}
	//make a copy of the content of the array, if the id was found.
	if(new_size != 0){

		printf("begin processing\n");
		//create a new dynamic array
		db_copy = (struct student *) calloc(SIZE, sizeof(struct student));
		//copy elements before the element to be removed
		int i = 0;
		int k = 0;

		while(i < indexToRemove){

				//index for db_copy
				memcpy((db_copy+k)->lastname,(db+i)->lastname,strlen((db+i)->lastname)+1);
				memcpy((db_copy+k)->firstname,(db+i)->firstname,strlen((db+i)->firstname)+1);
				(db_copy+k)->phoneNr = (db+i)->phoneNr;
				memcpy((db_copy+k)->university ,(db+i)->university, strlen((db+i)->university)+1);
				memcpy((db_copy+k)->nationality,(db+i)->nationality,strlen((db+i)->nationality)+1);
				i=i+1;
				k=k+1;
		}

		//copy elements after the elements to be removed
		i = indexToRemove+1;
		while(i > indexToRemove && i <= new_size){
			//index for db_copy
			int k=i-1;
			memcpy((db_copy+k)->lastname,(db+i)->lastname,strlen((db+i)->lastname)+1);
			memcpy((db_copy+k)->firstname,(db+i)->firstname,strlen((db+i)->firstname)+1);
			(db_copy+k)->phoneNr=(db+i)->phoneNr;
			memcpy((db_copy+k)->university,(db+i)->university,strlen((db+i)->university)+1);
			memcpy((db_copy+k)->nationality,(db+i)->nationality,strlen((db+i)->nationality)+1);
			i=i+1;
			k=k+1;
		}

		db=db_copy;
		//free(db_copy);
		//db_copy=NULL;	
		insertCnt--;			
		return 1;	
	}		
	return 0;			
}

void display_result(bool  res, bool operation){

	//search Operation
	if(operation == 1){

		if(res == 1){

			printf("the student is in the database\n");


		}else if(res == 0){

			printf("the student is not in the database\n");

		}

	}else if(operation  == 0){//delete Operation

		if(res == 1){
 
			printf("delete-operation succeded\n");

		}else if(res ==  0){

			printf("delete-operation failed\n");

		}			
	}	
}


bool search_student(int phoneNr){

	int i;
	for (i=0;i < SIZE;i++){

		if((db+i)->phoneNr == phoneNr){
			return 1;		
	
		}
	}
	//student not found
	return 0;
}

void display_db(){

	printf("%10s|%10s|%10s|%30s|%10s\n","lastname","firstname","Phone-nr","subject","nationality");
	printf("======================================================================================\n");
	int i;
	for (i=0; i <SIZE; i++) {
		
		if((db+i)->statusFlag == 1){
			printf("%10s|%10s|%10d|%30s|%10s\n",			
				(db+i)->lastname,(db+i)->firstname,(db+i)->phoneNr, (db+i)->university, (db+i)->nationality);
		}	
	}
	printf("\n");
	
}



