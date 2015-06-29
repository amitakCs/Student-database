#ifndef DB_OPS
#define DB_OPS
#define SIZE 3
typedef int bool;
#define true 1
#define false 0
struct student{
	bool statusFlag;
	char lastname[20];
	char firstname[20];
	int  mNr;
	char subject[30];
	char nationality[20];
};

int createDb(int s);
struct student getData(char * lastname, char * firstname, int matNr, char * courseOfStudy, char * nationality);
void insert_student(struct student *  st);
void update_student(int matNr);
bool delete_student(int matNr);
void display_result(bool  res, bool operation);
bool search_student(int matNr);
void display_db();
void writeData();
void readData();
void print();
#endif
