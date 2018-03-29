// search.h
// Programmed by Robert Sarvis

#ifndef search_h
#define buffer_h

#include <ncurses.h>			
#include <string.h>
 
#define SIZE 50
#define LENGTH 100

    char mesg[]="Enter a string: ";		
    char sub[80];
    int row,col;

    int linelocation;
    int whichstring;

    int i, j=0, k;
    bool flag = true;

    char answer;
    char newstr[80];
 
void search(char ** str);

#endif

