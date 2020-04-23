#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "collection.h"
#define numBooks 3
#define charLen 200
/*
Luke Brouwer's Final Project Assignment.
Change the numBooks #define to the number of lines in the unCataloged text file.
*/


int main(){
    if (readFile(fPtr)==(NULL)){
         exit(-1);
    }
    readCommand();

}

void bookSearchbyAuthor(){


    int val = 0;
    printf("Enter the author of the book.\n");

    // scans the line until newline character
    scanf("%[^\n]", uCmdPtr->TorA);
    scanf("%c", &buffer);
    printf("\n");

    printf("Searching for... %s\n", uCmdPtr->TorA);

    for (int i = 0; i < numBooks; i++){

        // searches the uncataloged file for any Author name matching the scanned user input
        if(strcmp(sPtr->authorName, uCmdPtr->TorA) == 0){

            printf("\n%d %s, written by %s, has %d available copies stored in this library.\n", sPtr->ID, sPtr->titleName, sPtr->authorName, sPtr->availableCopies);

            val = 1;
            exit(0);

        }
        else {
            sPtr++;
        }
    }
    if (val != 1)
        printf("Search unsuccessful. Resetting to main.\n");
}
void bookSearchbyTitle(){
    int val = 0;
    printf("Enter the title of the book.\n");
    scanf("%[^\n]", uCmdPtr->TorA);
    scanf("%c", &buffer);

    printf("\n");
    printf("Searching for... %s\n", uCmdPtr->TorA);

    for (int i = 0; i < numBooks; i++){

        if(strcmp(bookArr[i].titleName, uCmdPtr->TorA) == 0){

            printf("\n%d %s, written by %s, has %d available copies stored in this library.\n", sPtr->ID, sPtr->titleName, sPtr->authorName, sPtr->availableCopies);

            val = 1;
            exit(0);

        }
        else {
            sPtr++;
        }
    }
    if (val != 1)
        printf("Search unsuccessful. Resetting to main.\n");

}


int bookSearchbyID(){
    int ID = 0;
    printf("Enter the ID number of the book.\n");
    scanf("%d", &ID);
    sPtr = &bookArr[ID-1];


    // allows error handling if user enters a non-integer
    if (ID != 0){
        uCommand.ID = ID;
        if (sPtr->ID == uCommand.ID){
            printf("[%d] %s, written by %s, has %d available copies stored in this library.\n", sPtr->ID, sPtr->titleName, sPtr->authorName, sPtr->availableCopies);
            return ID;
        }
        else if (uCommand.ID != sPtr->ID)
            printf("That is not a valid ID number.\n");
        else {
            printf("Search unsuccessful.\n");
        }
    }
    else {
        printf("Invalid ID number.\n");
    }

    return 1;
}

void doBorrow(int ID){
    sPtr = &bookArr[ID-1];
    if (sPtr->ID == ID && sPtr->availableCopies > 0){

        printf("Number of in-library copies before: %d\n", sPtr->availableCopies);

        // when the number of available copies decrements, the number of borrowed copies increments
        sPtr->availableCopies--;
        sPtr->borrowedCopies++;

        printf("Number of in-library copies after: %d\n", sPtr->availableCopies);

    }
    else if (sPtr->ID != ID){

        // if ID not valid / found, loops back to main
        printf("That is not a valid ID number. Resetting to main.\n");
        readCommand();
    }
    else {
        printf("\nThere are not enough books remaining to borrow. Please come back later.\nResetting to main.\n");
        readCommand();
    }


}

void doReturn(int ID){
    sPtr = &bookArr[ID-1];
    if (sPtr->ID == ID){
        printf("Number of in-library copies before: %d\n", sPtr->availableCopies);

        sPtr->availableCopies++;
        printf("Number of in-library copies after: %d\n", sPtr->availableCopies);
    }
    else if (sPtr->ID != ID){
        printf("There is no book with that ID number in our library.\n");
        readCommand();
    }


}

