#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_ops.h"

extern  struct student * db;
extern int insertCounter;
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

int main(int argc, char ** argv){

	char lastname[20];
	char firstname[20];
	int  matNr=0;
	char subject[30];
	char nationality[20];
	int  operation;
	int  indexToRemove;
	//initialize the arrays
	memset(lastname,0,20*sizeof(char));
	memset(firstname,0,20*sizeof(char));
	memset(subject,0,20*sizeof(char));
	memset(nationality,0,20*sizeof(char));
	createDb(SIZE);
	printf("===================================\n");
	printf("   WELCOME TO STUDENT DATABASE     \n");
	printf("===================================\n");
	printf("\n");
	begin:		
		operation=0;
		do{
			printf("please choose one of these operations:\n");
			printf("   (1) enter a new student\n");
			printf("   (2) delete a student\n");
			printf("   (3) search a student\n");
			printf("   (4) update database\n");
			printf("   (5) show the current database\n");
			printf("   (6) exit\n");
			printf(">>> ");
		}while((!scanf("%d",&operation))&&clear_stdin(stdin));
		switch(operation){
			case 1:	
				if(insertCounter<=SIZE){
					puts("---------------------------------");
					printf("enter the lastname:          ");
					scanf("%s", lastname); 
					printf("enter the firstname:         ");
					scanf("%s", firstname);
					printf("enter the enrollment number: ");
					matNr=getIdNr();
					printf("enter the subject:           ");
					fgets(subject,30,stdin);
					remove_newline(subject);
					printf("enter the nationality:       ");
					scanf("%s",nationality);
					struct student s=getData(lastname,firstname,matNr,subject,nationality);
					insert_student(&s);
					matNr=0;
					puts("---------------------------------");
					goto begin;

				}else if(insertCounter>SIZE){
					puts("------------------------------------");
					printf("!!!No Insertion is possible!!!\n");
					puts("------------------------------------");
					goto begin;

				}
		
			case 2:
				puts("-----------------------------------");
				printf("enter the id of the Student to be delete:                ");
				scanf("%d",&indexToRemove);
				display_result(delete_student(indexToRemove),0);
				puts("----------------------------------- ");
				goto begin;
			case 3:
				puts("----------------------------------");
				printf("enter the id of Student you are searching:               ");
				scanf("%d",&matNr);
				search_student(matNr);
				matNr=0;
				goto begin;
			case 4:
				puts("----------------------------------");
				printf("enter the id of the student you want to update his data: ");
				scanf("%d",&matNr);
				update_student(matNr);
				matNr=0;
				goto begin;
				
			case 5:
				puts("----------------------------------");
				display_db();
				puts("----------------------------------");
				goto begin;
			
			case 6:
				puts("----------------------------------");
				writeData();
				//free dynamic memory
				free(db);
				db=0;
				printf("The database closed  successfully\n");
				puts("----------------------------------");
				exit(0);
				goto begin;
			default:
				puts("----------------------------------");
				printf("#please enter a number between 1 and 6#\n");
				puts("----------------------------------");
				goto begin;

		}
}



