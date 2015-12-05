#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_ops.h"
#include "help_functions.h"
#include "rw_ops.h"

insertCnt = 0;

int main(int argc, char ** argv){

	char lastname[20];
	char firstname[20];
	int  phone_nr = 0;
	char university[30];
	char nationality[20];
	int  operation;
	int  indexToRemove;

	//initialize the arrays
	memset(lastname,0,20*sizeof(char));
	memset(firstname,0,20*sizeof(char));
	memset(university,0,20*sizeof(char));
	memset(nationality,0,20*sizeof(char));
	createDb(SIZE);

	printf("======================================================================================================\n");
	printf("                                        # WELCOME TO STUDENT DATABASE #    \n");
	printf("======================================================================================================\n");
	printf("\n");

	begin:		
		operation = 0;
		do { 
    			printf("\n");
			printf("please choose one of these operations:\n");
			printf("   (1) enter a new student\n");
			printf("   (2) delete a student\n");
			printf("   (3) search a student\n");
			printf("   (4) update database\n");
			printf("   (5) show the current database\n");
			printf("   (6) exit\n");
			printf(">>> ");

		} while ((!scanf("%d",&operation)) && clear_stdin(stdin));

		switch (operation) {

			case 1:	
				if (insertCnt <= SIZE) {

					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("enter the lastname    : ");
					scanf("%s", lastname); 
					printf("enter the firstname   : ");
					scanf("%s", firstname);
					printf("enter the phone number: ");
					phone_nr=getPhoneNr();
					printf("enter the university  : ");
					fgets(university,30,stdin);
					remove_newline(university);
					printf("enter the nationality : ");
					scanf("%s",nationality);
					struct student s=getData(lastname, firstname, phone_nr, university, nationality);
					insertStudent_1(&s);
					phone_nr=0;
					goto begin;

				} else if (insertCnt > SIZE) {

					puts("-------------------------------------# Student-Database #-------------------------------------");
					printf("                            !!!The database is full. No Insertion is possible!!!\n");
					puts("-------------------------------------# Student-Database #-------------------------------------");
					goto begin;

				}
		
			case 2:

				puts("-------------------------------------# Student-Database #-------------------------------------");
				printf("enter the phone number  of the student you want to delete:    ");
				scanf("%d",&indexToRemove);
				display_result(delete_student(indexToRemove),0);
				//puts("-------------------------------------# Student-Database #-------------------------------------");
				goto begin;

			case 3:

				puts("-------------------------------------# Student-Database #-------------------------------------");
				printf("enter the phone number of Student you look for:               ");
				scanf("%d",&phone_nr);

				if (search_student(phone_nr)) {	

					printf("student found\n");

				} else {

					printf("student not found\n");

				}

				phone_nr = 0;
				//puts("-------------------------------------# Student-Database #-------------------------------------");
				goto begin;

			case 4:
				puts("-------------------------------------# Student-Database #-------------------------------------");
				printf("enter the phone number  of the student for:                    ");
				scanf("%d",&phone_nr);

				if (search_student(phone_nr)) {

					update_student(phone_nr);

				} else {

					printf("Sorry, cannot find the student with the entered phone number  %d\n", phone_nr);
				}
				phone_nr=0;
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
				exit(0);
				goto begin;
			default:
				puts("-------------------------------------# Student-Database #-------------------------------------");
				printf("#please enter a number between 1 and 6#\n");
				goto begin;

		}
}



