#ifndef DB_OPS
#define DB_OPS

#define SIZE 100

//define boolean-type
typedef int bool;
#define true 1
#define false 0

extern int  insertCnt;

//declaration of the struct
struct student {

	//a flag that shows if the current struct get data
	bool statusFlag;
	char lastname[20];
	char firstname[20];
	int  phoneNr;
	char university[30];
	char nationality[20];

};

extern struct student * db;

void createDb();
void  createEmptyDb(int s);
struct student getData(char * lastname, char * firstname, int phoneNr, char * university, char * nationality);
void insertStudent_0(struct student *  st);
void insertStudent_1(struct student * st);
void update_student(int phoneNr);
bool delete_student(int phoneNr);
void display_result(bool  res, bool operation);
bool search_student(int phoneNr);
void display_db();

#endif