int readCommand(){
    int userCommand = 0;
    int userSearch = 0;


    int userID = 0;
    printf("-------------------------------------------------\n");
    printf("Enter a number to complete an action: \n");
    printf("1 to search the library.\n");
    printf("2 to borrow a book from the library. \n");
    printf("3 to return a book to the library. \n");
    printf("4 to quit this interface. \n");
    printf("-------------------------------------------------\n");


    scanf("%d", &userCommand);
    scanf("%c", &buffer);

    // accepts only integer user input
    if (userCommand != 0){
        if (userCommand == 1){
                printf("Okay. Do you want to search by [1]Author, [2]Title, or [3]ID number?\n");
                scanf("%d", &userSearch);
                scanf("%c", &buffer);
                if (userSearch == 1){
                    bookSearchbyAuthor();
                    //readCommand();
                }
                else if (userSearch == 2){
                    bookSearchbyTitle();
                    //readCommand();
                }
                else if (userSearch == 3){
                    bookSearchbyID();
                    //readCommand();
                }
                else {
                    printf("Invalid command. Please enter a valid command.\n");


                }
        }
        else if (userCommand == 2){
            printf("What is the ID number of the book you would like to borrow?\n\n");
            scanf("%d", &userID);
            doBorrow(userID);
            writeFile(wPtr);

        }
        else if (userCommand == 3){
            printf("What is the ID number of the book you would like to return?\n\n");
            scanf("%d", &userID);
            doReturn(userID);
            writeFile(wPtr);

        }
        else if (userCommand == 4){
            printf("Okay. Thank you for using our online library. Quitting now.\n");
            writeFile(wPtr);

        }

        else {
            // loops back to the main if the integer is not 1-4
            printf("Invalid command. Please enter a valid integer (1-4).\n");
            readCommand();
        }

    }
    else {
        // if user inputs string
        scanf("%s", bufferStr);
        printf("Invalid command. Please enter a valid command.\n");

    }
    return 1; // if proper return 1}
}
int readFile(FILE *fPtr){

    // sets pointer to start of struct bookArray
    sPtr = &bookArr[0];
    int i;
    char ufileName[charLen];


    printf("Enter name of file: \n");
    scanf("%s", ufileName);


    // strncat for future authorName and titleName
    if ((fPtr = fopen(ufileName, "r"))){

        for (int i = 0; i < numBooks; i++){
            sPtr->ID = i + 1;
            fscanf(fPtr, "%[^,]", sPtr->authorName);
            fscanf(fPtr, "%c", &buffer);
            fscanf(fPtr, "%d", &sPtr->availableCopies);
            fscanf(fPtr, "%c", &buffer);
            fscanf(fPtr, "%c", &buffer);
            fscanf(fPtr, "%[^\n]", sPtr->titleName);
            fscanf(fPtr, "%c", &buffer);

            printf("%d %s, %d, %s\n", sPtr->ID, sPtr->authorName, sPtr->availableCopies, sPtr->titleName);
            sPtr++;

        }

        printf("\n");

        // resets pointer for future usage
        sPtr = &bookArr[0];

    }
    else {

        // if file path not found
        printf("Uncataloged libary file not found. Closing.");
        return NULL;
    }


    sPtr = &bookArr[0];

    fclose(fPtr);
    return (sPtr);
}

int writeFile(FILE *wPtr){
    sPtr = &bookArr[0];
    int i;

    char cfileName[charLen];

    printf("\nEnter name of the cataloged file to catalog updated book information: \n");
    scanf("%s", cfileName);
    // format cfile : ID, Author (<First Name> <Last Name>), Number of available copies,  Number of borrowed copies, Book Title
    if ((fPtr = fopen(cfileName, "w"))){
        for (int i = 0; i < numBooks; i++){
        fprintf(fPtr, "%d, %s, %d, %d, %s\n", sPtr->ID, sPtr->authorName, sPtr->availableCopies, sPtr->borrowedCopies, sPtr->titleName);


        sPtr++;
        }
    }

    else {
        printf("Cataloged library file not found. Closing.");
        return NULL;
    }

    // resert sPtr back to first element
    sPtr = &bookArr[0];
    fclose(wPtr);
    return (wPtr);
}




