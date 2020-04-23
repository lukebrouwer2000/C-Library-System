#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define numBooks 3
#define charLen 200

FILE *fPtr;
FILE *wPtr;
char buffer;
char bufferStr[100];
struct Book{

    char authorName[charLen];
    int availableCopies;
    int borrowedCopies;
    char titleName[charLen];
    int ID;
};
struct Book firstBook;
struct Book bookArr[numBooks];
struct Book *sPtr;


enum commandInput{I = 'I',T = 'T',A = 'A', Q = 'Q'};
enum commandType{Search, Borrow, Return, Quit};

struct userCommand{
    enum commandInput inputT;
    enum commandType command;
    int ID;
    char TorA[1000];
};
struct userCommand uCommand;
struct userCommand *uCmdPtr = &uCommand;

int readCommand(uCmdPtr);



int readFile(FILE *fPtr);

int writeFile(FILE *wPtr);


void bookSearchbyAuthor();

void bookSearchbyTitle();

int bookSearchbyID();

void doBorrow(int ID);

void doReturn(int ID);

void applyBook(FILE *fPtr);
