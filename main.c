#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_ops.h"

int reach_end_stdin(){
	while(getchar()!='\n');
	return 1;
}
void remove_newline(char * str){
	size_t str_len=strlen(str);
	if(str_len && str[str_len-1]=='\n'){
		str[str_len-1]=0;
	}
}
extern  struct student * db;
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
		}while((!scanf("%d",&operation))&&reach_end_stdin());
		switch(operation){
			case 1:		
				puts("---------------------------------");
				printf("enter the lastname:          ");
				scanf("%s", lastname); 
				printf("enter the firstname:         ");
				scanf("%s", firstname);
				printf("enter the enrollment number: ");
				scanf("%d",&matNr);
				getchar();
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
			case 2:
				puts("-----------------------------------");
				printf("enter the matriculation number of the Student to be delete:\n");
				scanf("%d",&indexToRemove);
				display_result(delete_student(indexToRemove),0);
				puts("----------------------------------- ");
				goto begin;
			case 3:
				puts("----------------------------------");
				printf("enter the matriculation number of Student you are searching:\n");
				scanf("%d",&matNr);
				search_student(matNr);
				matNr=0;
				goto begin;
			case 4:
				puts("----------------------------------");
				printf("enter the matriculation of the student you want to update his data\n");
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


