#ifndef HELP_FUNCTIONS
#define HELP_FUNCTIONS

bool search_duplicate(int id);
int  checkFileIsEmpty();
bool checkIfDataAvailable(struct student * db);
void parseLine(char * str,char * tokens [], int max_tokens);
void remove_semicolon(char * str);
int  clear_stdin(FILE * in);
int  getPhoneNr();
void remove_newline(char * str);

#endif
