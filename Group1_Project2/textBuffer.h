// textBuffer.h
// Programmed by John Barulich

#ifndef buffer_h
#define buffer_h

#include <ncurses.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_ROW 999
#define MAX_LEN_COL 99

struct TextBuffer;
typedef struct TextBuffer{
        char* textBuffer[MAX_LEN_ROW];
        char file[20];
        int lineCount;
} buffer;


int fillBuffer(char* file, char* textBuffer[], int lineCount);
int addNewLine(char ** textBufferPtr, int line, int lineCount);


#endif
