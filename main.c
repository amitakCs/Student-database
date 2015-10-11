#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_ops.h"

int main(int argc, char ** argv){

	char lastname[20];
	char firstname[20];
	int  idNr=0;
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

	printf("======================================================================================================);\n");
	printf("                                        # WELCOME TO STUDENT DATABASE #    \n");
	printf("======================================================================================================\n");
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
					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("enter the lastname:          ");
					scanf("%s", lastname); 
					printf("enter the firstname:         ");
					scanf("%s", firstname);
					printf("enter the enrollment number: ");
					idNr=getIdNr();
					printf("enter the subject:           ");
					fgets(subject,30,stdin);
					remove_newline(subject);
					printf("enter the nationality:       ");
					scanf("%s",nationality);
					struct student s=getData(lastname,firstname,idNr,subject,nationality);
					insertStudent_1(&s);
					idNr=0;
					goto begin;

				}else if(insertCounter>SIZE){
					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("                            !!!No Insertion is possible!!!\n");
					puts("-------------------------------------# Student-Database #-------------------------------------");
					goto begin;

				}
		
			case 2:
				puts("-------------------------------------# Student-Database #-------------------------------------");
				printf("enter the id of the student you want to delete:    ");
				scanf("%d",&indexToRemove);
				display_result(delete_student(indexToRemove),0);
				//puts("-------------------------------------# Student-Database #-------------------------------------");
				goto begin;
			case 3:
				puts("-------------------------------------# Student-Database #-------------------------------------");
				printf("enter the id of Student you look for:               ");
				scanf("%d",&idNr);
				if(search_student(idNr)){	
					printf("student found\n");

				}else{
					printf("student not found\n");
				}
				idNr=0;
				//puts("-------------------------------------# Student-Database #-------------------------------------");
				goto begin;
			case 4:
				puts("-------------------------------------# Student-Database #-------------------------------------");
				printf("enter the id of the student for:                    ");
				scanf("%d",&idNr);
				if(search_student(idNr)){
					update_student(idNr);
				}else{
					printf("Sorry, cannot find the student with id %d\n",idNr);
				}
				idNr=0;
				//puts("-------------------------------------# Student-Database #-------------------------------------");
				goto begin;
				
			case 5:
				puts("-------------------------------------# Student-Database #-------------------------------------");
				display_db();
				goto begin;
			
			case 6:
				puts("-------------------------------------# Student-Database #-------------------------------------");
				writeData();
				//free dynamic memory
				free(db);
				db=0;
				printf("The database closed  successfully\n");
				puts("-------------------------------------# Student-Database #-------------------------------------");
				exit(0);
				goto begin;
			default:
				puts("-------------------------------------# Student-Database #-------------------------------------");
				printf("#please enter a number between 1 and 6#\n");
				//puts("-------------------------------------# Student-Database #-------------------------------------");
				goto begin;

		}
}



